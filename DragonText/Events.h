#pragma once


void Walk(Player &player, int dice) {
	if (dice == 20) {
		// find a very good thing
	}
	else if (dice < 20 && dice >= 11) {
		// good or nothing happens on your way
		std::cout << "...you found nothing on your way.\n";
	}
	else if (dice < 11 && dice >= 2) {
		// a bad thing happen
	}
	else {
		// well...
	}
}

void Search(Player &player, int dice) {
	if (dice == 20) {
		// find a very good thing
	}
	else if (dice < 20 && dice >= 11) {
		// good or nothing happens on your way
	}
	else if (dice < 11 && dice >= 2) {
		// a bad thing happen
		std::cout << "...you found nothing...\n";
	}
	else {
		// well...
	}
}

void Rest(Player &player, int dice) {
	int lifeHealed = (player.MaxHealth * .3) + RollDice(player.MaxHealth * .7);
	player.Health += std::fmin(player.MaxHealth - player.Health, lifeHealed);
	if (player.Health == player.MaxHealth) {
		std::cout << "...you rested peacefully, your health is full!";
	}
	else {
		std::cout << "...you had problems resting, you healed " << lifeHealed << " points of health.";
	}
	std::cout << '\n';
}