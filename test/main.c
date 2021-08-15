#undef TESTLY_ASSERT_DISABLED
#include <testly/assert.h>
#include <testly/config.h>
#include <testly/run.h>

#include <stdlib.h>
#include <stdio.h>
#include <stdint.h>
#include <string.h>

static const char* SunshineHaiku = "Inspiring Hope.\nThrough the glistening sunshine.\nA new day to laugh again.";

char* GenerateSunshine()
{
	char* Copy = strdup(SunshineHaiku);
	return Copy;
}

int TestSunshine()
{
	const char* Expected = SunshineHaiku;
	char* Sunshine = GenerateSunshine();

	int Passed = Assert(0, "GenerateSunshine", TESTLY_EXIT_ON_FAIL,
		Expected, Sunshine, 
		"Expected %s, got %s.", Expected, Sunshine
	);

	free(Sunshine);

	return Passed;
}

int TestRainAndFail()
{
	Fail("Rain", TESTLY_EXIT_ON_FAIL, "Missing umbrella.");

	int Expected = 23;
	int Rain = 42;

	return Assert(sizeof(Expected), "RainStorm", TESTLY_EXIT_ON_FAIL,
		&Expected, &Rain,
		"Expected %i, got %i.", Expected, Rain
	);
}

int main(void)
{
	RUN_TEST(TestRainAndFail);
	RUN_TEST(TestSunshine);
	printf("Disabling color ...\n");
	Testly_SetColorMode(0);
	RUN_TEST(TestSunshine);
}