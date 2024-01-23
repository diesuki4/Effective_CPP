#include <iostream>
#include <cassert>

using namespace std;

/*
 * 정사각형은 직사각형이다?
 */

class Rectangle
{
    int h;
    int w;

public:
    Rectangle(int h, int w) : h(h), w(w) {}

    virtual int height() const { return h; }
    virtual int width() const  { return w; }

    virtual void setHeight(int newH) { h = newH; }
    virtual void setWidth(int newW)  { w  = newW; }

    virtual ~Rectangle() {}
};

/* 아래는 좋은 설계가 아니다.
 * 
 * 직사각형의 성질 중 <가로, 세로가 다를 수 있다> 는 성질은
 * 정사각형에 적용할 수 없다.
 *
 * 이렇듯, public 상속은 부모 객체의 모든 속성이
 * 자식 객체에도 적용될 때만 사용해야 한다. */
class Square : public Rectangle
{
public:
    Square(int h, int w) : Rectangle(h, w) {}
};

// 직사각형의 너비를 늘리는 함수
void makeWiden(Rectangle& r, int addW)
{
    int oldH = r.height();

    r.setWidth(r.width() + addW);

    assert(r.height() == oldH);
}

int main(int argc, char* argv[])
{
    Square sq(10, 10);

    // 정사각형의 너비만 늘린다..?
    makeWiden(sq, 5);

    // 문제 발생
    assert(sq.height() == sq.width());

    return 0;
}
