#include <iostream>
#include <vector>

using namespace std;

/*
 * std가 아닌 네임스페이스로 묶기
 */

namespace WidgetStuff
{
    template <typename T>
    class WidgetImpl
    {
        T a, b, c;
        vector<double> v;

    public:
        WidgetImpl() : a(), b(), c(), v() { }
    };

    template <typename T>
    class Widget
    {
        WidgetImpl<T>* pImpl;

    public:
        Widget() : pImpl(new WidgetImpl<T>)
        {

        }

        Widget(const Widget& rhs) : pImpl(new WidgetImpl<T>(*rhs.pImpl))
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

    /*
     * 함수는 부분 특수화가 안 돼서 오버로드 함수를 추가했더니,
     * std 네임스페이스에는 새로운 템플릿을 추가할 수 없다고 한다.
     *
     * 그럼 방법은 std 네임스페이스가 아닌
     * 다른 네임스페이스에 추가하면 된다.
     *
     * 그래서 현재 Widget 과 관련된 클래스와 swap() 함수를
     * WidgetStuff 라는 네임스페이스로 묶었다.
     *
     * 이렇게 하면, 컴파일러는 현재 네임스페이스에서
     * 우선적으로 swap() 함수를 찾을 것이다.
     *
     * 아래 있는 swap() 함수는 std::swap() 의 오버로드가 아님에 주의한다.
     */
    template <typename T>
    void swap(Widget<T>& a, Widget<T>& b)
    {
        a.swap(b);

        cout << "WidgetStuff::swap<T>(Widget<T>&, Widget<T>&)" << endl;
    }
}

int main(int argc, char* argv[])
{
    using namespace WidgetStuff;

    Widget<int> w1, w2;

    // WidgetStuff::swap<T>(Widget<T>&, Widget<T>&)
    swap(w1, w2);

    return 0;
}
