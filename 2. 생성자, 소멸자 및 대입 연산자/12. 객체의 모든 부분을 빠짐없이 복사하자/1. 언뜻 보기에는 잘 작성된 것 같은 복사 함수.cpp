#include <iostream>

using namespace std;

/*
 * 언뜻 보기에는 잘 작성된 것 같은 복사 함수
 */

class Customer
{
    string name;
    float lastTransactionTime;

public:
    Customer(string name = "Default", float lastTransactionTime = 0.F)
    : name(name), lastTransactionTime(lastTransactionTime) { }

    /*
     * 사용자 정의 복사 함수는 멤버가 누락될 가능성이 있지만
     * 깊은 복사를 제공할 수 있고
     * 
     * 컴파일러가 만드는 복사 함수는 멤버가 누락될 일은 없지만
     * 얕은 복사만 제공한다.
     * 
     * 아래에서는 lastTransactionTime 이 누락돼
     * 부분 복사(Partial copy) 가 일어나고 있다.
     */
    Customer(const Customer& rhs) : name(rhs.name)
    {
        cout << "Customer::복사 생성자" << endl;
    }

    Customer& operator= (const Customer& rhs)
    {
        cout << "Customer::복사 대입 연산자" << endl;
        name = rhs.name;
        return *this;
    }

    void Show() { cout << "Name: " << name << ", LastTransactionTime: " << lastTransactionTime << endl; }
};

class PriorityCustomer : public Customer
{
    int priority;
    
public:
    PriorityCustomer(int priority = 0, string name = "Default", float lastTransactionTime = 0.F)
    : Customer(name, lastTransactionTime), priority(priority) { }

    /*
     * 두 복사 함수는 언뜻 보기에는 잘 작성된 것 같지만
     * 부모 멤버 복사에 대한 어떤 고려도 없다.
     */

    /*
     * 복사 생성자에서는 부모에 대한 구문이 없으므로
     * 부모는 기본 생성자가 호출된다.
     */
    PriorityCustomer(const PriorityCustomer& rhs) : priority(rhs.priority)
    {
        cout << "PriorityCustomer::복사 생성자" << endl;
    }

    /*
     * 복사 대입 연산자에서는 부모의 멤버는
     * 아예 대입이 되지 않는다.
     * 
     * 사용자 정의 복사 대입 연산자에서는
     * 부모의 복사 대입 연산자를 자동으로 호출하지 않기 때문
     */
    PriorityCustomer& operator= (const PriorityCustomer& rhs)
    {
        cout << "PriorityCustomer::복사 대입 연산자" << endl;
        priority = rhs.priority;
        return *this;
    }

    void Show() { Customer::Show(); cout << "Priority: " << priority << endl; }
};

int main(int argc, char* argv[])
{
    Customer c1("Kim", 3.F), c2("Lee", 10.F);

    // lastTransactionTime 복사가 누락
    c1 = c2;
    c1.Show();

    PriorityCustomer p1(1, "Park", 5.F), p2(2, "Han", 7.F);

    // 부모 Customer 멤버의 복사가 완전 누락
    p1 = p2;
    p1.Show();

    return 0;
}
