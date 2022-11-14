
#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <string>

//class Component;
class GameObject;

#include "GameObject.h"

class Component
{
    private:
        /* data */
    
    public:

        Component(GameObject& associated);
        virtual ~Component() {}

        std::string type;
        void virtual Update(float dt) = 0;
        void virtual Render() = 0;
        bool virtual Is(std::string type) = 0;
    
    protected:

        GameObject& associated;
};




#endif //COMPNENT_H_INCLUDED