#include <iostream>
#include <vector>

using std::string;
using std::vector;

// custom libraries
#include "Mechanics.h"
#include "Interface.h"
#include "Characters.h"


int main() {
	Player player;
	player.Name = "Ever";

	Enemy slime("Slime", 6, 1, .5f);
	Enemy goblin("Goblin", 18, 5, 1.7f);
	Enemy orc("Orc", 34, 11, .9f);

	while (player.Health > 0) {
		player.Interface(); 

		std::cout << "What do you want to do ? \n";
		std::cout << "Walk: W / Search: S / Rest: R\n";
		char option = ChooseOption({ 'W', 'S', 'R' });
		int dice = RollDice(20);

		system("cls");
		switch (option) {
		case 'W':
			player.Walk({ slime, goblin, orc });
			break;
		case 'S':
			player.Search();
			break;
		case 'R':
			player.Rest();
		}
	}

	return 0;
}