#include "Physics.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>

std::vector<sf::Rect<double> > activeWorldHitboxes;

void doPhysics(sf::Rect<double>& hitbox, double& velocityX, double& velocityY)
{
   
   for(int i=0; i<activeWorldHitboxes.size(); i++)
   {
      
   }
}

void registerEntity(sf::Rect<double>& hitbox)
{
   activeWorldHitboxes.insert(activeWorldHitboxes.end(), hitbox);
}

void clearHitboxes()
{
   activeWorldHitboxes.clear();
}
