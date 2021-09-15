#ifndef RECT_H_INCLUDED
#define RECT_H_INCLUDED

class Rect
{
private:
    /* data */
public:
    Rect(float x, float y, float w, float h);
    ~Rect();
    float x;
    float y;
    float w;
    float h;

    bool Contains(float x, float y);
};


#endif //RECT_H_INCLUDED