#include <iostream>

using namespace std;

/*
 * private 상속은 Is-implemented-in-terms-of 관계를 의미한다
 *  
 * private 상속은 기능 몇 개를 활용할 목적으로 하는 것이다.
 *
 * private 상속을 하면 자식 클래스에서는 모두 private 으로 처리되는데
 * 이는 인터페이스가 아니라 세부 구현만을 물려 받겠다는 의미다.
 *
 * private 상속은 그 자체로 구현 기법 중 하나이며,
 * Derived 가 Base 를 써서 구현됐다고 생각하면 된다.
 *
 * 소프트웨어 설계 관점에서는 아무런 의미도 갖지 않으며, 구현에서만 의미를 갖는다.
 */

// 어딘가에서 tickFrequency 마다 Timer::onTick() 을 호출한다고 할 때
class Timer
{
public:
    explicit Timer(int tickFrequency = 1) {}

    virtual void onTick() const {}
};

/* Timer 의 기능을 이용해 일정 시간마다 Widget 객체의 정보를 기록할 수 있다.
 * 
 * Widget 은 기능을 이용할 뿐 Timer 의 일종이 아니고,
 * Widget 에서 onTick() 함수는 외부에 공개하는 인터페이스가 되면 안 되기 때문에
 *
 * public 상속은 적합하지 않다. */
class Widget : private Timer
{
private:
    void onTick() const override { /* Widget 의 정보 기록 */ }
};

int main(int argc, char* argv[])
{
    /* 불가
     * Is-A 관계인 public 상속에서만 자식이 부모 타입으로 변환될 수 있다.
    const Timer& ct = Widget();
    const Timer& ct = static_cast<Timer>(Widget()); */

    return 0;
}
