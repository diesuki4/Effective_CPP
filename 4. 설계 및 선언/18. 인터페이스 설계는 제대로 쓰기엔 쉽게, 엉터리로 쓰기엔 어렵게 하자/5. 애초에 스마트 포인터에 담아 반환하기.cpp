#include <iostream>

using namespace std;

/*
 * 애초에 스마트 포인터에 담아 반환하기
 */

class Investment
{
public:
    enum class EType { LowRisk };

    Investment()          { cout << "Investment::생성자" << endl; }
    virtual ~Investment() { cout << "Investment::소멸자" << endl; }

    /*
     * Investment* createInvestment(EType type);
     *
     * 기존 방식은 사용자가 할당받은 객체의 delete 를 까먹은 경우
     * 자원 누출이 발생한다.
     * 
     * 또, delete 를 2번 할 경우도 문제가 발생한다.
     * 
     * 따라서, 애초에 스마트 포인터에 담아 반환하면
     * 사용자의 실수를 미연에 방지할 수 있다.
     */
    static shared_ptr<Investment> createInvestment(EType type);
    static void releaseInvestment(Investment *pInv) { cout << "자원 소멸" << endl; }
};

class LowRiskInvestment : public Investment
{
public:
    LowRiskInvestment()  { cout << "LowRiskInvestment::생성자" << endl; }
    ~LowRiskInvestment() { cout << "LowRiskInvestment::소멸자" << endl; }
};

// 애초에 스마트 포인터에 담아 반환
shared_ptr<Investment> Investment::createInvestment(EType type)
{
    Investment* pInv = nullptr;

    switch (type)
    {
    case EType::LowRisk: pInv = new LowRiskInvestment(); break;
    }

    /*
     * shared_ptr 생성 시에 사용자 정의 삭제자를 전달하면
     * 사용자 측에서
     * 
     * Investment::releaseInvestment(shPtr.get());
     * 
     * 과 같이 호출하지 않아도 된다.
     */
    return shared_ptr<Investment>(pInv, Investment::releaseInvestment);
}

int main(int argc, char* argv[])
{
    /*
     * 사용자 측에서 delete 호출(소멸 시점)
     * 을 신경쓰지 않아도 된다.
     */
    shared_ptr<Investment> shPtr = Investment::createInvestment(Investment::EType::LowRisk);

    // 사용자의 수고를 한 층 더 덜었다.
    // Investment::releaseInvestment(shPtr.get());

    return 0;
}
