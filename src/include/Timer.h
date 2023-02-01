#ifndef TIMER_H_INCLUDED
#define TIMER_H_INCLUDED

class Timer
{
private:
    float time;
public:
    Timer();

    void Update(float dt);
    void Restart();
    float Get();
};

#endif //TIMER_H_INCLUDED