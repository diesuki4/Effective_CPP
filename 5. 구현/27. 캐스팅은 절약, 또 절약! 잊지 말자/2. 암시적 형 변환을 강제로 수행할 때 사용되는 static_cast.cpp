#include <iostream>

using namespace std;

/*
 * 암시적 형 변환을 강제로 수행할 때 사용되는 static_cast
 */

class Widget
{
    int size;

public:
    explicit Widget(int size) : size(size) { }
};

void WidgetFunc(const Widget& w)
{
    return;
}

int main(int argc, char* argv[])
{
    /*
     * explicit 생성자로 인해, 암시적 형 변환이 불가
     * WidgetFunc(10);
     *
     * 생성자에 explicit 키워드가 없으면 가능하다.
     * 상수 레퍼런스에는 임시 값, 임시 객체를 담을 수 있기 때문.
     */

    /*
     * 함수형 캐스팅
     */
    WidgetFunc(Widget(10));

    /*
     * C++ Style 캐스팅 (선호)
     *
     * 이렇게 암시적 형 변환을 강제로 수행할 때,
     * static_cast 를 사용한다.
     */
    WidgetFunc(static_cast<Widget>(10));

    /*
     * 캐스팅은 그냥 컴파일러에게 알려주는 것이 아니라,
     * 
     * 런타임에 실행되는 코드가 만들어지는 경우도 많다.
     */
    int x = 1 , y = 3;

    /*
     * cvtsi2sd xmm3, dword ptr [ebp+24]
     * 
     * 같은 런타임에서 동작하는 캐스팅 코드가 만들어진다.
     */
    double d = static_cast<double>(x) / y;

    /*
     * 이것도 비용이기 때문에, 차라리 처음부터
     * double 로 선언하는 게 효율적이다.
     */
    double dx = 1.F;
    int iy = 3;

    double dd = dx / iy;

    return 0;
}
