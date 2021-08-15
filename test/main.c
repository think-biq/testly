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

	int Passed = Check("RainStorm", 0, Expected, Sunshine,
		"Expected %s, got %s.", Expected, Sunshine
	);

	free(Sunshine);

	return Passed;
}

int TestRainAndFail()
{
	Fail("Rain", 0, "Missing umbrella.");

	int Expected = 23;
	int Rain = 42;

	return Check("RainStorm", sizeof(Expected), &Expected, &Rain,
		"Expected %i, got %i.", Expected, Rain
	);
}

int TestColor()
{
	int bColorConfig = Testly_IsColorModeActive();

	Testly_SetColorMode(1);
	Fail("Colored", 0, "Failing with color.");

	Testly_SetColorMode(0);
	Fail("Uncolored", 0, "Failing without color.");
	Testly_SetColorMode(1);

	Testly_SetColorMode(bColorConfig);

	return 1;
}

int main(void)
{
	RUN_TEST(TestRainAndFail);
	RUN_TEST(TestSunshine);
	RUN_TEST(TestColor);
}