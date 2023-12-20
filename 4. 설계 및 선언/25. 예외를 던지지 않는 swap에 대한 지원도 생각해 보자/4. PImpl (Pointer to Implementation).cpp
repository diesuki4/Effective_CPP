#include <iostream>
#include <vector>

using namespace std;

/*
 * PImpl (Pointer to Implementation)
 * 
 * 포인터를 활용해 선언부에서
 * 데이터 구현 세부를 감추는 방법이다.
 */

/*
 * 데이터 구현 세부는 보통
 * [클래스명]Impl 로 작성한다.
 */
class WidgetImpl
{
    int a, b, c;
    vector<double> v;

public:
    WidgetImpl() : a(0), b(0), c(0), v() { }
};

class Widget
{
    // 데이터 구현 세부가 감춰졌다.
    WidgetImpl* pImpl;

public:
    Widget() : pImpl(new WidgetImpl)
    {
    
    }

    Widget(const Widget& rhs)
    // swap() 호출을 비싸게 만드는 주원인 포인터
    : pImpl(new WidgetImpl(*rhs.pImpl))
    {
        cout << "Widget::복사 생성자" << endl;
    }

    Widget& operator= (const Widget& rhs)
    {
        // swap() 호출을 비싸게 만드는 주원인 포인터
        *pImpl = *rhs.pImpl;

        cout << "Widget::복사 대입 연산자" << endl;

        return *this;
    }

    ~Widget()
    {
        delete pImpl;
    }
};

namespace mystd
{
    template <typename T>
    void swap(T& a, T& b)
    {
        T temp(a);
        a = b;
        b = temp;

        cout << "mystd::swap<T>(T&, T&)" << endl;
    }
}

int main(int argc, char* argv[])
{
    Widget w1, w2;

    mystd::swap(w1, w2);

    return 0;
}
