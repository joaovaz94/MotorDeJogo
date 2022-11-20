#ifndef CAMERAFOLLOWER_H_INCLUDED
#define CAMERAFOLLOWER_H_INCLUDED

#include "Component.h"

class CameraFollower: public Component {
    private:


    public:

        CameraFollower(GameObject &go);
        ~CameraFollower();

        void Update(float dt);
        void Render();
        bool Is(std::string type);
};


#endif //CAMERAFOLLOWER_H_INCLUDED