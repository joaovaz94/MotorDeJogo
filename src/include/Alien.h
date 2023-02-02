
#ifndef ALIEN_H_INCLUDED
#define ALIEN_H_INCLUDED

#include <queue>

#include "Component.h"
#include "GameObject.h"
#include "Timer.h"
#include "Sound.h"

class Alien : public Component{
    private:
        
        Vec2 speed;
        int hp;
        int qtdMinions;

        std::vector <std::weak_ptr<GameObject>> minionArray;

        enum AlienState { MOVING, RESTING};
        AlienState state;
        Timer restTimer;
        Vec2 destination;

    public:

        Alien(GameObject &associated, int nMinions);
        ~Alien();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
        int GetMinionProximo(Vec2 posTiro);
        void NotifyCollision(GameObject &other);

        static int alienCount;
};


#endif //ALIEN_H_INCLUDED