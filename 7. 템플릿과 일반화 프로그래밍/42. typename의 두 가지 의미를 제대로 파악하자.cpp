#include <iostream>
#include <vector>
#include <type_traits>

using namespace std;

/*
 * typename의 두 가지 의미를 제대로 파악하자
 */

// 클래스만 올 때는 class
template <class T>
class Button;
// 모든 타입이 올 때는 typename
template <typename T>
class Widget;

template <typename T>
void Func()
{
    // 비의존 이름 (Non-dependent or Independent name)
    int value = 0;
    // 의존 이름 (Dependent name)
    vector<T> vec;
    /* 중첩 의존 이름 (Nested dependent name)
     * 
     * 컴파일러는 typename 키워드를 붙여주지 않는 한,
     * 중첩 의존 이름이 타입이라고 가정하지 않는다. */
    typename T::const_iterator iter;
};

template <typename T>
class Base
{
public:
    class Nested
    {
    public:
        Nested(int x) {}
    };
};

template <typename T>
// 1. Base 클래스 목록에 있거나
class Derived : public Base<T>::Nested
{
    // 2. 멤버 이니셜라이저 리스트에 있을 때는, 용도가 명확하므로 쓰지 않아도 된다.
    Derived(int x) : Base<T>::Nested(x)
    {
        // 여기서는 써 줘야 한다.
        typename Base<T>::Nested temp;
    }
};

template <typename IterT>
void workWithIterator(IterT iter)
{
    typedef typename iterator_traits<IterT>::value_type value_type;
}

int main(int argc, char* argv[])
{
    

    return 0;
}
