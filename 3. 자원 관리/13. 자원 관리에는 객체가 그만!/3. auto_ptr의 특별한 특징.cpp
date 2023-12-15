#include <iostream>

using namespace std;

/*
 * auto_ptr의 특별한 특징
 */

class Investment
{
public:
    enum class EType { LowRisk };

    Investment()          { cout << "Investment::생성자" << endl; }
    virtual ~Investment() { cout << "Investment::소멸자" << endl; }

    static Investment* createInvestment(EType type);
};

class LowRiskInvestment : public Investment
{
public:
    LowRiskInvestment()  { cout << "LowRiskInvestment::생성자" << endl; }
    ~LowRiskInvestment() { cout << "LowRiskInvestment::소멸자" << endl; }
};

Investment* Investment::createInvestment(EType type)
{
    switch (type)
    {
    case EType::LowRisk: return new LowRiskInvestment();
    }
}

int main(int argc, char* argv[])
{
    /*
     * 같은 객체를 2개 이상의 auto_ptr 이 관리하면
     * 나중에 해제딘 메모리를 delete 하게 되므로
     * 문제가 발생한다.
     * 
     * 따라서, auto_ptr 은 특별한 특징이 있다.
     * 
     * 복사 함수(복사 생성자, 복사 대입 연산자) 를 호출하면
     * 원본 객체는 nullptr 을 가리키도록 한다.
     * 
     * 복사하는 객체만이 자원의 유일한 소유권을 갖는 것이다.
     */
    auto_ptr<Investment> p1(Investment::createInvestment(Investment::EType::LowRisk));
    auto_ptr<Investment> p2(p1);

    if (p1.get() == nullptr)
        cout << p2.get() << endl;

    p1 = p2;

    if (p2.get() == nullptr)
        cout << p1.get() << endl;

    return 0;
}
