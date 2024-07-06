export module fbc.GameRNG;

import fbc.FUtil;
import std;

namespace fbc {
	export class GameRNG {
	public:
		GameRNG() : rng(std::random_device{}()) {}
		GameRNG(unsigned int seed) : GameRNG() {
			rng.seed(seed);
		}

		inline int getCounter() { return counter; }

		GameRNG& addCounter(int counter);
		GameRNG& reset(unsigned int seed);
		bool chance(float chance);
		float random(float begin, float end);
		int random(int begin, int end);

	private:
		int counter = 0;
		std::mt19937 rng;
	};

	GameRNG& GameRNG::addCounter(int add)
	{
		this->counter += add;
		for (int i = 0; i < add; i++) {
			rng();
		}
		return *this;
	}

	bool GameRNG::chance(float chance)
	{
		++counter;
		std::bernoulli_distribution dist(chance);
		return dist(rng);
	}

	float GameRNG::random(float begin, float end)
	{
		++counter;
		std::uniform_real_distribution<float> dist(begin, end);
		return dist(rng);
	}

	int GameRNG::random(int begin, int end)
	{
		++counter;
		std::uniform_int_distribution<int> dist(begin, end);
		return dist(rng);
	}
}