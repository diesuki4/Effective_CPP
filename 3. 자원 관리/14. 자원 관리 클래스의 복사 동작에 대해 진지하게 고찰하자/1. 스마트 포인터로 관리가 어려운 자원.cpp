#include <iostream>
#include <mutex>

using namespace std;

/*
 * 스마트 포인터로 관리가 어려운 자원
 */

/*
 * 모든 자원이 힙에 할당되는 것은 아니고
 * 그런 자원들은 스마트 포인터로 관리하기엔 무리가 있다.
 *
 * 대표적으로 멀티스레드에서 뮤텍스가 그렇다.
 */
mutex mtx;

void lock(mutex* pm)   { pm->lock(); }
void unlock(mutex* pm) { pm->unlock(); }

// RAII 법칙으로 구성된 자원 관리 클래스
class Lock
{
    mutex* mutexPtr;

public:
    // 생성 시에 자원을 획득하고
    explicit Lock(mutex* pm) : mutexPtr(pm)
    {
        lock(mutexPtr);
        cout << "Lock::생성자" << endl;
    }

    // 소멸 시에 해제한다.
    ~Lock()
    {
        unlock(mutexPtr);
        cout << "Lock::소멸자" << endl;
    }
};

int main(int argc, char* argv[])
{
    int sum = 0;

    // 임계 영역을 정하기 위해 블록을 만든다.
    {
        cout << "임계 영역 진입" << endl;

        Lock lck(&mtx);

        for (int i = 0; i < 100; ++i)
            ++sum;
    }

    cout << "임계 영역 탈출" << endl;

    return 0;
}
