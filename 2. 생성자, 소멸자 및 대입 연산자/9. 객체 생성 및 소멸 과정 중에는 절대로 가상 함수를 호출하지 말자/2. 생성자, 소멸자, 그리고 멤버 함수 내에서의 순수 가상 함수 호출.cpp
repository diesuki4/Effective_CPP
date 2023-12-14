#include <iostream>

using namespace std;

/*
 * 생성자, 그리고 멤버 함수 내에서의 순수 가상 함수 호출
 */

class Transaction
{
    int i;
    char c;
    float f;

public:
    /*
     * 값 타입의 경우 멤버 이니셜라이저나 몸체에서의 대입이나
     * 비용이 동일하기 때문에
     *
     * 이니셜라이저가 길어지는 걸 개선하고
     * 몸체에 중복 대입 코드가 들어가는 걸 방지하기 위해
     * 별도 private 초기화 함수를 만들곤 한다.
     */

    Transaction() { init(); }
    Transaction(int i) { init(i); }
    Transaction(int i, char c) { init(i, c); }
    Transaction(int i, char c, float f) { init(i, c, f); }

    virtual void logTransaction() const = 0;

private:
    /*
     * 하지만, 현 상황에서 이는
     * 생성자에서 순수 가상 함수를 호출하는 것보다 더 나쁜 코드다.
     *
     * 생성자에서의 순수 가상 함수 호출은 무조건 같은 클래스의 함수일 수밖에 없기 때문에
     * 그 함수의 구현부를 찾다가 링크 에러가 발생하는데
     *
     * 멤버 함수에서의 순수 가상 함수 호출은 자식 클래스의 재정의 함수를 호출해야 할 수도 있기 때문에
     * 클래스 내의 구현부를 찾지 않아 링크 에러가 발생하지 않는다.
     */
    void init(int i = 0, char c = '\0', float f = 0.F)
    {
        this->i = i;
        this->c = c;
        this->f = f;

        /*
         * 하지만, 이 함수는 여전히 부모의 생성자에서 호출되고 있기 때문에
         * 객체 타입에 관계 없이 현재는 Transaction 타입인 상태다.
         * 
         * 그렇기에 링크 에러가 없더라도
         * 객체가 생성되는 순간 링크된 구현부를 찾지 못 해
         * abort() 가 실행되면서 런타임 에러가 발생하게 된다.
         */
        logTransaction();
    }
};

class BuyTransaction : public Transaction
{
public:
    BuyTransaction()
    {
        logTransaction();
    }

    virtual void logTransaction() const override
    {
        cout << "매수 트랜잭션" << endl;
    }
};

int main(int argc, char* argv[])
{
    BuyTransaction b;

    return 0;
}
