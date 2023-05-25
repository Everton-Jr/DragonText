#pragma once

class Enemy;
class Item;

class Entity {
public:
	string Name = "Entity";
	int MaxHealth = 100;
	int Health = MaxHealth;
	int RawDamage = 5;
	float Speed = 1.0f;

	virtual int GetDamage() {
		int damage = round(RawDamage * .7);
		int additionalDamage = ceil(RawDamage * .3);
		return damage + RollDice(additionalDamage);
	}

	virtual void Interface() {
		Line();
		std::cout << Name << "\n\n";
		std::cout << "Health: " << Health << '/' << MaxHealth << '\n';
		Line();
		std::cout << '\n';
	}

	void TakeDamage(int amount) {
		std::cout << "..." << Name << " received " << amount << " points of damage!\n";
		Health -= amount;
	}

	void Attack(Entity& otherEntity) {
		int chance = 20;
		int evasionChance = abs((chance / otherEntity.Speed) - chance);
		std::cout << "X " << Name << " attacked " << otherEntity.Name << "...\n";
		if (RollDice(chance) > evasionChance) {
			int damage = GetDamage();
			otherEntity.TakeDamage(damage);
		}
		else {
			std::cout << "..." << Name << " missed the attack.\n";
		}
	}
};

class Player : public Entity {
public:
	int Strength = 1;
	int Gold = RollDice(20);
	int Steps = 0;

	int GetDamage() {
		int damage = round(RawDamage * .7) + Strength;
		int additionalDamage = ceil(RawDamage * .3);
		return damage + RollDice(additionalDamage);
	}

	void Interface() {
		Line();
		std::cout << Name << "\n\n";
		std::cout << "Health: " << Health << '/' << MaxHealth << '\n';
		std::cout << "Gold: " << Gold << '\n';
		std::cout << "Steps: " << Steps << " ft" << '\n';
		Line();
		std::cout << '\n';
	}

	void Fight(Entity enemy);
	void Walk(vector<Enemy> enemies);

	void Search() {
		std::cout << "You search for items...\n";
		int dice = RollDice(20);
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
		std::cout << '\n';
	}

	void Rest() {
		std::cout << "You try to rest...\n";
		int lifeHealed = (MaxHealth * .3) + RollDice(MaxHealth * .7);
		Health += std::fmin(MaxHealth - Health, lifeHealed);
		if (Health == MaxHealth) {
			std::cout << "...you rested peacefully, your health is full!";
		}
		else {
			std::cout << "...you had problems resting, you healed " << lifeHealed << " points of health.";
		}
		std::cout << "\n\n";
	}

	void Found(Item& item);
};

class Enemy : public Entity {
public:
	Enemy(string name_, int health_, int damage_, float speed_) {
		Name = name_;
		MaxHealth = health_;
		Health = MaxHealth;
		RawDamage = damage_;
		Speed = speed_;
	}
};

class Item {
public:
	string Name = "Item";

	Item(string name_) {
		Name = name_;
	}

	virtual void Use(Player& player) {
		std::cout << "..." << player.Name << " used the " << Name << '.';
	}
};

class Weapon : public Item {
public:
	int Damage = 12;

	Weapon(string name_, int damage_) : Item(name_) {
		Name = name_;
		Damage = damage_;
	}

	void Use(Player& player) {
		std::cout << "..." << player.Name << " equipped the " << Name << '.';
		player.RawDamage = Damage;
	}
};

// methods
void Player::Found(Item& item) {
	std::cout << "You found a " << item.Name << " want to keep it?\n";
	std::cout << "Yes: Y / No: N\n";
	char option = ChooseOption({ 'Y', 'N' });
	system("cls");
	if (option == 'Y') {
		item.Use(*this);
	}
	else {
		std::cout << "..." << Name << " left the item.";
	}
	std::cout << "\n\n";
}

void Player::Fight(Entity enemy) {
	while (Health > 0 && enemy.Health > 0) {
		Interface();
		enemy.Interface();
		std::cout << "Attack: A / Run: R\n";
		char option = ChooseOption({ 'A', 'R' });
		system("cls");

		switch (option) {
		case 'A':
			Attack(enemy);
			break;
		case 'R':
			break;
		}

		enemy.Attack(*this);
	}
	if (Health > 0) {
		// player won
	}
	else {
		std::cout << Name << " died...";
	}
}

void Player::Walk(vector<Enemy> enemies) {
	Steps++;
	std::cout << "You walk through the woods...\n";
	if (Steps % 15 != 0) {
		int dice = RollDice(20);
		if (dice == 20) {
			// find a very good thing
		}
		else if (dice < 20 && dice >= 11) {
			// good or nothing happens on your way
			std::cout << "...you found nothing on your way.\n";
		}
		else if (dice < 11 && dice >= 2) {
			// a bad thing happen
			int enemiesAmount = enemies.size();
			int enemyNumber = RollDice(enemiesAmount) - 1;
			Enemy enemy = enemies[enemyNumber];
			std::cout << "...you found the " << enemy.Name << " on your way.\n";

			Fight(enemy);
		}
		else {
			// well...
		}
	}
	else {
		std::cout << "...you found a travelling merchant\n";
		std::cout << "You want to talk to him?\n";
		std::cout << "Yes: Y / No: N\n";
		char option = ChooseOption({ 'Y', 'N' });
		if (option == 'Y') {
			// shop
		}
	}

	std::cout << '\n';
}