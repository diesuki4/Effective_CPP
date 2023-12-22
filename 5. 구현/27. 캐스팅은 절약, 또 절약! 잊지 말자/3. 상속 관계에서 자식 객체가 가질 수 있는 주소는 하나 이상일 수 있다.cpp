#include <iostream>

using namespace std;

/*
 * 상속 관계에서 자식 객체가 가질 수 있는 주소는 하나 이상일 수 있다
 */

class Base { };
class Derived : public Base { };

class GrandMother { };
class Mother : virtual public GrandMother { };
class Father : virtual public GrandMother { };
class Child : public Mother, public Father { };

int main(int argc, char* argv[])
{
    Derived d;

    // Derived* => Base* 암시적 형 변환
    Base* pb = &d;

    /*
     * 이때, 두 포인터의 값이 같지 않을 때가 간혹 있다.
     *
     * 이런 경우에는 Base* 오프셋을 Derived* 에 적용해
     * 실제 Base* 주소를 구하는 동작이
     *
     * <런타임에 수행된다.>
     *
     * 부모-자식 상속 관계에서 자식 객체가 가질 수 있는 주소가
     * 하나 이상이 될 수 있다는 뜻이다.
     */
    cout << reinterpret_cast<int*>(&d) << endl;
    cout << reinterpret_cast<int*>(pb) << endl << endl;

    /*
     * 실제로는 다중 상속을 사용하면
     * 이런 현상이 생긴다.
     *
     * 단일 상속인 경우에도 간혹 발생하긴 한다.
     *
     * 따라서, C++ 에서는 데이터가 어떤 식으로
     * 메모리에 올라가 있을 것이라는
     * 섣부른 가정은 피해야 한다.
     *
     * 예를 들어, 어떤 객체의 주소를 char* 타입으로 바꿔서
     * 포인터끼리 비교하고 더하고 빼는 등의 산술연산을 하는 것은
     * Undefined behavior 로 빠질 가능성이 매우 높다.
     */
    Child c;

    GrandMother* pg = &c;
    Mother* pm = &c;
    Father* pf = &c;

    cout << reinterpret_cast<int*>(&c) << endl;
    cout << reinterpret_cast<int*>(pg) << endl;
    cout << reinterpret_cast<int*>(pm) << endl;
    cout << reinterpret_cast<int*>(pf) << endl;

    return 0;
}
