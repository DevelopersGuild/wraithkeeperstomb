#ifndef CONSTANTS_H
#define CONSTANTS_H

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;


//Hero
const float HERO_BASE_HP = 100.f;
const float HERO_BASE_SPEED = 7.f;
const int HERO_BASE_LEVEL = 1;
const float HERO_BASE_ARMOR = 30.f;
const float HERO_BASE_DAMAGE = 20.f;
const float HERO_ARMOR_PER_LEVEL = 9.f;
const float HERO_DAMAGE_PER_LEVEL = 8.f;

const float GRAVITY = 40.f;

//Enemies
const float ENEMY_DETECTION_RADIUS = 200.f;

const float ENEMY1_BASE_HP = 100.f;
const float ENEMY1_BASE_SPEED = 3.f;
const float ENEMY1_DAMAGE = 20.f;
const float ENEMY1_ARMOR = 10.f;

const float ENEMY2_BASE_HP = 100.f;
const float ENEMY2_BASE_SPEED = 2.f;
const float ENEMY2_DAMAGE = 35.f;
const float ENEMY2_ARMOR = 15.f;

//Weapons
const float SPEAR_RANGE = 250.f;
const float SPEAR_COOLDOWN = 1.f;
const float SPEAR_DAMAGE = 25.f;
const float SPEAR_CRIT_CHANCE = 15.f;
const float SPEAR_CRIT_MULTIPLIER = 1.5f;
const float SPEAR_DMG_FLUCTUATION_RATE = 0.1f;

#endif
