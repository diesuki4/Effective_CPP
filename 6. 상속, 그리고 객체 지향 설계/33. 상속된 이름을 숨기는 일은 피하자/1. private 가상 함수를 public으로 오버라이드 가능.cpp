/*
 * https://stackoverflow.com/questions/2170688/private-virtual-method-in-c#answer-2170696
 */
#include <iostream>

using namespace std;

/*
 * private 가상 함수를 public으로 오버라이드 가능
 */

class Base
{
private:
    virtual void print() {}
};

class Derived : public Base
{
/* 이런 동작은 버그가 아니라,
 * 오버라이드라는 개념에 접근 레벨도 포함하기 위한
 *
 * 의도적인 허용이라고 한다. */
public:
    void print() override {}
};

int main(int argc, char* argv[])
{
    Base b;
    Derived d;

    // b.print();
    d.print();

    return 0;
}
