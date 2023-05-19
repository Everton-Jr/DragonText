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
	int playerSteps = 0;

	Enemy slime("Slime", 6, 1, .5f);
	Enemy goblin("Goblin", 18, 5, 1.7f);
	Enemy orc("Orc", 34, 11, .9f);

	while (player.Health > 0) {
		std::cout << "What do you want to do ? \n";
		std::cout << "Walk: W / Search: S / Rest: R\n";
		char option = ChooseOption({ 'W', 'S', 'R' });
		int dice = RollDice(20);

		system("cls");
		switch (option) {
		case 'W':
			std::cout << "You walk through the woods...\n";
			Walk(player, dice);
			break;
		case 'S':
			std::cout << "You search for items...\n";
			Search(player, dice);
			break;
		case 'R':
			std::cout << "You try to rest...\n";
			Rest(player, dice);
		}

		playerSteps ++;
	}

	return 0;
}