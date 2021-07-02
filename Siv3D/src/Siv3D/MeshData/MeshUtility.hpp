﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2021 Ryo Suzuki
//	Copyright (c) 2016-2021 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include <Siv3D/MeshData.hpp>
# include <Siv3D/SIMD_Float4.hpp>

namespace s3d
{
    namespace MeshUtility
    {
        ///////////////////////////////////////////////////////////////
        //
        //

        //
        //  DirectX Mesh Geometry Library
        //
        //  Copyright (c) 2014-2021 Microsoft Corp
        //
        //  Permission is hereby granted, free of charge, to any person obtaining a copy of this
        //  software and associated documentation files (the "Software"), to deal in the Software
        //  without restriction, including without limitation the rights to use, copy, modify,
        //  merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
        //  permit persons to whom the Software is furnished to do so, subject to the following
        //  conditions:
        //
        //  The above copyright notice and this permission notice shall be included in all copies
        //  or substantial portions of the Software.
        //
        //  THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED,
        //  INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A
        //  PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT
        //  HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF
        //  CONTRACT, TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE
        //  OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.

        enum CNORM_FLAGS : unsigned long
        {
            CNORM_DEFAULT = 0x0,
            // Default is to compute normals using weight-by-angle

            CNORM_WEIGHT_BY_AREA = 0x1,
            // Computes normals using weight-by-area

            CNORM_WEIGHT_EQUAL = 0x2,
            // Compute normals with equal weights

            CNORM_WIND_CW = 0x4,
            // Vertices are clock-wise (defaults to CCW)
        };

        bool ComputeNormals(
            _In_reads_(nFaces * 3) const uint32_t* indices, _In_ size_t nFaces,
            _In_reads_(nVerts) const DirectX::XMFLOAT3* positions, _In_ size_t nVerts,
            _In_ CNORM_FLAGS flags,
            _Out_writes_(nVerts) DirectX::XMFLOAT3* normals) noexcept;
        //
        //
        ///////////////////////////////////////////////////////////////
    }
}
