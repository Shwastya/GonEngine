// Entry Point (main projects)
#pragma once

// Call for side project client
#include "engine/gon.hpp"

#if defined(GON_WIN64) || defined(GON_WIN32)

int main(int argc, char** argv)
{
	GON_LOG_ON
	{
		auto test{ gon::initProject() };
		test->run();
		delete test;
		return 0;
	}		
	GON_LOG_OFF
}

#endif
