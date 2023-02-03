#ifndef ENDSTATE_H_INCLUDED
#define ENDSTATE_H_INCLUDED

#include "State.h"
#include "Music.h"

class EndState : public State
{
public:

    EndState();
    ~EndState();

    void LoadAssets();
    void Update(float dt);
    void Render();

    void Start();
    void Pause();
    void Resume();

private:
    Music *backgrounMusic;
};



#endif //ENDSTATE_H_INCLUDED