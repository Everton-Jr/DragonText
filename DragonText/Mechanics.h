#pragma once

int indexOf(vector<int> array_, int valueToFind) {
	for (int i = 0; i < array_.size(); i++) {
		if (array_[i] == valueToFind) {
			return i;
		}
	}
	return -1;
}

char indexOf(vector<char> array_, int valueToFind) {
	for (int i = 0; i < array_.size(); i++) {
		if (array_[i] == valueToFind) {
			return i;
		}
	}
	return -1;
}

int RollDice(int maxValue) {
	// set random seed
	srand(time(NULL));
	int result = (rand() % maxValue) + 1;
	return result;
}

void ClearInput() {
	std::cin.clear();
	std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n');
}

char ChooseOption(vector<char> options) {
	char option;
	while (true) {
		if (std::cin >> option) {
			option = toupper(option);
			int optionPosition = indexOf(options, option);
			if (optionPosition != -1) {
				ClearInput();
				return options[optionPosition];
			}
		}
		else {
			ClearInput();
		}
		std::cout << "Invalid answer, try again...\n";
	}
}

int ChooseOption(vector<int> options) {
	int option;
	while (true) {
		if (std::cin >> option) {
			option = toupper(option);
			int optionPosition = indexOf(options, option);
			if (optionPosition != -1) {
				ClearInput();
				return options[optionPosition];
			}
		}
		else {
			ClearInput();
		}
		std::cout << "Invalid answer, try again...\n";
	}
}