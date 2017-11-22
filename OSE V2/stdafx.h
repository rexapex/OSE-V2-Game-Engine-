#pragma once

#include <string>
#include <vector>
#include <map>

#include <iostream>
#include <memory>

//export functions for testing iff building in debug mode
#ifdef _WIN32
	#ifdef _DEBUG
		//define warning C4251 when debugging as DEBUG_EXPORT is only needed for unit tests
		//hopefully unit tests still function correctly ?!?!?!?
		//#pragma warning(disable:4251)
		#define DEBUG_EXPORT __declspec(dllexport)
	#else
		#define DEBUG_EXPORT
	#endif // DEBUG
#endif
