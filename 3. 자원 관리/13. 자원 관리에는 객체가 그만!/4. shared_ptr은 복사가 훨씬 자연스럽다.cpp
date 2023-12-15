#include <iostream>
#include <vector>

using namespace std;

/*
 * shared_ptr은 복사가 훨씬 자연스럽다
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
     * 복사 함수 호출시 원본이
     * nullptr 을 가리키도록 하는 특성 때문에
     * 
     * 정상적인 복사가 이뤄져야 하는 vector 등의
     * STL 컨테이너에서는 auto_ptr 을 원소로 쓸 수 없다.
     * 
     * vector<auto_ptr<Investment>> v(2, auto_ptr<Investment>(Investment::createInvestment(Investment::EType::LowRisk)));
     */
    
    /*
     * 이런 상황에서는
     * 참조 카운팅 방식 스마트 포인터 (RCSP, Reference-Counting Smart Pointer) 가
     * 좋은 대안이 될 수 있다.
     */
    vector<shared_ptr<Investment>> v(3);

    v[0] = shared_ptr<Investment>(Investment::createInvestment(Investment::EType::LowRisk));
    v[1] = shared_ptr<Investment>(Investment::createInvestment(Investment::EType::LowRisk));
    v[2] = v[0];

    /*
     * 더 이상 가리키는 객체가 없을 경우 소멸한다는 점은
     * 가비지 컬렉션과 같지만
     * 
     * GC 와는 달리 순환 참조를 없앨 수 없다는 점은 다르다.
     * 
     * shared_ptr 에서 순환 참조는
     * 하나를 unique_ptr 로 설정해 해결할 수 있다.
     */

    cout << endl << "v[1]이 가리키던 객체의 참조 카운트가 0이 된다." << endl;
    v[1] = v[0];

    cout << endl << "현재 v[0] 객체의 참조 카운트: " << v[0].use_count() << endl;
    cout << "프로그램 종료" << endl;

    /*
     * 3개의 shared_ptr 은 순차적으로 소멸하므로,
     * 하나씩 사라지며 참조 카운트를 감소시키다가
     * 
     * 마지막에 0이 되는 녀석이 자원을 delete 하게 된다.
     */

    return 0;
}
