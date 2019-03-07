#include <time.h>
#include "TestU01.h"

uint64_t mixstate;
uint64_t mixbits() {
	uint64_t out = (mixstate +=0x9e3779b97f4a7c15);
	out = (out ^ (out>>30) *0x4be98134a5976fd3);
	out = (out ^ (out>>29) *0x3bc0993a5ad19a13);
	return out ^ (out>>31);
}

//my own implementation of xorshift256
static inline uint64_t rotl(const uint64_t x, int k) {
	return (x << k) | (x >> (64 - k));
}

static uint64_t state[4];

uint64_t next() {
	uint64_t result = rotl(state[1] *5, 7) *9;
	uint64_t last = state[1] << 17;
	
	state[2] ^= state[0];
	state[3] ^= state[1];
	state[1] ^= state[2];
	state[0] ^= state[3];
	
	state[2] ^= last;
	
	state[3] = rotl(state[3], 45);
	
	return result;
}

unsigned int lol() {
	return (unsigned int)next();
}

int main(int argc, char * argv[]) {
	//create seed for rng
	mixstate = time(0);
	printf("%llu\n", mixstate);
	//use a bitmixer to better distribute seed
	state[0] = mixbits();
	state[1] = mixbits();
	state[2] = mixbits();
	state[3] = mixbits();

	unif01_Gen* gen = unif01_CreateExternGenBits("liamxor", lol);
	bbattery_BigCrush(gen);
	unif01_DeleteExternGenBits(gen);
	return 0;
}