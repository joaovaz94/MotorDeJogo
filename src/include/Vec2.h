#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

class Vec2
{
private:
    /* data */
public:
    Vec2(float x, float y);
    ~Vec2() {}

    float x;
    float y;

    Vec2 GetRotated(float rad);

    Vec2 operator+(Vec2 const &vetor);
};


#endif //VEC2_H_INCLUDED