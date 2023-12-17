#include <iostream>
#include <mutex>

using namespace std;

/*
 * RAII 자원 관리 객체 복사 시 고려할 수 있는 4가지 방안
 */

mutex mtx;

void lock(mutex* pm)   { pm->lock(); }
void unlock(mutex* pm) { pm->unlock(); }

class Uncopyable
{
    /*
     * 복사 함수를 private 으로 설정해
     * 자식 클래스에서 접근할 수 없도록 한다.
     *
     * 기본 복사 생성자와 기본 복사 대입 연산자를 막을 뿐,
     * 사용자 정의 복사 함수는 막을 수 없다.
     */
    Uncopyable(const Uncopyable&);
    Uncopyable& operator= (const Uncopyable&);

protected:
    Uncopyable() { }
    ~Uncopyable() { }
};

// 1. 복사를 애초에 금지한다.
class LockUncopyable : private Uncopyable
{
    mutex* mutexPtr;

public:
    explicit LockUncopyable(mutex* pm) : mutexPtr(pm)
    {
        lock(mutexPtr);
    }

    ~LockUncopyable()
    {
        unlock(mutexPtr);
    }
};

// 2. 얕은 복사를 허용하되, 참조 카운팅으로 관리한다.
class LockRCSP
{
    /*
     * shared_ptr 은 삭제자(deleter) 함수를 인자로 전달할 수 있다.
     *
     * 따라서, 기존 포인터를 shared_ptr 에 담는 것은 아주 좋은 방법이다.
     */
    shared_ptr<mutex> mutexPtr;

public:
    explicit LockRCSP(mutex* pm)
    // 사용자 정의 삭제자 전달
    : mutexPtr(pm, unlock)
    {
        lock(mutexPtr.get());
    }

    /*
     * 이제 shared_ptr 을 통해
     * 참조 카운트가 0이 될 때 알아서 unlock() 을
     * 호출할 것이므로
     *
     * 소멸자에서 unlock() 하지 않아도 된다.
     *
     * ~LockRCSP() { unlock(mutexPtr.get()); }
     */
};

// 3. 깊은 복사를 통해 진짜 복사한다.
class StringDeepCopy
{
    int* pData;

public:
    StringDeepCopy(int data) : pData(new int(data)) { }

    StringDeepCopy& operator= (const StringDeepCopy& rhs)
    {
        int* pOrig = pData;

        pData = new int(*rhs.pData);

        delete pOrig;
    }

    /*
     * 깊은 복사에서 자원 관리 객체는
     * 각각의 사본을 확실하게 해제하는 것이 중요하다.
     */
    ~StringDeepCopy()
    {
        delete pData;
    }
};

// 4. 자원의 소유권을 옮긴다.
class LockOwnership
{
    /*
     * 대입 연산 시에 원본이 nullptr 을 가리키게 되는
     * auto_ptr 의 특징을 활용할 수 있다.
     */
    auto_ptr<mutex> mutexPtr;

public:
    // shared_ptr 과 달리 auto_ptr 은 삭제자를 설정할 수 없다.
    explicit LockOwnership(mutex* pm) : mutexPtr(pm)
    {
        lock(mutexPtr.get());
    }

    /*
     * nullptr 을 가리키고 있다면
     * 소유권을 잃었다는 뜻이므로
     * 해제하지 않는다.
     */
    ~LockOwnership()
    {
        mutex* pm = mutexPtr.get();
        
        if (pm != nullptr)
            unlock(pm);
    }
};

int main(int argc, char* argv[])
{


    return 0;
}
