#include <SFML/Graphics.hpp>

#ifndef ___CL_PHYSICS
#define ___CL_PHYSICS

// Applies physics (gravity, collisions, motion) to an entity.

void doPhysics(sf::Rect<double>& hitbox, double& velocityX, double& velocityY);


// Registers the hitbox as collidable.

void registerEntity(sf::Rect<double>& hitbox);

#endif
