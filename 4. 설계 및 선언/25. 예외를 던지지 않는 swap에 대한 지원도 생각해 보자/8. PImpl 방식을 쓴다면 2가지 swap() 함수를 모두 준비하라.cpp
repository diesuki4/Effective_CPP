#include <iostream>
#include <vector>

using namespace std;

/*
 * PImpl 방식을 쓴다면 2가지 swap() 함수를 모두 준비하라
 * 
 * 1. 동일한 네임스페이스의 swap() 함수
 * (같은 이름일 뿐, std::swap() 의 오버로드가 아님)
 * 
 * 2. std::swap() 의 완전 특수화
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

        /*
         * PImpl 포인터를 빠르게 바꾸는 멤버 함수는
         * 필수로 구현해야 한다.
         */
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
     * 1 순위로 찾아진다.
     * 
     * 같은 네임스페이스에 있기 때문.
     * 
     * std::swap() 의 오버로드가 아니다.
     */
    template <typename T>
    void swap(Widget<T>& a, Widget<T>& b)
    {
        a.swap(b);

        cout << "WidgetStuff::swap<T>(Widget<T>&, Widget<T>&)" << endl;
    }

    template <typename T>
    void WidgetFunc(T& a, T& b)
    {
        cout << "어떤 작업" << endl;

        /*
         * std::swap 을 끌어와 후순위에 두어
         * 
         * 마땅한 함수가 없을 때 사용할 수 있다.
         */
        using std::swap;

        swap(a, b);
    }
}

/*
 * 2 순위로 찾아진다.
 * 
 * std::swap() 의 완전 특수화이기 때문.
 * 
 * 만약, std::swap() 의 완전 특수화를 작성하지 않은 상태에서
 * 1 순위를 작성해놓고는 std::swap() 으로 잘못 호출하면,
 * 
 * 표준 std::swap<T>(T& a, T& b) 가 호출된다.
 * 
 * 이때 2 순위 완전 특수화를 작성 해놓았다면
 * 이런 실수에도 대처할 수 있다.
 */
namespace std
{
    using namespace WidgetStuff;

    template <>
    void swap<Widget<float>>(Widget<float>& a, Widget<float>& b)
    {
        a.swap(b);

        cout << "std::swap<Widget<float>>(Widget<float>&, Widget<float>&)" << endl;
    }
}

/*
 * 3 순위로 찾아진다.
 * 
 * 표준 std::swap<T>(T& a, T& b)
 */

int main(int argc, char* argv[])
{
    using namespace WidgetStuff;

    Widget<float> w1, w2;

    /*
     * 1. WidgetStuff::swap<T>(Widget<T>&, Widget<T>&)
     * 2. std::swap<Widget<float>>(Widget<float>&, Widget<float>&)
     * 3. 표준 std::swap<T>(T& a, T& b)
     */
    WidgetFunc(w1, w2);

    return 0;
}
