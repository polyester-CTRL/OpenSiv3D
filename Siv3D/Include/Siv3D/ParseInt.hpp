﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (C) 2008-2016 Ryo Suzuki
//	Copyright (C) 2016 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# pragma once
# include "Fwd.hpp"
# include "String.hpp"
# include "Radix.hpp"

namespace s3d
{
	template <class IntegerType>
	inline IntegerType ParseInt(const String& str, Radix radix = Radix::Unspecified);

	template <>
	inline int8 ParseInt<int8>(const String& str, Radix radix)
	{
		const long result = ::wcstol(str.c_str(), nullptr, radix.value());
		return (result < INT8_MIN || INT8_MAX < result) ? 0 : static_cast<int8>(result);
	}

	template <>
	inline uint8 ParseInt<uint8>(const String& str, Radix radix)
	{
		const unsigned long result = ::wcstoul(str.c_str(), nullptr, radix.value());
		return (UINT8_MAX < result) ? 0 : static_cast<uint8>(result);
	}

	template <>
	inline int16 ParseInt<int16>(const String& str, Radix radix)
	{
		const long result = ::wcstol(str.data(), nullptr, radix.value());
		return (result < INT16_MIN || INT16_MAX < result) ? 0 : static_cast<int16>(result);
	}

	template <>
	inline uint16 ParseInt<uint16>(const String& str, Radix radix)
	{
		const unsigned long result = ::wcstoul(str.data(), nullptr, radix.value());
		return (UINT16_MAX < result) ? 0 : static_cast<uint16>(result);
	}

	template <>
	inline int32 ParseInt<int32>(const String& str, Radix radix)
	{
		# if defined (SIV3D_TARGET_WINDOWS)

			return ::wcstol(str.data(), nullptr, radix.value());

		# elif defined (SIV3D_TARGET_OSX)

			const long result = ::wcstol(str.data(), nullptr, radix.value());
			return (result < INT32_MIN || INT32_MAX < result) ? 0 : static_cast<int32>(result);

		# endif
	}

	template <>
	inline uint32 ParseInt<uint32>(const String& str, Radix radix)
	{
		# if defined (SIV3D_TARGET_WINDOWS)

			return ::wcstoul(str.data(), nullptr, radix.value());

		# elif defined (SIV3D_TARGET_OSX)

			const unsigned long result = ::wcstoul(str.data(), nullptr, radix.value());
			return (UINT32_MAX < result) ? 0 : static_cast<uint32>(result);

		# endif
	}

	template <>
	inline long ParseInt<long>(const String& str, Radix radix)
	{
		return ::wcstol(str.data(), nullptr, radix.value());
	}

	template <>
	inline unsigned long ParseInt<unsigned long>(const String& str, Radix radix)
	{
		return ::wcstoul(str.data(), nullptr, radix.value());
	}

	template <>
	inline int64 ParseInt<int64>(const String& str, Radix radix)
	{
		return ::wcstoll(str.data(), nullptr, radix.value());
	}

	template <>
	inline uint64 ParseInt<uint64>(const String& str, Radix radix)
	{
		return ::wcstoull(str.data(), nullptr, radix.value());
	}
}