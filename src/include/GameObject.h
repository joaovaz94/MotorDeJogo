#ifndef GAMEOBJECT_H_INCLUDED
#define GAMEOBJECT_H_INCLUDED

#include "Component.h"
#include <string>
#include <vector>
#include <memory>
#include "Rect.h"

class Component;

class GameObject
{
    private:
        /* data */
        std::vector<std::unique_ptr <Component>> components;
        bool isDead;

    public:
        GameObject();
        ~GameObject();

        void Start();
        void Update(float dt);
        void Render();
        bool IsDead();
        void RequestDelete();
        void AddComponent(Component* cpt);
        void RemoveComponent(Component* cpt);
        Component* GetComponent(std::string type);

        Rect box;
        bool started;
};


#endif //GAMEOBJECT_H_INCLUDED