#include <iostream>

using namespace std;

/*
 * Name hiding
 *
 * 이름에 관한 것이므로
 * 가상, 비가상, 변수, 열거형, 중첩 클래스, using 등
 * 종류에 상관 없이 일어난다.
 *
 * 이것은 멀리 떨어진 Base 클래스로부터 오버로드 버전을 상속시키는 경우를
 * 실수로 간주하게 막겠다는 것이다.
 *
 * 엄연히 따지면 부모의 모든 것을 물려 받는다는
 * public 상속 = Is-A 관계의 위반이다.
 */

// 전역 Scope
int x;

void SomeFunc()
{   // SomeFunc Scope
    double x;

    // SomeFunc 의 x 가 전역 x 를 가린다.
    cin >> x;
}

class Base
{   // Base Scope
    int x;

public:
    virtual void mf1() = 0;
    virtual void mf1(int) {}
    virtual void mf2()    {}
    void mf3()            {}
    void mf3(double)      {}
};

class DerivedPublic : public Base
{   // Base Scope 내부에 중첩된 DerivedPublic Scope
public:
    using Base::mf3;

    void mf1() override {}
    void mf3()          {}
    void mf4()
    {   // mf4 Scope
        // mf4 => DerivedPublic => Base => 전역 순으로 탐색한다.
        mf2();
    }
};

/* 기본 클래스의 모든 것을 상속 받고 싶지는 않은 경우도 있다.
 * 이때는 모든 것을 받지 않기 때문에 public 상속은 쓸 수 없다.
 * 
 * 이렇게 상속 받은 함수들 중 외부에 일부만 공개하고 싶을 때
 * private 상속을 쓴다. */
class DerivedPrivate : private Base
{   // Base Scope 내부에 중첩된 DerivedPrivate Scope
public:
    /* using 을 쓰면 모든 mf1 의 오버로드가 공개된다.
    using Base::mf1;*/

    /* 전달 함수(Forwarding function) 를 만들어
     * 하나의 mf1 버전만 외부에 공개한다. */
    void mf1() override { Base::mf1(); }
};

int main(int argc, char* argv[])
{
    DerivedPublic dpbc;

    dpbc.mf1();
    /* 부모의 mf1(int) 가 가려짐
    dpbc.mf1(5); */

    dpbc.mf2();

    dpbc.mf3();
    /* 부모의 mf3 오버로드 버전들을 using 선언으로 끌고 왔다. */
    dpbc.mf3(5.0);

    DerivedPrivate dprv;

    /* private 상속과 전달 함수를 통해
     * 하나의 mf1 버전만 외부에 공개 */
    dprv.mf1();
    // dprv.mf1(5);

    return 0;
}
