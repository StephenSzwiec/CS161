/*
* written by Stephen Szwiec, 13 February 2020 for CS161 at Minot State University
*/

#pragma once
#include <cstdint>
#include <random>

class CRollTheBones {
/*
* original xoshiro written in 2019 by David Blackman and Sebastiano Vigna (vigna@acm.org)
* http://prng.di.unimi.it/xoshiro256plusplus.c
* original splitmix written in 2015 by Sebastiano Vigna (vigna@acm.org)
* http://xoroshiro.di.unimi.it/splitmix64.c
*
* This method reimplements xoshiro and splitmix into a ready-made PRNG for integers using 256bit state values
* this 256state value is based on a 4*64bit array of values populated from system entropy
* this implementation is more cryptographically secure than a 32-bit Marsenne Twister for PRNG
* and is not as vulnerable to time attack or other deterministic hash value inferences as other solutions
* depending on the system clock, because it uses OS specific entropy pools
*/
private:
	//four 64bit intergers to give 256bit internal state
	uint64_t s[4];
	//collects entropy in a non-deterministic fashion from OS
	random_device rd;
	//splitmix64 function to seed the actual PRNG object 
	uint64_t splitmix(uint64_t x) {
		//take in initial seed x, then permutate recursively by xor, rotation
		uint64_t z = (x += 0x9e3779b97f4a7c15);
		z = (z ^ (z >> 30)) * 0xbf58476d1ce4e5b9;
		z = (z ^ (z >> 27)) * 0x94d049bb133111eb;
		return z ^ (z >> 31);
	}

	//static rotl method invoked for rotating bits within roller
	static inline uint64_t rotl(const uint64_t input, int roll) {
		return (input << roll) | (input >> (64 - roll));
	}

public:
	//these are only public because <random> really really wants them to be and I don't feel like redefining class functions for c++11
	using result_type = std::uint64_t;
	static constexpr result_type default_seed = 0x9e3779b97f4a7c15;
	static constexpr result_type min() { return std::numeric_limits<result_type>::min(); }
	static constexpr result_type max() { return std::numeric_limits<result_type>::max(); }

	//find the next permutation in the generator
	uint64_t next() {
		 //actual returned result is the first and last elements, rotated left 23 bits (half the length) plus the first element
		const uint64_t result = rotl(s[0] + s[3], 23) + s[0];
		const uint64_t t = s[1] << 17; //temp value with offset
		//scamble the tuples with XOR to change the 256bit state pool
		s[2] ^= s[0];
		s[3] ^= s[1];
		s[1] ^= s[2];
		s[0] ^= s[3];
		s[2] ^= t;
		//rotate last element
		s[3] = rotl(s[3], 45);
		return result;
	}

	/* This is the jump function for the generator. It is equivalent
    *  to 2^128 calls to next(); it can be used to generate 2^128
    *  non-overlapping subsequences for parallel computations.
    */
	void jump() {
		static const uint64_t JUMP[] = { 0x180ec6d33cfd0aba, 0xd5a61266f0c9392c, 0xa9582618e03fc9aa, 0x39abdc4529b1661c };
		uint64_t s0 = 0;
		uint64_t s1 = 0;
		uint64_t s2 = 0;
		uint64_t s3 = 0;
		for(int i = 0; i < sizeof JUMP / sizeof *JUMP; i++)
				for(int b = 0; b < 64; b++) {
					if (JUMP[i] & UINT64_C(1) << b) {
						s0 ^= s[0];
						s1 ^= s[1];
						s2 ^= s[2];
						s3 ^= s[3];
					}
			next();
		}
		s[0] = s0;
		s[1] = s1;
		s[2] = s2;
		s[3] = s3;
	}


	//initialize initial entropy state and randomize for default constructor
	CRollTheBones(){
		//seed from splitmix
		for(int i = 0; i < 4; i++) {
			s[i] = splitmix(rd());
		}
		//cycle 2^128 times on initialization
		jump();
	}

	result_type operator()() {
		return next();
    }
};
