#pragma once

void Line() {
	for (int i = 0; i < 30; i++) {
		std::cout << '-';
	}
	std::cout << '\n';
}

void UserInterface(Player& player) {
	Line();
	std::cout << player.Name << "\n\n";
	std::cout << "Health: " << player.Health << '/' << player.MaxHealth << '\n';
	std::cout << "Gold: " << player.Gold << '\n';
	std::cout << "Steps: " << player.Steps << " ft" << '\n';
	Line();
	std::cout << '\n';
}