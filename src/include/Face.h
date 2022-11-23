#ifndef FACE_H_INCLUDED
#define FACE_H_INCLUDED

#include "Component.h"
#include "InputManager.h"

class Face : public Component {
    private:

        int hitpoints;

    public:

        Face(GameObject& associated);
        ~Face();

        std::string type = "Face";

        void Damage(int damage);

        void Update(float dt);
        void Render();
        bool Is(std::string type);

};


#endif //FACE_H_INCLUDED