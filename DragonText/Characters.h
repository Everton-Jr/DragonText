#pragma once
#include <iomanip>

class Enemy;
class Item;

class Entity {
public:
	string Name = "Entity";
	int MaxHealth = 100;
	int Health = MaxHealth;
	int RawDamage = 5;
	float Speed = 1.0f;

	const float MAX_VELOCITY = 3.0f;


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

	void Attack(Entity &otherEntity) {
		int chance = 20;
		int enemyMaxVelocity = 3.0f;
		int evasionChance = chance * (otherEntity.Speed / MAX_VELOCITY);
		evasionChance = fmin(chance - 1, evasionChance);
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

	void FindGold(int quantity) {
		std::cout << Name << " found " << quantity << " of gold...\n";
		Gold += quantity;
	}
	
	void Found(Item&);
	void Fight(Entity);
	void Walk(vector<Enemy>);
	void Search();
	void Rest(vector<Enemy>);
};

class Enemy : public Entity {
public:
	Enemy(string name_, int health_, int damage_, float speed_) {
		Name = name_;
		MaxHealth = health_;
		Health = MaxHealth;
		RawDamage = damage_;
		Speed = fmin(speed_, MAX_VELOCITY);
	}
};

class Item {
public:
	string Name = "Item";
	string Description = "It's useful!";
	int GoldValue = 0;

	Item(string name_) {
		Name = name_;
	}

	virtual void Use(Player& player) {
		std::cout << "..." << player.Name << " used the " << Name << ".\n";
	}
};

class Herb : public Item {
public:
	int HealPower = 5;

	Herb(string name_, int healPower_, int goldValue_ = 0) : Item(name_) {
		Name = name_;
		HealPower = healPower_;
		GoldValue = goldValue_;
	}

	void Use(Player& player) {
		player.Health += HealPower;
		std::cout << Name << " cured " << player.Name << " by " << HealPower << " health\n";
	}
};

class Weapon : public Item {
public:
	int Damage = 12;

	Weapon(string name_, int damage_, string description_, int goldValue_ = 0) : Item(name_) {
		Name = name_;
		Damage = damage_;
		Description = description_;
		GoldValue = goldValue_;
	}

	virtual void Use(Player& player) {
		player.RawDamage = Damage;
		std::cout << "..." << player.Name << " equipped the " << Name << ".\n";
	}
};

// methods
void Player::Found(Item& item) {
	std::cout << "You found a " << item.Name << " want to keep it?\n";
	std::cout << "Yes: Y / No: N\n";
	char option = ChooseOption(vector<char>{ 'Y', 'N' });
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
	bool runned = false;
	while (Health > 0 && enemy.Health > 0) {
		Interface();
		enemy.Interface();
		std::cout << "Attack: A / Run: R\n";
		char option = ChooseOption(vector<char>{ 'A', 'R' });
		system("cls");

		if (option == 'A') {
			Attack(enemy);
		}
		else if (option == 'R') {
			int runChance = RollDice(20) + Speed;
			int enemyCatchChance = fmin(enemy.Speed * 6, 19);
			std::cout << Name;
			if (runChance > enemyCatchChance) {
				std::cout << " runned!\n";
				runned = true;
				break;
			}
			std::cout << " couldn't run...\n";
		}

		enemy.Attack(*this);
	}
	if (Health <= 0) {
		std::cout << Name << " died...\n";
	}
	else {
		if (!runned) {
			FindGold(RollDice(enemy.MaxHealth / 2));
		}
	}
}

void Player::Walk(vector<Enemy> enemies) {
	Steps++;
	std::cout << "You walk through the woods...\n";
	// Steps % 15 != 0
	if (false) {
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
		char option = ChooseOption(vector<char>{ 'Y', 'N' });
		if (option == 'Y') {
			// shop
			vector<Item> itemsForSale = {
				Weapon("Dagger", 6, "Deals 6 of damage", 3),
				Weapon("Simple Sword", 15, "Deals 15 of damage", 10),
				Weapon("Long Sword", 20, "Deals 20 of damage", 20),
				Weapon("Great Sword", 25, "Deals 25 of damage", 30),
				Weapon("Fire staff", 30, "Deals 30 of damage", 50)
			};
			std::cout << "Enter an item between 1 and " << itemsForSale.size() << std::endl;
			vector<int> options = {};
			for (int i = 1; i <= itemsForSale.size(); i++) {
				int realKey = i - 1;
				int identation = 14;
				std::cout << i << ". ";
				std::cout << std::left << std::setw(identation) << itemsForSale[realKey].Name + ":";
				std::cout << std::right << std::setw(identation) << itemsForSale[realKey].Description;
				std::cout << std::setw(9) << itemsForSale[realKey].GoldValue << " golds" << std::endl;
				options.push_back(i);
			}
			
			int option = ChooseOption(options);
			Item choosedItem = itemsForSale[option];
			std::cout << "Are you sure you want to buy " << choosedItem.Name << "?\n";
			std::cout << "Yes: Y / No: N\n";
			char accepted = ChooseOption(vector<char>{ 'Y', 'N' });
			if (accepted == 'Y') {
				if (Gold < choosedItem.GoldValue) {
					std::cout << "You don't have gold...\n";
				}
				else {
					std::cout << "You bought the item...\n";
					Gold -= choosedItem.GoldValue;
					choosedItem.Use(*this);
				}
			}
			std::cout << "...You leave the shop.\n";
		}
	}

	std::cout << '\n';
}

void Player::Search() {
	std::cout << "You search for items...\n";
	int dice = RollDice(20);
	// 'true' for testing <<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<<
	if (true) {
		// find a very good thing
		int eventNumber = RollDice(2);
		switch (eventNumber) {
		case 1:
			// int goldQuantity = 50 + RollDice(150);
			FindGold(50 + RollDice(150));
			break;
		case 2:
			vector<Item> possibleItems = {
				Weapon("Large Sword", 20, "Deals 20 of damage"),
				// Item("Golden Glove")
			};
			Item item = possibleItems[RollDice(possibleItems.size()) - 1];
			Found(item);
			break;
		}
	}
	else if (dice < 20 && dice >= 11) {
		// good or nothing happens on your way
		vector<Item> possibleItems = {
			Weapon("Large Sword", 20, "Deals 20 of damage"),
			Item("Golden Glove")
		};
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

void Player::Rest(vector<Enemy> enemies) {
	std::cout << "You try to rest...\n";
	if (RollDice(20) <= 5) {
		std::cout << "...an enemy found you trying to rest.\n";
		Enemy enemy = enemies[RollDice(enemies.size()) - 1];
		Fight(enemy);
	}
	else {
		int lifeHealed = RollDice(MaxHealth * .6);
		Health += std::fmin(MaxHealth - Health, lifeHealed);
		if (Health == MaxHealth) {
			std::cout << "...you rested peacefully, your health is full!";
		}
		else {
			std::cout << "...you had problems resting, you healed " << lifeHealed << " points of health.";
		}
		std::cout << "\n\n";
	}
}