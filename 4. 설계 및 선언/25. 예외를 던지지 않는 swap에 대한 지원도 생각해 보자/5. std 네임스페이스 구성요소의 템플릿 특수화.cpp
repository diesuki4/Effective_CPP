#include <iostream>
#include <vector>

using namespace std;

/*
 * std 네임스페이스 구성요소의 완전 템플릿 특수화
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
    WidgetImpl* pImpl;

public:
    Widget() : pImpl(new WidgetImpl)
    {

    }

    Widget(const Widget& rhs) : pImpl(new WidgetImpl(*rhs.pImpl))
    {
        cout << "Widget::복사 생성자" << endl;
    }

    Widget& operator= (const Widget& rhs)
    {
        *pImpl = *rhs.pImpl;

        cout << "Widget::복사 대입 연산자" << endl;

        return *this;
    }

    /*
     * 하지만, pImpl 방식인 이 클래스에서는
     * 포인터가 가리키는 실제 객체까지 복사하며
     * 교환할 필요는 없다.
     * 
     * 단순히 포인터만 교환해도 될 터.
     * 
     * 따라서, std::swap<Widget>() 템플릿 특수화 함수에서
     * 사용하기 위한 포인터 교환 swap() 함수를 제공한다.
     * 
     * 캡슐화 관점에서 friend 선언은 좋지 않다.
     */
    void swap(Widget& other)
    {
        /*
         * std::swap 을 끌어와 후순위에 둔다.
         *
         * 1 순위인 현재 함수 뒤에 2 순위로 찾아진다.
         */
        using std::swap;

        swap(pImpl, other.pImpl);
    }

    ~Widget()
    {
        delete pImpl;
    }
};

/*
 * std 네임스페이스를 그대로 사용한다.
 * 
 * 일반적으로 std 네임스페이스의 구성요소는 함부로 변경할 수 없지만,
 * 
 * 사용자 정의 타입에 대한 템플릿 특수화는 허용된다.
 */
namespace std
{
    /*
     * 완전 템플릿 특수화 (Total Template Specialization)
     * 
     * std::swap() 이 Widget 타입에 대해서는
     * 아래 함수로 동작하도록 한다.
     */
    template <>
    void swap<Widget>(Widget& a, Widget& b)
    {
        // 임시 객체 없이, 단순히 포인터만 교환하도록 한다.
        a.swap(b);

        cout << "std::swap<Widget>(Widget&, Widget&)" << endl;
    }
}

int main(int argc, char* argv[])
{
    Widget w1, w2;

    swap(w1, w2);

    return 0;
}
