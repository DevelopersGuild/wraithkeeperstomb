#ifndef CONSTANTS_H
#define CONSTANTS_H

static const int WINDOW_WIDTH = 1280;
static const int WINDOW_HEIGHT = 720;

//Hero
const float HERO_BASE_HP = 100.f;
const float HERO_BASE_SPEED = 7.f;
const int HERO_JUMP_VELOCITY = 35; //for testing purpose
const int HERO_BASE_LEVEL = 1;
const float HERO_BASE_ARMOR = 30.f;
const float HERO_BASE_DAMAGE = 20.f;
const float HERO_ARMOR_PER_LEVEL = 9.f;
const float HERO_DAMAGE_PER_LEVEL = 8.f;

const float GRAVITY = 11.f;

//Enemies
const float ENEMY_DETECTION_RADIUS = 200.f;

const float ENEMY1_BASE_HP = 100.f;
const float ENEMY1_BASE_SPEED = 3.f;
const float ENEMY1_DAMAGE = 35.f;
const float ENEMY1_ARMOR = 10.f;

const float ENEMY2_BASE_HP = 100.f;
const float ENEMY2_BASE_SPEED = 2.f;
const float ENEMY2_DAMAGE = 35.f;
const float ENEMY2_ARMOR = 15.f;

//Weapons
const float SPEAR_RANGE = 125.f;
const float SPEAR_COOLDOWN = 1.f;
const float SPEAR_DAMAGE = 25.f;
const float SPEAR_CRIT_CHANCE = 15.f;
const float SPEAR_CRIT_MULTIPLIER = 1.5f;
const float SPEAR_DMG_FLUCTUATION_RATE = 0.1f;

//Projectiles
const float HOLYORB_SPEED = 10.f;
const float HOLYORB_RANGE = 500.f;
const float HOLYORB_COOLDOWN = 1.f;
const float HOLYORB_DAMAGE = 25.f;
const float HOLYORB_CRIT_CHANCE = 10.f;
const float HOLYORB_CRIT_MULTIPLIER = 1.5f;
const float HOLYORB_DMG_FLUCTUATION_RATE = 0.3f;

const float FIREBALL_SPEED = 5.f;
const float FIREBALL_RANGE = 750.f;
const float FIREBALL_COOLDOWN = 3.f;
const float FIREBALL_DAMAGE = 20.f;
const float FIREBALL_CRIT_CHANCE = 10.f;
const float FIREBALL_CRIT_MULTIPLIER = 1.5f;
const float FIREBALL_DMG_FLUCTUATION_RATE = 0.2f;

#endif
