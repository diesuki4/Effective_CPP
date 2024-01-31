#include <iostream>

using namespace std;

/*
 * private 상속보다는 public 상속 + 객체 합성이 더 자주 쓰인다
 *
 * 그래도 private 상속을 고려해 볼 수 있는 경우
 * 1. 부모의 protected 부분에 접근해야 할 때
 * 2. 가상 함수를 좀 더 쉽게 오버라이드하고 싶을 때
 * 3. 공간이 매우 중요한 시스템에서 EBO 최적화를 사용해야 할 때
 *
 * 사실, public 상속 + 객체 합성에서도 이런 점들은 보완이 가능하다.
 * 1. friend 선언 혹은 Getter/Setter 로 해결이 가능하다.
 * 2. 객체의 정보를 넘겨주는 과정이 필요할 뿐, 구현이 불가능한 것은 아니다.
 * 3. EBO 때문에 private 상속을 쓰라고 하기엔 무리가 있다.
 *
 * private 상속을 심사숙고해서 구사하자는 것은
 * private 상속 이외에 모든 대안을 고민한 후,
 *
 * 그래도 가장 나은 방법이라고 생각되면 쓰라는 것이다.
 */

class Timer
{
public:
    explicit Timer(int tickFrequency = 1) {}

    virtual void onTick() const {}
};

// private 상속 대신 객체 합성을 써도 된다.
class Widget
{
    class WidgetTimer;
    /* 현실적으로는 <private 상속> 보다 <public 상속 + 객체 합성> 이 더 자주 쓰인다.
     *
     * <private 상속> 에서는 Widget 의 자식들에게 onTick() 함수를 오버라이드할 가능성을 주게 되지만,
     * <public 상속 + 객체 합성> 에서는 그럴 방법이 없으므로 오버라이드를 막을 수 있다.
     *
     * 또, Pimpl 관용구를 이용해 컴파일 의존성을 줄일 수도 있다. */
    unique_ptr<WidgetTimer> pImpl;

public:
    Widget();
    ~Widget();
};

class Widget::WidgetTimer : public Timer
{
public:
    void onTick() const override { /* Widget 의 정보 기록 */ }
};

Widget::Widget() : pImpl(make_unique<WidgetTimer>())
{
}

Widget::~Widget() = default;

int main(int argc, char* argv[])
{

    return 0;
}
