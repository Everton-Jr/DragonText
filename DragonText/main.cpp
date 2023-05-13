#include <iostream>
#include <vector>

using std::string;
using std::vector;

// custom libraries
#include "Mechanics.h"
#include "Characters.h"

int main() {
	Player player;
	player.Name = "Player";

	Enemy snake("Snake", 10, 1, 2.1f);

	player.Attack(snake);
	snake.Attack(player);

	return 0;
}