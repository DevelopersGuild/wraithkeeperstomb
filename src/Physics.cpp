#include "Physics.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>

std::vector< sf::FloatRect > activeWorldHitboxes;

void doPhysics(sf::FloatRect& hitbox, float& velocityX, float& velocityY)
{
   
   for(int i=0; i<activeWorldHitboxes.size(); i++)
   {
      
   }
}

void registerEntity(sf::FloatRect& hitbox)
{
   activeWorldHitboxes.insert(activeWorldHitboxes.end(), hitbox);
}

void clearHitboxes()
{
   activeWorldHitboxes.clear();
}
