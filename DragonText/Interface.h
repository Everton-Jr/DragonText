#pragma once

void Line() {
	for (int i = 0; i < 20; i++) {
		std::cout << '-';
	}
	std::cout << '\n';
}

void UserInterface(Player& player) {
	Line();
	std::cout << player.Name << "\n\n";
	std::cout << "Health: " << player.Health << '/' << player.MaxHealth << '\n';
	std::cout << "Steps: " << player.Steps << " ft" << '\n';
	Line();
}