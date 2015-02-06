#include "Physics.h"
#include "Constants.h"
#include <SFML/Graphics.hpp>
#include <vector>

std::vector< sf::FloatRect * > activeWorldHitboxes;

inline float sq(float f)
{
   return f*f;
}

inline float min(float f1,  float f2)
{
   return f1>f2 ? f2  : f1;
}

//Start with dumb algorithm for now, will replace if causes lag
void doPhysics(sf::FloatRect& hitbox, float& velocityX, float& velocityY)
{
   static const int STEPS=20;

   float stepX=velocityX/STEPS;
   float stepY=velocityY/STEPS;

   for(int i=0; i<STEPS; i++)
   {
      for(int i=0; i< activeWorldHitboxes.size(); i++)
      {
         sf::FloatRect * checking=activeWorldHitboxes[i];
         if( checking -> intersects(hitbox))
         {
            float leastDiffX=min(
                  sq(checking -> top - hitbox.top),
                  sq(checking -> top + checking -> height - (hitbox.top + hitbox.height))
            );
            float leastDiffY=min(
                  sq(checking -> left - hitbox.left),
                  sq(checking -> left + checking -> width - (hitbox.left + hitbox.width))
            );
            if(leastDiffX>leastDiffY)
            {
               stepX=0;
            }
            else
            {
               stepY=0;
            }
            if(stepX==0 && stepY==0)
              return; //stuck
         }
      }
      hitbox.left+=stepX;
      hitbox.top+=stepY;
   }
}

void registerEntity(sf::FloatRect& hitbox)
{
   activeWorldHitboxes.insert(activeWorldHitboxes.end(), & hitbox);
}

void clearHitboxes()
{
   activeWorldHitboxes.clear();
}
