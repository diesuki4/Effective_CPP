#include <iostream>

/*
 * releaseInvestment() 라는 함수가
 * 외부 DLL 에 존재한다고 가정
 * 
 * #pragma comment(lib, "InvestmentReleaseModule.lib")
 * #pragma comment(lib, "InvestmentAcquireModule.lib")
 */

using namespace std;

/*
 * 교차 DLL 문제를 방지하는 shared_ptr
 */

class Investment
{
public:
    Investment()  { cout << "Investment::생성자" << endl; }
    ~Investment() { cout << "Investment::소멸자" << endl; }
};

/*
 * InvestmentReleaseModule.dll 에 존재하는 함수라고 가정
 */
void releaseInvestment(Investment* pInv)
{
    cout << "InvestmentReleaseModule.dll 에서 소멸" << endl;

    if (pInv != nullptr)
        delete pInv;
}

/*
 * InvestmentAcquireModule.dll 에 존재하는 함수라고 가정
 */
Investment* acquireInvestment()
{
    cout << "InvestmentAcquireModule.dll 에서 생성" << endl;

    return new Investment;
}

shared_ptr<Investment> acquireInvestmentSafe()
{
    cout << "InvestmentAcquireModule.dll 에서 생성, 후에 이 DLL 에서 해제될 것을 기억" << endl;

    return shared_ptr<Investment>(new Investment);
}

int main(int argc, char* argv[])
{
    /*
     * new 와 delete 가
     * 다른 DLL 에서 이뤄지면
     * 
     * 교차 DLL 문제로 인해 런타임 에러가 발생한다.
     */
    Investment* pInv = acquireInvestment();
    releaseInvestment(pInv);

    /*
     * shared_ptr 의 기본 삭제자는
     * 자신이 생성된 DLL 과 동일한 DLL 에서
     * delete 되도록 만들어져 있다.
     * 
     * 자원을 어떤 DLL 에서 delete 해야 하는지를 기억하고 있기 때문.
     * 
     * 따라서, 여러 DLL 사이에서 이리저리 넘겨지더라도
     * 교차 DLL 문제가 발생하지 않는다.
     */
    shared_ptr<Investment> shPtr = acquireInvestmentSafe();

    return 0;
}
