#include <iostream>

using namespace std;

/*
 * 생성자, 소멸자에서 절대 가상 함수를 호출하지 마라
 */

class Transaction
{
public:
    Transaction()
    {
        /*
         * 부모의 생성자가 먼저 호출되기 때문에
         * 아직 자식의 멤버와 가상 함수 테이블은
         * 초기화되지 않았다.
         * 
         * 그래서 부모의 생성자가 실행되는 동안
         * 그 객체의 타입은 부모의 타입으로 동작한다.
         */
        cout << "현재 타입: " << typeid(*this).name() << endl;

        /*
         * 따라서, 부모 생성자에서 가상 함수를 호출하면
         * 자식이 아닌 부모의 함수가 호출된다.
         * 
         * 자식의 멤버가 초기화되지도 않았는데
         * 자식 멤버를 조작하는 자식 함수를 호출할 수는 없기 때문
         */

        /*
         * 특히, 순수 가상 함수의 경우
         * 부모에서는 정의가 존재하지 않기 때문에
         * 링크 에러가 발생한다.
         * 
         * logTransaction();
         * 
         */
    }

    virtual void logTransaction() const = 0;

    virtual ~Transaction()
    {
        /*
         * 생성자와 같은 이유로
         * 부모의 소멸자가 실행되는 동안
         * 그 객체의 타입은 부모의 타입으로 동작한다.
         * 
         * 따라서, 부모 소멸자에서도 가상 함수를 호출하면
         * 자식이 아닌 부모의 함수가 호출된다.
         */
    }
};

class BuyTransaction : public Transaction
{
public:
    BuyTransaction()
    {
        cout << "현재 타입: " << typeid(*this).name() << endl;

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
