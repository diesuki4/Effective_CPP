#include <iostream>
#include <vector>

using namespace std;

/*
 * std 네임스페이스에 새로운 템플릿을 추가하는 건 금지되어 있다
 */

// 만약 클래스가 아닌, 클래스 템플릿이라면?
template <typename T>
class WidgetImpl
{
    T a, b, c;
    vector<double> v;

public:
    WidgetImpl() : a(), b(), c(), v() { }
};

// 클래스 템플릿
template <typename T>
class Widget
{
    WidgetImpl<T>* pImpl;

public:
    Widget() : pImpl(new WidgetImpl<T>)
    {

    }

    Widget(const Widget& rhs)
    : pImpl(new WidgetImpl<T>(*rhs.pImpl))
    {
        cout << "Widget::복사 생성자" << endl;
    }

    Widget& operator= (const Widget& rhs)
    {
        *pImpl = *rhs.pImpl;

        cout << "Widget::복사 대입 연산자" << endl;

        return *this;
    }

    void swap(Widget& other)
    {
        using std::swap;

        swap(pImpl, other.pImpl);
    }

    ~Widget()
    {
        delete pImpl;
    }
};

namespace std
{
    // 함수 템플릿은 부분 특수화 대신, 오버로드를 사용해야 한다.
    template <typename T>
    // void swap<Widget<T>>(Widget<T>& a, Widget<T>& b)
    void swap(Widget<T>& a, Widget<T>& b)
    {
        a.swap(b);

        cout << "std::swap<T>(Widget<T>&, Widget<T>&)" << endl;
    }

    /*
     * 그런데 컴파일도 실행도 잘 되지만,
     * 이렇게 사용하는 건 사실 안 된다.
     * 
     * std 구성요소에 대해서는
     * 
     * template <>
     * void swap<int>(int& a, int& b)
     * 
     * 같은 완전 특수화는 가능하지만,
     * 
     * template <typename T>
     * void swap(Widget<T>& a, Widget<T>& b)
     * 
     * 이렇게 새로운 템플릿(위에서는 swap() 의 오버로드 함수)
     * 을 추가하는 건 금지다.
     * 
     * 잘 작동하더라도 Undefined behavior 로 이어질 수 있다.
     */
}

int main(int argc, char* argv[])
{
    Widget<int> w1, w2;

    swap(w1, w2);

    return 0;
}
