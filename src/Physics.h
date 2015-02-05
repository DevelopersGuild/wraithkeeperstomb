#include <Rect.hpp>

#ifndef ___CL_PHYSICS
#define ___CL_PHYSICS

// Applies physics (gravity, collisions, motion) to an entity.

void doPhysics(sf::Rect& hitbox, float& velocityX, float& velocityY);


// Registers the hitbox as collidable.

void registerEntity(sf::Rect& hitbox);

#endif
