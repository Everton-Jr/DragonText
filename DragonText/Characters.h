#pragma once

class Entity {
public:
	string Name = "Entity";
	int MaxHealth = 100;
	int Health = MaxHealth;
	int RawDamage = 10;
	float Speed = 1.0f;

	int GetDamage() {
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
		string message;
		if (RollDice(chance) > evasionChance) {
			std::cout << Name << " attacked " << otherEntity.Name << '\n';
			int damage = GetDamage();
			otherEntity.TakeDamage(damage);
		}
		else {
			std::cout << Name << " missed the attack\n";
		}
	}
};

class Enemy;

class Player : public Entity {
public:
	int Strength = 1;

	int GetDamage() {
		int damage = round(RawDamage * .7) + Strength;
		int additionalDamage = ceil(RawDamage * .3);
		return damage + RollDice(additionalDamage);
	}
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