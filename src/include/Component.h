
#ifndef COMPONENT_H_INCLUDED
#define COMPONENT_H_INCLUDED

#include <string>

class Component;

#include "GameObject.h"

class Component
{
    private:
        /* data */
    
    public:

        Component(GameObject& associated);
        virtual ~Component();

        virtual void Update() = 0;
        virtual void Render() = 0;
        virtual bool Is(std::string type) = 0;
    
    protected:

        GameObject& associated;
};




#endif //COMPNENT_H_INCLUDED