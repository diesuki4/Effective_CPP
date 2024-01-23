#include <iostream>

using namespace std;

/*
 * 객체 지향 설계의 장점
 */

class Airplane
{
public:
    /* 이런 고전적인 객체 지향 설계의 장점
     *
     * 1. 공통 사항이 명확해진다.
     * 2. 코드 중복이 줄어든다.
     * 3. 기능 확장이 용이하다.
     * 4. 유지보수가 쉬워진다. */
    virtual void fly(const char* destination)
    {
        cout << destination << "으로 경비행기로 떠납니다." << endl;
    }
};

class ModelA : public Airplane {};
class ModelB : public Airplane {};
// 대형 여객기를 이용해야 하지만, fly() 오버라이드를 깜빡한 경우
class ModelCX : public Airplane {};

int main(int argc, char* argv[])
{
    ModelCX cx;

    /* 컴파일 에러 없이 잘 동작하는 것 같지만, 런타임에 문제가 인지된다.
     * 
     * 문제는 fly() 가 기본 구현을 갖고 있다는 점이 아니라,
     * ModelCX 가 기본 구현을 상속 받는 과정에서 어떤 확인 절차도 없었다는 것이다. */
    cx.fly("미국");

    return 0;
}
