#pragma once

class Enemy;

class Entity {
public:
	string Name = "Entity";
	int MaxHealth = 100;
	int Health = MaxHealth;
	int Damage = 10;
	float Speed = 1.0f;

	void TakeDamage(int amount) {
		Health -= amount;
	}
};

class Player : Entity {

};

class Enemy : Entity {

};