#pragma once

// Auto-link library on MSVC
#ifdef _MSC_VER
	#ifdef _DEBUG
		#pragma comment( lib, "mnet-Debug.lib" )
	#else
		#pragma comment( lib, "mnet-Release.lib" )
	#endif
#endif

// This file is part of 'mnet' C++ library. Copyright (C) 2010 Jani Kajala (kajala@gmail.com).
