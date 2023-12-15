#include <iostream>

using namespace std;

/*
 * 자식 클래스에서 부모 클래스의 복사를 빠뜨리지 마라
 * 
 * 설계가 잘 된 객체 지향 시스템에는
 * 복사 함수가 복사 생성자, 복사 대입 연산자
 * 딱 2개만 존재한다.
 */

class Customer
{
    string name;
    float lastTransactionTime;

public:
    Customer(string name = "Default", float lastTransactionTime = 0.F)
    : name(name), lastTransactionTime(lastTransactionTime) { }

    // lastTransactionTime 누락으로 인한 부분 복사를 해결했다.

    Customer(const Customer& rhs) : name(rhs.name), lastTransactionTime(rhs.lastTransactionTime)
    {
        cout << "Customer::복사 생성자" << endl;
    }

    Customer& operator= (const Customer& rhs)
    {
        cout << "Customer::복사 대입 연산자" << endl;
        name = rhs.name;
        lastTransactionTime = rhs.lastTransactionTime;
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

    PriorityCustomer(const PriorityCustomer& rhs)
    // 부모의 복사 생성자도 호출해줘야 한다.
    : Customer(rhs)
    , priority(rhs.priority)
    {
        cout << "PriorityCustomer::복사 생성자" << endl;
    }

    /*
     * 혹시라도 코드 중복을 줄이기 위해 복사 대입 연산자에서
     * 복사 생성자를 호출하려는 발상을 했다면
     * 
     * 매우 위험하기 때문에 접는 게 좋다.
     * 
     * 선언과 동시에 초기화, 선언 후 대입이라는 역할이 다르기 때문에
     * 따로 작성해줘야 하는 게 맞다.
     * 
     * 단, 기본 타입에 대해서는 비용이 같기 때문에
     * private init() 함수에 몰아 중복을 줄여도 된다.
     */
    PriorityCustomer& operator= (const PriorityCustomer& rhs)
    {
        cout << "PriorityCustomer::복사 대입 연산자" << endl;

        // 부모의 복사 대입 연산자도 호출해줘야 한다.
        Customer::operator=(rhs);

        priority = rhs.priority;

        return *this;
    }

    void Show() { Customer::Show(); cout << "Priority: " << priority << endl; }
};

int main(int argc, char* argv[])
{
    Customer c1("Kim", 3.F), c2("Lee", 10.F);

    c1 = c2;
    c1.Show();

    PriorityCustomer p1(1, "Park", 5.F), p2(2, "Han", 7.F);

    p1 = p2;
    p1.Show();

    return 0;
}
