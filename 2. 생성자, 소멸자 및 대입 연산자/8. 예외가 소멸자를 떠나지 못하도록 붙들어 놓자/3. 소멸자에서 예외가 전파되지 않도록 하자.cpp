#include <iostream>

using namespace std;

/*
 * 소멸자에서 예외가 전파되지 않도록 하자
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
        throw "Exception!!";

        cout << "DB Close" << endl;
    }
};

class DBConn
{
    DBConnection db;
    bool closed;

public:
    DBConn() : db(DBConnection::Create()), closed(false)
    {
        db.open();
    }

    /*
     * 사용자에게 close() 함수의 레퍼 함수를 제공해
     * 사용자가 우선적으로 예외의 전파에 대응할 수 있도록 한다.
     * 
     * 문제가 있을 때 소멸자가 아닌
     * 다른 함수에서 예외가 전파되도록 하는 것이다.
     */
    void close()
    {
        db.close();
        closed = true;
    }

    ~DBConn()
    {
        // close() 함수가 성공했다면 문제가 없겠지만
        if (!closed)
        {
            try
            {
                db.close();
            }
            catch (...)
            {
                cout << "close() 호출이 실패했다는 로그" << endl;

                /*
                 * 실패했다면 여전히 삼키거나, 끝내거나
                 * 2가지 갈림길에 서게 된다.
                 */ 

                /*
                 * 사용자에게 우선적으로 예외를 처리하도록 넘겼으므로
                 * 여기서는 프로그램을 끄지 않는 게 좋을 것 같다.
                 * 
                 * 프로그램을 끌지 안 끌지를 사용자가 결정하도록 넘겼는데
                 * 여기서 무조건 끄도록 하는 건 맞지 않기 때문이다.
                 * 
                 * abort();
                 */
            }
        }
    }
};

int main(int argc, char* argv[])
{
    DBConn conn;

    try
    {
        /*
         * 사용자가 close() 호출을 깜빡 했어도
         * DBConn 의 소멸자가 한번 더 확인할 것이다.
         * 
         * close() 호출은 사용자가 우선적으로
         * 예외를 처리할 수 있게 하기 위함이다.
         */
        conn.close();
    }
    catch (...)
    {
        cout << "사용자 측에 우선적으로 넘겨진 예외 처리" << endl;

        /*
         * 사용자는 프로그램을 끄지 않도록 결정했다.
         * 
         * abort();
         */
    }

    return 0;
}
