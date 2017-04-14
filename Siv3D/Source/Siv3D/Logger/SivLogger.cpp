﻿//-----------------------------------------------
//
//	This file is part of the Siv3D Engine.
//
//	Copyright (c) 2008-2017 Ryo Suzuki
//	Copyright (c) 2016-2017 OpenSiv3D Project
//
//	Licensed under the MIT License.
//
//-----------------------------------------------

# include <Siv3D/Logger.hpp>
# include "../Siv3DEngine.hpp"
# include "ILogger.hpp"

namespace s3d
{
	namespace detail
	{
		void Log_impl::writeln(const String& text) const
		{
			Siv3DEngine::GetLogger()->write(LogDescription::App, text);
		}
	}

	namespace Logger
	{
		void SetOutputLevel(const OutputLevel level)
		{
			Siv3DEngine::GetLogger()->setOutputLevel(level);
		}

		void OutputLog(const LogDescription desc, const String& str)
		{
			Siv3DEngine::GetLogger()->write(desc, str);
		}

		void WriteRawHTML(const String& str)
		{
			Siv3DEngine::GetLogger()->writeRawHTML(str);
		}

		void RemoveLogOnExit()
		{
			Siv3DEngine::GetLogger()->removeLogOnExit();
		}
	}
}
