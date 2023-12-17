#include <iostream>

using namespace std;

/*
 * 기본 타입처럼 일관성 있게 설계하라
 */

class Widget
{
    int data;

public:
    Widget(int data) : data(data) { }

    /*
     * Widget operator* (const Widget& rhs) { return Widget(data * rhs.data); }
     * 
     * 객체는 값 타입을 반환하게 되면 대입이 가능해진다.
     * 
     * if (a*b = c) 로 잘못 쓰여질 수 있다.
     */

    /*
     * 반환 값에 const 를 붙여 사용자의 실수를 막을 수 있다.
     * 
     * if (a*b = c) 와 같이 작성 불가
     */
    const Widget operator* (const Widget& rhs) { return Widget(data * rhs.data); }

    /*
     * 클래스를 설계할 때, 마땅한 이유가 없다면
     * 기본 타입처럼 동작하게 만드는 것이 가장 좋다.
     * 
     * int 타입에서 if (a*b = c) 가 동작하지 않는 것처럼.
     * 
     * 일관성 있는 인터페이스만큼 제대로 쓰기 좋은 것이 없기 때문이다.
     */

    operator bool() const
    {
        return (data != 0);
    }
};

int main(int argc, char* argv[])
{

    return 0;
}
