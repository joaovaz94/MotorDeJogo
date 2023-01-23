#ifndef PENGUINCANNON_H_INCLUDED
#define PENGUINCANNON_H_INCLUDED

#include "Component.h"
#include "GameObject.h"

class PenguinCannon : public Component
{
private:
    std::weak_ptr< GameObject > pbody;
    float angle;

public:
    PenguinCannon(GameObject &associated, std::weak_ptr< GameObject > penguinBody);
    ~PenguinCannon();

    void Update(float dt);
    void Render();
    bool Is(std::string type);

    void Shoot();
};

#endif //PENGUINCANNON_H_INCLUDED