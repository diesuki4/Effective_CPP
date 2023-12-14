#include <iostream>

using namespace std;

/*
 * 자식 클래스 함수를 통한 부모 생성자로의 정보 전달
 */

class Transaction
{
protected:
    /*
     * 자식의 멤버 이니셜라이저에서 보낸 정보를 받을 인자를 추가한다.
     */
    Transaction(const string& logInfo)
    {
        /*
         * logTransaction() 이 이제 일반 함수이므로
         * 의구심 없이 안전하게 호출할 수 있다.
         */
        logTransaction(logInfo);
    }

public:
    /*
     * 생성자에서 호출될 함수를
     * 가상 혹은 순수 가상 함수로 정의해 위험 요소를 만들지 말고
     * 
     * 처음부터 무조건 이 함수를 가져다 쓰도록
     * 그냥 일반 함수로 선언한다.
     */
    void logTransaction(const string& logInfo) const
    {
        /*
         * 자식의 static 클래스 함수로부터 전달된
         * 정보를 활용할 수 있다.
         */
        cout << logInfo << endl;
    }
};

class BuyTransaction : public Transaction
{
    /*
     * 부모의 생성자에서 자식의 가상 함수를 호출한다는 꿈을 버리고
     * 부모 생성자에 인자로 값을 넘기기 위해
     * 
     * 가상 함수 대신 선언된 헬퍼 함수이다.
     * 
     * static 클래스 함수이므로
     * 객체 생성 여부와 관계 없이 호출 가능하고
     * 
     * 멤버 변수의 값에 접근할 수 없으므로,
     * 초기화 여부에 관계 없이 사용할 수 있다.
     * 
     * 전자나 후자나 자식의 멤버를 활용할 수 없다는 점은 같다.
     * 
     * 외부에서는 호출될 일이 없으므로 private 으로 선언했다.
     */
    static string createLogString()
    {
        const static string logString = "매수 트랜젝션";

        return logString;
    }

public:
    /*
     * 가상 함수를 통해 직접 호출하는 것이 아닌,
     * 인자를 통해 부모 생성자에 전달한다.
     */
    BuyTransaction() : Transaction(createLogString()) { }
};

int main(int argc, char* argv[])
{
    BuyTransaction b;

    return 0;
}
