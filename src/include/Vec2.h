#ifndef VEC2_H_INCLUDED
#define VEC2_H_INCLUDED

#include <string>

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

    std::string toStr();

    Vec2 GetRotated(float rad);
    float GetMagnitude();
    Vec2 Normalize();
    float DistanciaDoVetor(Vec2 &vetor);
    float AnguloParaAlvo(Vec2 &vetor);
    float atan();
    Vec2 RotateAroundVec(Vec2 &vetor, float rad);


    Vec2 operator+(Vec2 const &vetor);
    Vec2 operator+=(Vec2 const &vetor); 
    Vec2 operator-(Vec2 const &vetor);
    Vec2 operator-=(Vec2 const &vetor); 
    Vec2 operator*(float num);
    Vec2 operator/(float num);
    
    static inline float Dot(const Vec2& a, const Vec2& b) {
			return a.x * b.x + a.y * b.y;
    }

	static inline Vec2 Rotate(const Vec2& p, float angle) {
			float cs = std::cos(angle), sn = std::sin(angle);
			return Vec2 ( p.x * cs - p.y * sn, p.x * sn + p.y * cs );
	}
};


#endif //VEC2_H_INCLUDED