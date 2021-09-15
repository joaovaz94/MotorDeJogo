#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

class Vec2
{
private:
    /* data */
public:
    Vec2(float x, float y);
    ~Vec2();

    float x;
    float y;

    void GetRotated(float rad);
};


#endif //VEC2_H_INCLUDED