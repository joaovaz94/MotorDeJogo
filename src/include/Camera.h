#ifndef CAMERA_H_INCLUDED
#define CAMERA_H_INCLUDED

#include "GameObject.h"
#include "Vec2.h"
#include "InputManager.h"

class Camera
{
    private:

        static GameObject *focus;
        
    public:

        Camera();
        ~Camera();

        static void Follow(GameObject *newFocus);
        static void Unfollow();
        static void Update(float dt);
        static void Reset();

        static Vec2 pos;
        static Vec2 speed;
};




#endif //CAMERA_H_INCLUDED