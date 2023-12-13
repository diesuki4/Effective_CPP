#include <iostream>

using namespace std;

/*
 * 순수 가상 소멸자
 */

// Abstract WithOut Virtuals (가상 함수가 없는 추상 클래스)
class AWOV
{
    int data;

protected:
    AWOV(int data) : data(data) { cout << "AWOV::생성자" << endl; }

public:
    void ShowData() { cout << data << endl; }

    /*
     * 추상 클래스로 만들고 싶은데
     * 마땅히 넣을 순수 가상 함수가 없을 때도 있다.
     *
     * 추상 클래스 -> 상속을 염두에 뒀다 -> 가상 소멸자를 가져야 한다
     * 추상 클래스 -> 순수 가상 함수를 가져야 한다
     *
     * 둘을 모두 만족하는 방법은
     * 소멸자를 순수 가상 소멸자로 선언하는 것이다.
     */
    virtual ~AWOV() = 0;
};

/*
 * 단, 부모의 가상 소멸자가 호출되려면 몸체는 있어야 하기 때문에
 * 별도로 정의는 해주어야 한다.
 * 
 * 클래스 내부에서 바로
 * virtual ~AWOV() { } 로 선언하게 되면
 * 순수 가상 소멸자가 되지 않는다.
 */
AWOV::~AWOV() { cout << "AWOV::소멸자" << endl; }

class Derived : public AWOV
{
public:
    Derived(int data) : AWOV(data) { cout << "Derived::생성자" << endl; }
    ~Derived() { cout << "Derived::소멸자" << endl; }
};

int main(int argc, char* argv[])
{
    AWOV* pa = static_cast<AWOV*>(new Derived(5));

    pa->ShowData();

    delete pa;

    return 0;
}
