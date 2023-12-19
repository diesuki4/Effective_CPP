/*
 * https://drdobbs.com/cpp/how-non-member-functions-improve-encapsu/184401197
 * https://stackoverflow.com/questions/5989734/effective-c-item-23-prefer-non-member-non-friend-functions-to-member-functions
 */
#include <iostream>

using namespace std;

/*
 * 비멤버 비프렌드 함수로도 구현할 수 있으면 멤버 함수보다 낫다
 *
 * 멤버 함수의 개수가 캡슐화의 척도가 될 수 있다는 사실을 이해했다면,
 * 
 * 멤버 함수보다는 비멤버 비프렌드 함수가
 * 캡슐화를 더 높이는 방법이라는 것을 알 수 있다.
 * 
 * 멤버 함수의 반대는 프렌드 함수가 아니라, 비멤버 함수다.
 *
 * 무조건 멤버 함수로 구현하거나 friend 선언을 하지 말고
 * 항상 캡슐화를 고려해 비멤버 비프렌드 함수도 고려해야 한다.
 */

class TimeKeeper
{
    float currentTime;

public:
    enum class EType { Atomic };

    TimeKeeper(float time = 0.F) : currentTime(time) { }
    virtual ~TimeKeeper() { }

    /*
     * 대표적으로 팩토리 함수가 그렇다.
     *
     * 비멤버 비프렌드 함수로도 구현 가능한 것을
     * 굳이 정적 클래스 함수로 만드는 것은
     *
     * 캡슐화를 저해시킨다.
     */
    static shared_ptr<TimeKeeper> CreateTimeKeeper(EType type, TimeKeeper& tk);

    float getCurrentTime() const { return currentTime; }
    void setCurrentTime(float newTime) { currentTime = newTime; }

    /*
     * 캡슐화 관점에서는 클래스 내부에서도
     * 데이터 멤버를 직접 사용하는 것보다는
     * Getter, Setter 를 쓰는 게 낫지 않을까?
     *
     * 어차피 inline 처리되어 성능에는 지장이 없을 것이다.
     */
    virtual void show() { cout << "TimeKeeper 시간: " << getCurrentTime() << endl; }
};

class AtomicClock : public TimeKeeper
{
public:
    AtomicClock(float time) : TimeKeeper(time) { }

    virtual void show() override { cout << "AtomicClock 시간: " << getCurrentTime() << endl; }
};

// 정적 클래스 함수에서도 마찬가지로
shared_ptr<TimeKeeper> TimeKeeper::CreateTimeKeeper(EType type, TimeKeeper& tk)
{
    TimeKeeper* ptk = nullptr;

    switch (type)
    {
    // 데이터 멤버 사용으로 인해
    // 코드 깨짐이 발생할 수 있다.
    case EType::Atomic: ptk = new AtomicClock(tk.currentTime); break;
    }

    return shared_ptr<TimeKeeper>(ptk);
}

/*
 * 따라서, 비멤버 비프렌드로도 구현이 가능한
 * 정적 팩토리 함수 같은 것들은 멤버 함수보다는
 *
 * 차라리, 비멤버 비프렌드 함수로 빼는 게
 * 캡슐화에는 더 도움이 된다.
 *
 * 밖으로 빼라는 것이 꼭 이렇게 빼라는 것이 아니고
 * 다른 클래스의 비멤버 비프렌드 함수로 구현해도 된다.
 *
 * private 멤버의 캡슐화에 영향을 주지만 않는다면.
 *
 * 그리고 std::sort() 같은 경우를 보면
 * 밖으로 빼고 템플릿을 적용하면서
 * 
 * 매 컨테이너마다 정렬 함수를 구현하지 않고
 * 하나의 함수로 모든 컨테이너를 정렬할 수 있도록 했다.
 */
shared_ptr<TimeKeeper> CreateTimeKeeper(TimeKeeper::EType type, TimeKeeper& tk)
{
    TimeKeeper* ptk = nullptr;

    switch (type)
    {
    // 데이터 멤버 대신
    // 기존 멤버 함수를 활용해
    // 코드 깨짐을 줄였다.
    case TimeKeeper::EType::Atomic: ptk = new AtomicClock(tk.getCurrentTime()); break;
    }

    return shared_ptr<TimeKeeper>(ptk);
}

int main(int argc, char* argv[])
{
    TimeKeeper tk(5.F);

    shared_ptr<TimeKeeper> shtk = CreateTimeKeeper(TimeKeeper::EType::Atomic, tk);

    return 0;
}
