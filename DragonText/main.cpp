#include <iostream>
#include <vector>

using std::string;
using std::vector;

// custom libraries
#include "Mechanics.h"
#include "Characters.h"
#include "Events.h"

int main() {
	Player player;
	player.Name = "Ever";

	while (player.Health > 0) {
		std::cout << "What do you want to do ? \n";
		std::cout << "Walk: W / Search: S / Rest: R\n";
		char option = ChooseOption({ 'W', 'S', 'R' });

		system("cls");
		switch (option) {
		case 'W':
			std::cout << "You walk through the woods...\n";
			Walk();
			break;
		case 'S':
			std::cout << "You search for items...\n";
			Search();
			break;
		case 'R':
			std::cout << "You try to rest...\n";
			Rest(player);
		}
	}

	return 0;
}