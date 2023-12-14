#include <iostream>

using namespace std;

/*
 * 생성자, 소멸자에서 가상 함수를 호출하면 일어나는 일
 */

class Transaction
{
public:
    Transaction()
    {
        /*
         * 이 호출은 자식의 재정의 함수 호출을 의도했을 것이다.
         *
         * 하지만, 현재 타입은 자식이 초기화되기 전인 Transaction 이므로
         * 이 클래스의 함수가 호출된다.
         *
         * 앞의 두 상황과 달리, 링크 에러나 런타임 에러도 없이
         * 조용히 점점 이상한 방향으로 실행되므로
         * 더 위험하다고 할수 있다.
         */
        logTransaction();
    }

    /*
     * 순수 가상 함수가 아닌 몸체를 가지므로
     * 이제 생성자, 소멸자에서도 호출할 수 있다.
     */
    virtual void logTransaction() const { cout << "트랜잭션" << endl; }

    /*
     * 생성자와 마찬가지로 자식이 아닌
     * 이 클래스의 함수가 호출된다.
     */
    virtual ~Transaction() { logTransaction(); }
};

class BuyTransaction : public Transaction
{
public:
    virtual void logTransaction() const override { cout << "매수 트랜잭션" << endl; }
};

int main(int argc, char* argv[])
{
    BuyTransaction b;

    return 0;
}
