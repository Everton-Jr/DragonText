#pragma once


void Walk() {
	std::cout << "...you found nothing on your way.\n";
}

void Search() {
	std::cout << "...you found nothing...\n";
}

void Rest(Player &player) {
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