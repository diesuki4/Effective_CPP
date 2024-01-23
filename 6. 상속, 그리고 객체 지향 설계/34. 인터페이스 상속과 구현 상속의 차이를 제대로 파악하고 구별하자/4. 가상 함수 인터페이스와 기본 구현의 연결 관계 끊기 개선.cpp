#include <iostream>

using namespace std;

/*
 * 가상 함수 인터페이스와 기본 구현의 연결 관계 끊기 개선
 */

class Airplane
{
public:
    // defaultFly() 같은 별도 기본 구현을 만드는 게 거추장스러울 수 있다.
    virtual void fly(const char* destination) = 0;
};

// 그럴 경우 순수 가상 함수의 본문을 정의하는 방법을 활용할 수 있다.
void Airplane::fly(const char* destination)
{
    cout << destination << "으로 경비행기로 떠납니다." << endl;
}

class ModelA : public Airplane
{
public:
    // fly() 를 꼭 오버라이드 해야 하지만, 기본 구현은 제공되고 있다.
    void fly(const char* destination) override { Airplane::fly(destination); }
};

class ModelB : public Airplane
{
public:
    void fly(const char* destination) override { Airplane::fly(destination); }
};

class ModelCX : public Airplane
{
public:
    void fly(const char* destination) override
    {
        cout << destination << "으로 대형 여객기로 떠납니다." << endl;
    }
};

int main(int argc, char* argv[])
{
    ModelCX cx;

    cx.fly("미국");

    /* 단, 인터페이스와 기본 구현에
     * 다른 보호 수준을 지정하는 융통성은 포기해야 한다. */
    cx.Airplane::fly("일본");

    return 0;
}
