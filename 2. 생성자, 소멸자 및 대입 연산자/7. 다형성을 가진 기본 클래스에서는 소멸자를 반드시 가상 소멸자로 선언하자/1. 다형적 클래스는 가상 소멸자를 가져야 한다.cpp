#include <iostream>

using namespace std;

/*
 * 다형적 클래스는 가상 소멸자를 가져야 한다
 * 
 * <다형적 클래스>
 * 가상 함수를 최소 1개 이상 가진 클래스다.
 * 부모 클래스 가상 함수를 통해 자식을 조작할 수 있다.
 *
 */

class TimeKeeper
{
public:
    enum class EType { Atomic };

    TimeKeeper()  { cout << "TimeKeeper::생성자" << endl; }
    virtual ~TimeKeeper() { cout << "TimeKeeper::소멸자" << endl; }

    /*
     * 팩토리 함수 (Factory function)
     * 
     * 자식 객체를 만들어 부모 포인터로 반환하는 함수
     */
    static TimeKeeper* GetTimeKeeper(EType type);

    virtual void GetCurrentTime() { cout << "TimeKeeper 시간" << endl; }
};

class AtomicClock : public TimeKeeper
{
public:
    AtomicClock()  { cout << "AtomicClock::생성자" << endl; }
    ~AtomicClock() { cout << "AtomicClock::소멸자" << endl; }

    virtual void GetCurrentTime() override { cout << "AtomicClock 시간" << endl; }
};

TimeKeeper* TimeKeeper::GetTimeKeeper(EType type)
{
    switch (type)
    {
    case EType::Atomic: return new AtomicClock();
    }
}

int main(int argc, char* argv[])
{
    TimeKeeper *ptk = TimeKeeper::GetTimeKeeper(TimeKeeper::EType::Atomic);

    /*
     * 부모인 TimeKeeper 의 소멸자가 가상 소멸자가 아니면,
     *
     * AtomicClock 객체에서 TimeKeeper 부분만
     * 부분 소멸(Partially destroyed) 한다.
     */
    delete ptk;

    return 0;
}
