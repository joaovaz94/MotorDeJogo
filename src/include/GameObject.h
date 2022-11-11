#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Component.h"
#include <string>
#include <vector>
#include "Rect.h"

class GameObject
{
    private:
        /* data */
        std::vector<Component*> components;
        bool isDead;

    public:
        GameObject();
        ~GameObject();

        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);

        Rect box;
};


#endif //GAMEOBJECT_H_INCLUDED