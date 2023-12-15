#include <iostream>

using namespace std;

/*
 * 자원 누수가 발생할 수 있는 여러 상황들
 */

class Investment
{
public:
    enum class EType { LowRisk };

    Investment()          { cout << "Investment::생성자" << endl; }
    virtual ~Investment() { cout << "Investment::소멸자" << endl; }

    // 팩토리 함수
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
 * 1. delete 전에 return 문을 만날 경우
 */
void Func1(int num)
{
    Investment *pInv = Investment::createInvestment(Investment::EType::LowRisk);

    if (num == 2)
        return;

    // num == 2 이면 소멸하지 않고 누수된다.
    delete pInv;
}

/*
 * 2. delete 전에 continue 문을 만날 경우
 */
void Func2(int num)
{
    for (int i = 0; i < num; ++i)
    {
        Investment* pInv = Investment::createInvestment(Investment::EType::LowRisk);

        if (1 <= i)
            continue;

        // 첫 객체 이외에는 소멸하지 않고 누수된다.
        delete pInv;
    }
}

/*
 * 3. delete 전에 예외가 발생할 경우
 */
int Func3(int num) throw(int)
{
    Investment* pInv = Investment::createInvestment(Investment::EType::LowRisk);

    if (num == 2)
        throw num;

    // num == 2 이면 소멸하지 않고 누수된다.
    delete pInv;

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

    // 자원 누수가 발생하는 상황들
    cout << endl << "--- Func1(2) ---" << endl;
    Func1(2);
    cout << endl << "--- Func2(2) ---" << endl;
    Func2(2);
    cout << endl << "--- Func3(2) ---" << endl;
    Func3(2);

    return 0;
}
