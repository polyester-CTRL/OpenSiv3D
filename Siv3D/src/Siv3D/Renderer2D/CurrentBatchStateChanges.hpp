﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2020 Ryo Suzuki
//	Copyright (c) 2016-2020 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/Common.hpp>
# include <Siv3D/Mat3x2.hpp>
# include <Siv3D/MathConstants.hpp>

namespace s3d
{
	namespace detail
	{
		inline float CalculateMaxScaling(const Mat3x2& mat)
		{
			return (Float2{ mat._11 + mat._21, mat._12 + mat._22 }.length() / Math::Constants::Sqrt2_v<float>);
		}
	}

	template <class Enum>
	class CurrentBatchStateChanges
	{
	private:

		uint32 m_states = 0;

	public:

		[[nodiscard]]
		bool has(const Enum command) const noexcept
		{
			return ((m_states & (0x1 << FromEnum(command))) != 0);
		}

		[[nodiscard]]
		bool hasStateChange() const noexcept
		{
			return (m_states > 1);
		}

		void set(const Enum command) noexcept
		{
			m_states |= (0x1u << FromEnum(command));
		}

		void clear(const Enum command) noexcept
		{
			m_states &= ~(0x1u << FromEnum(command));
		}

		void clear() noexcept
		{
			m_states = 0;
		}
	};
}
