#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

class Vec2
{
private:
    /* data */
public:
    Vec2(float x, float y);
    Vec2();
    ~Vec2() {}

    float x;
    float y;

    Vec2 GetRotated(float rad);
    float GetMagnitude();
    Vec2 Normalize();
    float DistanciaDoVetor(Vec2 &vetor);

    Vec2 operator+(Vec2 const &vetor);
    Vec2 operator-(Vec2 const &vetor);
    Vec2 operator*(float num);
    Vec2 operator/(float num);
};


#endif //VEC2_H_INCLUDED