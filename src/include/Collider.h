
#ifndef COLLIDER_H_INCLUDED
#define COLLIDER_H_INCLUDED

#include "Component.h"
#include "GameObject.h"

class Collider : public Component
{
private:
    Vec2 scale;
    Vec2 offset;
public:
    Collider(GameObject &associated, Vec2 scale = {1,1}, Vec2 offset = {0,0});

    Rect box;

    void Update(float dt);
    void Render();
    bool Is(std::string type);
    void SetScale(Vec2 scale);
    void SetOffset(Vec2 offset);
};

#endif //COLLIDER_H_INCLUDED