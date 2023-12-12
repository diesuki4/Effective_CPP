#include <iostream>

using namespace std;

/*
 * 멤버의 초기화 순서는 선언된 순서이다
 */

// 부모 클래스가 먼저 초기화된다.
class Base
{
    // 멤버의 초기화 순서 = 선언된 순서
    string theName;     // (1)
    string theAddress;  // (2)

public:
    Base(const string& name, const string& address)
    : theName(name), theAddress(address) { }
};

// 자식은 부모 다음으로 초기화된다.
class Derived : public Base
{
    string thePhone;        // (3)
    int numTimesConsulted;  // (4)

public:
    // 멤버 이니셜라이저에서의 순서는 관계 없지만,
    // 그래도 선언 순서와 동일하게 맞춰주자.
    Derived(const string& name, const string& address, const string& phone)
    : Base(name, address), thePhone(phone), numTimesConsulted(0) { }
};

int main(int argc, char* argv[])
{


    return 0;
}
