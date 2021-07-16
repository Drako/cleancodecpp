#pragma once

// only DLLs on Windows
#ifdef _WIN32
#	ifdef BUILD_DLL
#		ifdef _MSC_VER
#			define GOL_DLL_INTERFACE __declspec(dllexport)
#		else // !_MSC_VER
#			define GOL_DLL_INTERFACE __attribute__((dllexport))
#		endif // _MSC_VER
#	else // !BUILD_DLL
#		ifdef _MSC_VER
#			define GOL_DLL_INTERFACE __declspec(dllimport)
#		else // !_MSC_VER
#			define GOL_DLL_INTERFACE __attribute__((dllimport))
#		endif // _MSC_VER
#	endif // BUILD_DLL
#endif // _WIN32
