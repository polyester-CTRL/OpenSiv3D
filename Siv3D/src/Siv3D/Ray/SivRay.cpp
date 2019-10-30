//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2019 Ryo Suzuki
//	Copyright (c) 2016-2019 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <cfloat>
# include <Siv3D/Ray.hpp>
# include <Siv3D/AABB.hpp>
# include <Siv3D/SIMD_Float4.hpp>
# include <Siv3D/SIMDMath.hpp>

namespace s3d
{
	///////////////////////////////////////////////////////////////
	//
	//

	//
	//	DirectXMath
	//
	//	The MIT License(MIT)
	//
	//	Copyright(c) 2011 - 2019 Microsoft Corp
	//
	//	Permission is hereby granted, free of charge, to any person obtaining a copy of this
	//	softwareand associated documentation files(the "Software"), to deal in the Software
	//	without restriction, including without limitation the rights to use, copy, modify,
	//	merge, publish, distribute, sublicense, and /or sell copies of the Software, and to
	//	permit persons to whom the Software is furnished to do so, subject to the following
	//	conditions :
	//
	//	The above copyright noticeand this permission notice shall be included in all copies
	//	or substantial portions of the Software.
	//
	//	THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
	//	INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
	//	PARTICULAR PURPOSE AND NONINFRINGEMENT.IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
	//	HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
	//	CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
	//	OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

	namespace detail
	{
		inline constexpr __m128 m128_RayEpsilon{ 1e-20f, 1e-20f, 1e-20f, 1e-20f };
		inline constexpr __m128 m128_FltMin{ -FLT_MAX, -FLT_MAX, -FLT_MAX, -FLT_MAX };
		inline constexpr __m128 m128_FltMax{ FLT_MAX, FLT_MAX, FLT_MAX, FLT_MAX };

		//-----------------------------------------------------------------------------
		// Return true if any of the elements of a 3 vector are equal to 0xffffffff.
		// Slightly more efficient than using XMVector3EqualInt.
		//-----------------------------------------------------------------------------
		inline bool Vector3AnyTrue(__m128 V)
		{
			// Duplicate the fourth element from the first element.
			__m128 C = SIMD::Swizzle<SIMD::constants::SwizzleX, SIMD::constants::SwizzleY, SIMD::constants::SwizzleZ, SIMD::constants::SwizzleX>(V);

			return SIMD::ComparisonAnyTrue(SIMD::Vector4EqualIntR(C, SIMD::TrueInt()));
		}
	}

	Optional<float> Ray::intersects(const experimental::AABB& aabb) const
	{
		//assert(SIMD::Internal::Vector3IsUnit(Direction));

		const __m128 Origin = SIMD_Float4(origin, 0.0f);
		const __m128 Direction = SIMD_Float4(direction, 0.0f);

		// Load the box.
		__m128 vCenter = SIMD_Float4(aabb.center, 0.0f);
		__m128 vExtents = SIMD_Float4(aabb.size * 0.5f, 0.0f);

		// Adjust ray origin to be relative to center of the box.
		__m128 TOrigin = SIMD::Subtract(vCenter, Origin);

		// Compute the dot product againt each axis of the box.
		// Since the axii are (1,0,0), (0,1,0), (0,0,1) no computation is necessary.
		__m128 AxisDotOrigin = TOrigin;
		__m128 AxisDotDirection = Direction;

		// if (fabs(AxisDotDirection) <= Epsilon) the ray is nearly parallel to the slab.
		__m128 IsParallel = SIMD::LessOrEqual(SIMD::Abs(AxisDotDirection), detail::m128_RayEpsilon);

		// Test against all three axii simultaneously.
		__m128 InverseAxisDotDirection = SIMD::Reciprocal(AxisDotDirection);
		__m128 t1 = SIMD::Multiply(SIMD::Subtract(AxisDotOrigin, vExtents), InverseAxisDotDirection);
		__m128 t2 = SIMD::Multiply(SIMD::Add(AxisDotOrigin, vExtents), InverseAxisDotDirection);

		// Compute the max of min(t1,t2) and the min of max(t1,t2) ensuring we don't
		// use the results from any directions parallel to the slab.
		__m128 t_min = SIMD::Select(SIMD::Min(t1, t2), detail::m128_FltMin, IsParallel);
		__m128 t_max = SIMD::Select(SIMD::Max(t1, t2), detail::m128_FltMax, IsParallel);

		// t_min.x = maximum( t_min.x, t_min.y, t_min.z );
		// t_max.x = minimum( t_max.x, t_max.y, t_max.z );
		t_min = SIMD::Max(t_min, SIMD::SplatY(t_min));  // x = max(x,y)
		t_min = SIMD::Max(t_min, SIMD::SplatZ(t_min));  // x = max(max(x,y),z)
		t_max = SIMD::Min(t_max, SIMD::SplatY(t_max));  // x = min(x,y)
		t_max = SIMD::Min(t_max, SIMD::SplatZ(t_max));  // x = min(min(x,y),z)

		// if ( t_min > t_max ) return false;
		__m128 NoIntersection = SIMD::Greater(SIMD::SplatX(t_min), SIMD::SplatX(t_max));

		// if ( t_max < 0.0f ) return false;
		NoIntersection = SIMD::OrInt(NoIntersection, SIMD::Less(SIMD::SplatX(t_max), SIMD::Zero()));

		// if (IsParallel && (-Extents > AxisDotOrigin || Extents < AxisDotOrigin)) return false;
		__m128 ParallelOverlap = SIMD::InBounds(AxisDotOrigin, vExtents);
		NoIntersection = SIMD::OrInt(NoIntersection, SIMD::AndCInt(IsParallel, ParallelOverlap));

		if (!detail::Vector3AnyTrue(NoIntersection))
		{
			float distance = 0.0f;
			// Store the x-component to *pDist
			SIMD::StoreFloat(&distance, t_min);
			return distance;
		}
		
		return none;
	}

	//
	//
	///////////////////////////////////////////////////////////////
}
