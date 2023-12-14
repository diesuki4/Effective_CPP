#include <iostream>

using namespace std;

/*
 * 대입 연산자는 *this의 참조자를 반환하게 하자
 * 
 * 관례이므로 지키는 것이 좋다.
 */

class Widget
{
    float data;

public:
    Widget(float data = 0.F) : data(data) { }

    // 반환 형은 레퍼런스다.
    Widget& operator= (const Widget& rhs)
    {
        data = rhs.data;

        return *this;
    }

    /*
     * = 연산자 뿐만 아니라 +=, *=, /= 등
     * 모든 형태의 대입 연산자도 마찬가지다.
     */
    Widget& operator+= (const Widget& rhs)
    {
        data += rhs.data;

        return *this;
    }

    /*
     * 인자 타입이 일반적이지 않은 경우에도 마찬가지다.
     */
    Widget& operator+= (const int rhs)
    {
        data += rhs;

        return *this;
    }

    void Show() { cout << data << endl; }
};

int main(int argc, char* argv[])
{
    Widget x, y, z, w;

    // x = (y = (z = 3.F))
    x = y = z = 3.F;

    // (x += (y += z))
    x += y += z;

    (x += 5).Show();

    return 0;
}
