#pragma once

void ChoosePath() {
	std::cout << "What do you want to do?\n";
	std::cout << "Walk: W / Search: S / Rest: R\n";
	char option = ChooseOption({ 'W', 'S', 'R' });
	
	system("cls");
	switch (option) {
	case 'W':
		std::cout << "You walk through the woods...";
		break;
	case 'S':
		std::cout << "You search for items...";
		break;
	case 'R':
		std::cout << "You try to rest...";
		break;
	}
	std::cout << '\n';
}