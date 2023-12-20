/*
 * https://drdobbs.com/cpp/how-non-member-functions-improve-encapsu/184401197
 * https://stackoverflow.com/questions/5989734/effective-c-item-23-prefer-non-member-non-friend-functions-to-member-functions
 */
#include <iostream>

using namespace std;

/*
 * 관련성으로 묶기 좋은 네임스페이스를 활용하라
 */

namespace TimeKeeperNS
{
    class TimeKeeper
    {
        float currentTime;

    public:
        enum class EType { Atomic };

        TimeKeeper(float time = 0.F) : currentTime(time) { }
        virtual ~TimeKeeper() { }

        float getCurrentTime() const { return currentTime; }
        void setCurrentTime(float newTime) { currentTime = newTime; }

        virtual void show() { cout << "TimeKeeper 시간: " << getCurrentTime() << endl; }
    };

    class AtomicClock : public TimeKeeper
    {
    public:
        AtomicClock(float time) : TimeKeeper(time) { }

        virtual void show() override { cout << "AtomicClock 시간: " << getCurrentTime() << endl; }
    };

    /*
     * 클래스와 관련된 생성 함수가
     * 클래스 밖에 있다보니 탐탁치 않을 수 있다.
     * 
     * 이럴 때는, 네임스페이스를 활용해
     * 관련된 것들을 하나로 묶어주면 좋다.
     * 
     * 참고로 네임스페이스는
     * 여러 파일에 존재해도 상관 없기 때문에
     * 헤더를 나눠 작성해도 된다.
     * 
     * 이런 특징 덕분에 편의 함수 집합의 확장은
     * 새로운 헤더 파일을 만들고, 동일한 네임스페이스에
     * 함수를 선언하기만 하면 된다.
     *
     * 클래스 내부를 수정하는 것보다 훨씬 효율적이다.
     *
     * std 네임스페이스도 그렇게 작성되어 있다.
     */
    shared_ptr<TimeKeeper> CreateTimeKeeper(TimeKeeper::EType type, TimeKeeper& tk)
    {
        TimeKeeper* ptk = nullptr;

        switch (type)
        {
        case TimeKeeper::EType::Atomic: ptk = new AtomicClock(tk.getCurrentTime()); break;
        }

        return shared_ptr<TimeKeeper>(ptk);
    }
}

int main(int argc, char* argv[])
{
    // TimeKeeper 와 관련된 것들을 불러올 수 있다.
    using namespace TimeKeeperNS;

    TimeKeeper tk(5.F);

    shared_ptr<TimeKeeper> shtk = CreateTimeKeeper(TimeKeeper::EType::Atomic, tk);

    return 0;
}
