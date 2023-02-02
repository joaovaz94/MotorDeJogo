#ifndef TITLESTATE_H_INCLUDED
#define TITLESTATE_H_INCLUDED

#include "State.h"

class TitleState : public State
{
public:

    TitleState();
    ~TitleState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();
};



#endif //TITLESTATE_H_INCLUDED