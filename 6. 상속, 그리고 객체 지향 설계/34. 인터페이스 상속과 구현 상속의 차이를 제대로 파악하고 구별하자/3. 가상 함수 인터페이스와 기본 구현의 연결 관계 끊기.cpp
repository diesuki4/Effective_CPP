#include <iostream>

using namespace std;

/*
 * 가상 함수 인터페이스와 기본 구현의 연결 관계 끊기
 */

class Airplane
{
public:
    // 순수 가상 함수로 만들어, 인터페이스를 분리
    virtual void fly(const char* destination) = 0;

/* 기본 구현이 protected 인 이유는
 * 
 * 비행기의 사용자는 "비행기가 날 수 있다" 만 알면 될 뿐,
 * "어떻게 나는가" 는 신경 쓰지 말아야 하기 때문. */
protected:
    // 기본 동작을 상속하되, 오버라이드하지 않도록 한다.
    void defaultFly(const char* destination)
    {
        cout << destination << "으로 경비행기로 떠납니다." << endl;
    }
};

class ModelA : public Airplane
{
public:
    // 인터페이스와 기본 구현을 다시 결합
    void fly(const char* destination) override { defaultFly(destination); }
};

class ModelB : public Airplane
{
public:
    void fly(const char* destination) override { defaultFly(destination); }
};

class ModelCX : public Airplane
{
public:
    // 기본 구현을 쓰지 않는 경우 오버라이드한다.
    void fly(const char* destination) override
    {
        /* 기본 구현 오버라이드를 깜빡하는 걸 방지하기 위한
         * 안전 장치를 하나 더 추가한 것이다. */
        cout << destination << "으로 대형 여객기로 떠납니다." << endl;
    }
};

int main(int argc, char* argv[])
{
    ModelCX cx;

    cx.fly("미국");

    return 0;
}
