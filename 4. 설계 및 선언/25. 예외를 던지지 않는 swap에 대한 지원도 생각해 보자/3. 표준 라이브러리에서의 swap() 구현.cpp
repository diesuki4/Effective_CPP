#include <iostream>
#include <vector>

using namespace std;

/*
 * 표준 라이브러리에서의 swap() 구현
 */

class Widget
{
    int a, b, c;
    vector<double> v;

public:
    Widget() : a(0), b(0), c(0), v()
    {
    
    }

    // 임시 객체 temp 를 만들 때 1번 호출
    Widget(const Widget& rhs)
    : a(rhs.a), b(rhs.b), c(rhs.c), v(rhs.v)
    {
        cout << "Widget::복사 생성자" << endl;
    }

    // 값을 복사하는 데 2번 호출
    Widget& operator= (const Widget& rhs)
    {
        a = rhs.a;
        b = rhs.b;
        c = rhs.c;
        v = rhs.v;

        cout << "Widget::복사 대입 연산자" << endl;

        return *this;
    }
};

namespace mystd
{
    // 의외로 꽤 비용이 든다.
    template <typename T>
    void swap(T& a, T& b)
    {
        T temp(a);  // 복사 생성자
        a = b;      // 복사 대입 연산자
        b = temp;   // 복사 대입 연산자

        cout << "mystd::swap<T>(T&, T&)" << endl;
    }
}

int main(int argc, char* argv[])
{
    Widget w1, w2;

    mystd::swap(w1, w2);

    return 0;
}
