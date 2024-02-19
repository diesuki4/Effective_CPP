#include <iostream>

using namespace std;

/*
 * 템플릿으로 된 Base 클래스 함수 이름은 찾아지지 않는다
 */

// 2가지 방법으로 메시지를 보내는 기능 제공
class Company
{
public:
    void sendCleartext(const string& msg) { cout << "Hello Company" << endl; }
    void sendEncrypted(const string& msg) { cout << "SGVsbG8gQ29tcGFueUE=" << endl; }
};

// 메시지 전송기 레퍼 클래스
template <class COM>
class MsgSender
{
public:
    void sendClear(const string& msg)  { COM().sendCleartext(msg); }
    void sendSecret(const string& msg) { COM().sendEncrypted(msg); }
};

// 암호화된 메시지만 전송할 수 있음
class SecurityCompany
{
public:
    /* void sendCleartext(const string& msg); */
    void sendEncrypted(const string& msg) { cout << "SGVsbG8gU2VjdXJpdHlDb21wYW55" << endl; }
};

/* 메시지 전송기 레퍼 클래스 (완전 특수화)
 * 암호화된 메시지만 전송 가능 */
template <>
class MsgSender<SecurityCompany>
{
public:
    /* void sendClear(const string& msg); */
    void sendSecret(const string& msg) { SecurityCompany().sendEncrypted(msg); }
};

// 로깅을 지원하는 메시지 전송기로 확장
template <class COM>
class LoggingMsgSender : public MsgSender<COM>
{
public:
    /* MsgSender<COM>::sendClear() 가 가상 함수가 아니기 때문에
     * 재정의하지 않고 레퍼 함수로 감싼 것은 잘 한 것이다. */
    void sendClearMsg(const string& msg)
    {
        /* 하지만, 이 코드는 컴파일 되지 않음
         * 
         * COM 이 어떤 클래스가 될 지 모르고, 템플릿 특수화로 인해
         * 함수가 아예 존재하지 않을 가능성도 있기 때문.
         *
         * 이처럼 템플릿으로 된 Base 클래스의 함수 이름은
         * 별도로 요청하지 않으면 알아서 찾지 않는다. */
        sendClear(msg);

        /* ... 어떤 로그 기록 작업 */
    }
};

int main(int argc, char* argv[])
{
    

    return 0;
}
