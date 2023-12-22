#include <iostream>

using namespace std;

/*
 * C++ 캐스팅의 종류
 */

class Base
{
public:
    virtual void show() { cout << "Base" << endl; }

    virtual ~Base() { }
};

class Derived : public Base
{
public:
    virtual void show() override { cout << "Derived" << endl; }
};

int main(int argc, char* argv[])
{
    // C-Style
    double d;
    int *p = (int*)&d;

    // 함수형
    int i = int(&d);

    /*
     * const_cast
     * 
     * 객체의 상수성을 제거하는 용도로 쓰인다.
     * 
     * 포인터나 레퍼런스만 가능하고
     * 값 타입에는 적용할 수 없다.
     */
    const Base b;
    Base* pb = const_cast<Base*>(&b);

    pb->show();

    /*
     * dynamic_cast
     * 
     * <안전한 다운캐스팅> 을 할 때 쓰인다.
     * 
     * 가상 함수를 하나라도 가진 다형적 클래스에서
     * 포인터와 실제 객체가 올바른 상속 관계에 있는지
     * 결정하는 작업에 쓰인다.
     * 
     * 런타임에 확인이 필요하므로, 비용이 높다.
     *
     * 컴파일러 중에는 클래스 이름을 strcmp() 로 비교해
     * 판단하는 경우도 있다.
     *
     * 올바른 상속 관계가 아니라면 nullptr 이 반환된다.
     */
    if (dynamic_cast<Derived*>(pb) == nullptr)
        cout << "올바른 상속 관계가 아님" << endl;

    /*
     * reinterpret_cast
     *
     * 포인터를 int 로 바꾸는 등의 포인터 관련
     * Low-level 캐스팅에 사용된다.
     * 
     * 주소값 디버깅 등 Low-level 코드 이외에는
     * 거의 사용할 일이 없다.
     */
    cout << reinterpret_cast<int*>(pb) << endl;

    /*
     * static_cast
     *
     * 암시적 변환을 강제로 수행할 때 사용한다.
     * 
     * 기본 타입 간 변환
     * void* 변환
     * 비상수 객체를 상수 객체로 변환
     * 부모-자식 상속 관계 간 변환
     * (dynamic_cast 와 달리, 올바른 상속 관계가 아닐 경우 Undefined behavior 가 된다.)
     */
    float f = static_cast<float>(i);
    void* pv = static_cast<void*>(pb);

    // 호출 불가
    // static_cast<const Base*>(pb)->show();
    
    // Undefined behavior
    static_cast<Derived*>(pb);

    return 0;
}
