#include <iostream>

using namespace std;

/*
 * private 상속보다 public 상속 + 객체 합성이 더 자주 쓰인다
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
     * <public 상속 + 객체 합성> 에서는 그럴 방법이 없다.
     *
     * 또, pImpl 관용구를 이용해 컴파일 의존성을 줄일 수 있다. */
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
