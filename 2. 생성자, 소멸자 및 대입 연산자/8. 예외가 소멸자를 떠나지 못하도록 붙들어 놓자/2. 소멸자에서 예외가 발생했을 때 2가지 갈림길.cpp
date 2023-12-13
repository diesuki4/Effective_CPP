#include <iostream>

using namespace std;

/*
 * 소멸자에서 예외가 발생했을 때 2가지 갈림길
 */

class DBConnection
{
public:
    static DBConnection Create()
    {
        return DBConnection();
    }

    void open()
    {
        cout << "DB Open" << endl;
    }

    void close() throw(string)
    {
        /*
         * 연결을 닫는 도중 예외 발생 가정
         * 
         * Caller 에게 예외가 전파(Propagate) 된다.
         */
        throw "Exception!!";

        cout << "DB Close" << endl;
    }
};

/*
 * 사용자가 DBConnection 의 close() 호출을 깜빡해서
 * 자원 낭비가 발생하도록 두는 것보다는
 * 
 * 사용자를 배려해 자원 관리 클래스를 만드는 게 좋다.
 * 스마트 포인터의 원리와 비슷하다.
 */
class DBConn
{
    DBConnection db;

public:
    DBConn() : db(DBConnection::Create())
    {
        db.open();
    }

    ~DBConn()
    {
        try
        {
            // 예외 발생
            db.close();
        }
        catch (...)
        {
            /*
             * 소멸자에서 예외가 발생했다면 길은 2개다.
             * 
             * 필수적으로 로그는 출력해야 한다.
             */
            cout << "close() 호출이 실패했다는 로그" << endl;

            /*
             * 1. 로그만 찍고 예외를 삼켜 계속 실행한다.
             * 
             * 단, 예외를 삼키더라도 신뢰성 있게
             * 실행을 지속할 수 있는 상황이어야 한다.
             */

            /*
             * 2. 프로그램을 바로 끝낸다. (추천)
             *
             * 예외를 삼켰다가 Undefined behavior 에 이르러
             * 못 볼꼴을 볼 바에는 꺼 버리겠다는 것이다.
             */
            abort();
        }
    }
};

int main(int argc, char* argv[])
{
    DBConn conn;

    return 0;
}
