#include <iostream>

using namespace std;

/*
 * 상속을 염두하지 않았다면 가상 소멸자를 쓰지 마라
 * 
 * 상속을 염두했다면,
 * 소멸자라도 가상 소멸자로 만들어서 다형적 클래스로 만들어라.
 */

class Point
{
    int x;
    int y;

public:
    Point(int x, int y) : x(x), y(y) { }
    ~Point() { }

    /*
     * 가상 소멸자도 가상 함수다.
     * 
     * 가상 함수가 1개라도 존재하는 다형적 클래스가 되는 순간,
     * 클래스에는 가상 함수 테이블 포인터(vptr) 가 추가된다.
     * 
     * vptr 은 가상 함수 테이블(vtbl) 을 가리키게 된다.
     * 
     * 다형적 클래스에서는 가상 함수 호출을 위해 vtbl 을 참조해야 하기 때문에,
     * C++이 C보다 느리다고 불리는 이유 중 하나이다.
     */

    /*
     * 이 클래스에 가상 소멸자를 넣지 않는다면
     * 크기가 8바이트가 되어 x64 레지스터에 딱 들어가겠지만,
     * 
     * 가상 소멸자로 선언하는 순간 16바이트(x64는 포인터가 8바이트) 가 되어
     * 레지스터에 들어갈 수 없게 된다.
     */

    /*
     * 또, C언어 같은 다른 언어에서 동일한 배치로 데이터를 배치했다고 해도
     * vtbl 을 어떻게 할 수 없기 때문에 호환성도 떨어지게 된다.
     */
};

// 좋지 않은 설계
class PointBadPoly
{
    int x;
    int y;

public:
    PointBadPoly(int x, int y) : x(x), y(y) { }
    virtual ~PointBadPoly() { }
};

int main(int argc, char* argv[])
{
    cout << sizeof(Point) << endl;
    cout << sizeof(PointBadPoly) << endl;

    return 0;
}
