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

	void Walk() {
		Steps++;
		std::cout << "You walk through the woods...\n";
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
		}
		else {
			// well...
		}
		std::cout << '\n';
	}

	void Search() {
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