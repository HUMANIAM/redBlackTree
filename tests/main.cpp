#define CATCH_CONFIG_RUNNER
#define TEST true
#include <catch.hpp>

#include "../benchmark.h"

int main()
{
	//If the TEST macro is defined to be true,
	//runCatchTests will be called and immediately
	//return causing the program to terminate. Change TEST
	//to false in the macro def at the top of this file
	//to skip tests and run the rest of your code.
	if (TEST)
	{
		return Catch::Session().run();
	}

	//run benchmark after passing
	//run_benchmark();
	//start working on other parts of your project here.
	return 0;
}
