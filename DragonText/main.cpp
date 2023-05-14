#include <iostream>
#include <vector>

using std::string;
using std::vector;

// custom libraries
#include "Mechanics.h"
#include "Characters.h"

int main() {
	Player player;
	player.Name = "Ever";

	Weapon dagger("Dagger", 12);
	player.Found(dagger);

	Item medalion("Medalion");
	player.Found(medalion);

	return 0;
}