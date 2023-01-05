#ifndef MINION_H_INCLUDED
#define MINION_H_INCLUDED

#include "Component.h"

class Minion : public Component
{
private:
    std::weak_ptr<GameObject> alienCenter;
    float arc;
public:
    Minion(GameObject& associated, std::weak_ptr<GameObject> alienCenter, float arcOffsetDeg = 0);
    ~Minion();
    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void Shoot(Vec2 target);
};



#endif //MINION_H_INCLUDED