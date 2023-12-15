#include <iostream>

using namespace std;

/*
 * auto_ptr을 통한 자동 소멸
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

/*
 * 코드를 유지보수하다 보면
 * 누구도 모르는 사이 이런 상황들이 발생할 수 있다.
 * 
 * 따라서, 항상 delete 문이 호출될 것이라고
 * 확정해서는 안 된다.
 */

void Func1(int num)
{
    /*
     * 자원이 항상 해제되도록 만드는 아이디어는
     * 
     * 값 타입의 객체는 무조건 스택 프레임과 함께
     * 소멸한다는 데에서 나온다.
     * 
     * 자원을 값 타입의 객체에 넣고
     * scope 를 떠날 때, 소멸자에서 자원과 함께 소멸하는 것이다.
     * 
     * 값 타입의 객체를 통해 소멸 시점을 한정할 수 있게 된다.
     */

    /*
     * 스마트 포인터 auto_ptr 이 이렇게 동작한다.
     * 
     * 자신이 소멸할 때, 가리키고 있는 객체에 대해
     * 소멸자가 자동으로 delete 를 호출한다.
     * 
     * Investment *pInv = Investment::createInvestment(Investment::EType::LowRisk);
     * 
     * 아래처럼 자원 획득과 자원 관리 객체의 초기화가 한 문장에서 이루어지는 것을
     * RAII (Resource Acquisition Is Initialization) 라고 한다.
     */
    auto_ptr<Investment> pInv(Investment::createInvestment(Investment::EType::LowRisk));

    if (num == 2)
        return;

    /*
     * 이제 delete 연산은 필요하지 않다.
     * 
     * delete pInv;
     */
}

void Func2(int num)
{
    for (int i = 0; i < num; ++i)
    {
        // Investment* pInv = Investment::createInvestment(Investment::EType::LowRisk);
        auto_ptr<Investment> pInv(Investment::createInvestment(Investment::EType::LowRisk));

        if (1 <= i)
            continue;

        // delete pInv;
    }
}

int Func3(int num) throw(int)
{
    // Investment* pInv = Investment::createInvestment(Investment::EType::LowRisk);
    auto_ptr<Investment> pInv(Investment::createInvestment(Investment::EType::LowRisk));

    if (num == 2)
        throw num;

    // delete pInv;

    return num;
}

int main(int argc, char* argv[])
{
    cout << "--- Func1(1) ---" << endl;
    Func1(1);
    cout << endl << "--- Func2(1) ---" << endl;
    Func2(1);
    cout << endl << "--- Func3(1) ---" << endl;
    Func3(1);

    // 스마트 포인터를 통해 자원 누수를 해결
    cout << endl << "--- Func1(2) ---" << endl;
    Func1(2);
    cout << endl << "--- Func2(2) ---" << endl;
    Func2(2);
    cout << endl << "--- Func3(2) ---" << endl;
    try
    {
        Func3(2);
    }
    catch (...)
    {
        /*
         * 예외가 잡히면 정상적으로
         * 스택 풀기(Stack Unwinding) 가 수행되면서
         * 스택 자원이 회수된다.
         * 
         * 예외가 잡히지 않으면 terminate() 를 호출해
         * 프로그램 자체를 종료시켜 버린다.
         */
        cout << "예외 처리됨" << endl;
    }

    return 0;
}
