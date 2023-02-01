#ifndef BULLET_H_INCLUDED
#define BULLET_H_INCLUDED

#include "Component.h"
#include "Vec2.h"

class Bullet : public Component
{
private:

    Vec2 speed;
    float distanceLeft;
    int damage;
    
public:
    Bullet(GameObject& associated, float angle, float speed, int damage, float maxDistance, std::string sprite, int frameCount, float frameTime, bool targetsPlayer );
    bool targetsPlayer;

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    int GetDamage();
    void NotifyCollision(GameObject &other);
};


#endif //BULLET_H_INCLUDED