/*
 * https://ko.wikipedia.org/wiki/믹스인
 * https://en.wikibooks.org/wiki/More_C++_Idioms/Non-copyable_Mixin
 * https://www.boost.org/doc/libs/1_72_0/boost/core/noncopyable.hpp
 */
#include <iostream>

using namespace std;

/*
 * 비가상 함수는 재정의하지 말자
 *
 * 자식에서 구현을 재정의할 것이라면, 가상 함수로 만들어 오버라이드하자.
 */

class BaseDyn
{
public:
    // 가상 함수
    virtual void f() { cout << "BaseDyn" << endl; }

    virtual ~BaseDyn() {}
};

class DerivedDyn : public BaseDyn
{
public:
    // 가상 함수 오버라이드
    void f() override { cout << "DerivedDyn" << endl; }

    /* 다형적 클래스에서 소멸자를 virtual 로 만들어야 하는 이유도
     * 자식 클래스에서는 무조건 부모의 소멸자를 재정의하기 때문이다.
     *
     * (참고) 상속에서 소멸자를 virtual 로 선언하지 않아도 되는 경우
     * Boost::noncopyable 클래스처럼 부모의 인터페이스로 자식을 조작하려고 상속한 게 아닐 때
     *
     * 이때는 부모 인터페이스로 자식을 조작하지 않기 때문에, 부모에 가상 함수가 존재하지 않는다.
     *
     * 이렇게 부모로서가 아니라 어떤 속성, 특징, 사용할 수 있는 메서드를
     * 포함하기 위해 상속하는 경우를 믹스인(Mixin) 이라고 한다. */
    ~DerivedDyn() {}
};

class BaseStt
{
public:
    // 비가상 함수
    void f() { cout << "BaseStt" << endl; }
};

class DerivedStt : public BaseStt
{
public:
    // 비가상 함수 재정의
    void f() { cout << "DerivedStt" << endl; }
};

int main(int argc, char* argv[])
{
    /* 실제 객체에 따라, 런타임에 동적 바인딩이 진행된다. */
    BaseDyn* pBdyn = new DerivedDyn;
    pBdyn->f();   // DerivedDyn::f

    /* 런타임에 동적 바인딩 */
    DerivedDyn* pDdyn = new DerivedDyn;
    pDdyn->f();   // DerivedDyn::f

    delete pBdyn;
    delete pDdyn;

    /* 실제 객체에 상관 없이, 컴파일 타임에
     * 무조건 BaseStt 의 함수로 정적 바인딩이 진행된다. */
    BaseStt* pBstt = new DerivedStt;
    pBstt->f();   // BaseStt::f

    /* 컴파일 타임에 무조건 DerivedStt 의 함수로 정적 바인딩
     *
     * 1. public 상속은 Is-A 관계를 뜻한다.
     * 2. 비가상 함수는 자식에 관계없는 불변동작을 정의한다.
     *
     * 자식에서 비가상 함수를 재정의 해버리면, Derived 는 Base 일종(Is-A) 이 아니게 된다.
     * 재정의된 함수로 인해 불변동작이 다르게 동작하도록 바뀌었기 때문. */
    DerivedStt* pDstt = new DerivedStt;
    pDstt->f();   // DerivedStt::f

    delete pBstt;
    delete pDstt;

    return 0;
}
