#ifndef PENGUINBODY_H_INCLUDED
#define PENGUINBODY_H_INCLUDED

#include "Component.h"
#include "GameObject.h"

class PenguinBody : public Component
{
private:
    std::weak_ptr< GameObject > pcannon;
    Vec2 speed;
    float linearSpeed;
    float angle;
    int hp;

public:

    static PenguinBody *player;
    PenguinBody(GameObject &associated);
    ~PenguinBody();

    void Start();
    void Update(float dt);
    void Render();
    bool Is(std::string type);

};

#endif //PENGUINBODY_H_INCLUDED