
#ifndef ALIEN_H_INCLUDED
#define ALIEN_H_INCLUDED

#include <queue>

#include "Component.h"
#include "GameObject.h"

class Alien : public Component{
    private:
        
        class Action {
            public:
                enum ActionType {
                    MOVE,
                    SHOOT
                };
                Vec2 pos;
                ActionType type;

                Action(ActionType type, float x, float y);
        };

        Vec2 speed;
        int hp;
        int qtdMinions;

        std::queue<Action> taskQueue;
        std::vector <std::weak_ptr<GameObject>> minionArray;

    public:

        Alien(GameObject &associated, int nMinions);
        ~Alien();

        void Start();
        void Update(float dt);
        void Render();
        bool Is(std::string type);
};


#endif //ALIEN_H_INCLUDED