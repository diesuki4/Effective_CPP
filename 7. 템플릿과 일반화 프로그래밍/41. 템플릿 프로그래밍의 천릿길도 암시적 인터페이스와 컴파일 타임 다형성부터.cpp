#include <iostream>

using namespace std;

/*
 * 템플릿 프로그래밍의 천릿길도 암시적 인터페이스와 컴파일 타임 다형성부터
 * 
 * 정적(컴파일 타임) 다형성
 * - 함수 오버로딩
 * - 템플릿
 * 
 * 동적(런타임) 다형성
 * - 가상 함수
 */

class Widget
{
public:
    Widget() {}

    virtual size_t size() const { return 10; }
    virtual void normalize() const {}

    void swap(Widget& other) {}
    bool operator!= (const Widget& rhs) { return true; }

    virtual ~Widget() {}
};

Widget someWidget;

/* 일반 함수는 타입의 인터페이스에 따라 함수를 작성하면 된다.
 * 이 때의 중점은 함수의 시그니처다. */
void doProcessing(Widget& w)
{
    if (10 < w.size() && w != someWidget)
    {
        Widget temp(w);
        // 소스 코드에 명시적으로 드러나는 명시적 인터페이스
        temp.normalize();
        // virtual 함수이므로 런타임 다형성
        temp.swap(w);
    }
}

Widget someT;

/* 함수 템플릿은 함수 내용에 따라 타입의 인터페이스를 작성해줘야 한다.
 * 이 때의 중점은 본문의 표현식이다. */
template <typename T>
void doProcessingT(T& t)
{
    if (10 < t.size() && t != someT)
    {
        T temp(t);
        // 컴파일을 위해 T 타입이 지원해야 하는 암시적 인터페이스
        temp.normalize();
        /* 템플릿은 컴파일 타임에 인스턴싱되는데, 이때 타입에 따라
         * 호출되는 함수가 달라지기 때문에 컴파일 타임 다형성이라고 한다. */
        temp.swap(t);
    }
}

int main(int argc, char* argv[])
{
    

    return 0;
}
