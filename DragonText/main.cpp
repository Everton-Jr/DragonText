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
		ChoosePath(player);
	}

	return 0;
}