#pragma once

int RollDice(int maxValue) {
	// set random seed
	srand(time(NULL));
	int result = (rand() % maxValue) + 1;
	return result;
}