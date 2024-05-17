#include "FixedMath.h"

uint16_t RandomOld()
{
	static uint16_t randVal = 0xABC;

	uint16_t lsb = randVal & 1;
	randVal >>= 1;
	if (lsb == 1)
		randVal ^= 0xB400u;

	return randVal - 1;
}

static uint16_t xs = 1;

uint16_t Random()
{
	xs ^= xs << 7;
	xs ^= xs >> 9;
	xs ^= xs << 8;
	return xs;
}

void SeedRandom(uint16_t seed)
{
	xs = seed | 1;
}
