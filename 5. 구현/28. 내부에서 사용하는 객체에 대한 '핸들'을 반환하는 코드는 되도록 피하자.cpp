#include <iostream>

using namespace std;

/*
 * 내부에서 사용하는 객체에 대한 '핸들'을 반환하는 코드는 되도록 피하자
 * 
 * 레퍼런스, 포인터, 반복자 등 핸들에 상관 없이, 멤버 함수가 상수 객체인지도 상관 없이
 * 내부 멤버의 핸들을 반환하는 함수는 위험하다.
 * 
 * [] 연산자 오버로딩 등 실제로 유용하게 쓰이므로
 * 위험하다는 거지 절대로 쓰지 말라는 것은 아니다.
 */

class Point
{
    int x;
    int y;

public:
    Point(int x, int y) : x(x), y(y) {}

    void setX(int newX) { x = newX; }
    void setY(int newY) { y = newY; }
};

struct RectData
{
    Point ulhc;
    Point lrhc;

    RectData(int ulx, int uly, int lrx, int lry) : ulhc(ulx, uly), lrhc(lrx, lry) {}
};

class Rectangle
{
    shared_ptr<RectData> pData;

public:
    Rectangle(int ulx, int uly, int lrx, int lry) : pData(make_shared<RectData>(ulx, uly, lrx, lry)) {}

    /* 잘못된 설계
     * 읽기 전용인 const 멤버 함수에서 읽기/쓰기가 가능한 레퍼런스를 반환
     *
     * 레퍼런스, 포인터, 반복자 등 핸들을 반환하는 함수는
     * 객체의 캡슐화를 무너뜨릴 수 있다. */
    Point& upperLeft()  const { return pData->ulhc; }

    /* 조금은 더 나은 설계
     * 핸들을 반환하되, 읽기만 가능한 상수 객채로 반환
     *
     * 캡슐화가 조금 저하되긴 했지만, 원래 Point 에 접근하는 것을 알고 시작한 설계이기 때문에
     * 여기서는 의도적인 완화라고 볼 수 있다. */
    const Point& lowerRight() const { return pData->lrhc; }
};

const Rectangle boundingBox()
{
    return Rectangle(5, 6, 7, 8);
}

int main(int argc, char* argv[])
{
    const Rectangle cRect(1, 2, 3, 4);

    // 잘못된 설계로 인해 상수 객체의 값 변경이 가능
    cRect.upperLeft().setX(50);

    // 소멸한 임시 객체의 멤버를 가리키는 Dangling 포인터가 된다.
    const Point* pUpperLeft = &(boundingBox().upperLeft());

    return 0;
}
