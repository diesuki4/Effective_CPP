#include <iostream>

using namespace std;

/*
 * 템플릿 Base 클래스 함수 이름을 찾도록 요청하는 3가지 방법
 * 
 * 핵심은 부모 함수 호출이 유효한지를
 * 파생 클래스 정의가 구문 분석될 때 확인하는지,
 * 아니면, 클래스 템플릿이 인스턴싱될 때 확인하는지의 차이다.
 * 
 * C++ 은 전자인 이른 진단(Early diagnose) 을 기본 정책으로 설정했고
 * 아래 3가지 방법으로 후자로 확인 시점을 미룰 수 있다.
 */

class Company
{
public:
    void sendCleartext(const string& msg) { cout << "Hello Company" << endl; }
    void sendEncrypted(const string& msg) { cout << "SGVsbG8gQ29tcGFueUE=" << endl; }
};

template <class COM>
class MsgSender
{
public:
    void sendClear(const string& msg)  { COM().sendCleartext(msg); }
    void sendSecret(const string& msg) { COM().sendEncrypted(msg); }
};

class SecurityCompany
{
public:
    /* void sendCleartext(const string& msg); */
    void sendEncrypted(const string& msg) { cout << "SGVsbG8gU2VjdXJpdHlDb21wYW55" << endl; }
};

template <>
class MsgSender<SecurityCompany>
{
public:
    /* void sendClear(const string& msg); */
    void sendSecret(const string& msg) { SecurityCompany().sendEncrypted(msg); }
};

template <class COM>
class LoggingMsgSender : public MsgSender<COM>
{
public:
    // 2. using 선언을 이용
    // 부모 함수를 Name resolution 후보에 올렸을 뿐이지, 사용을 강제하는 것은 아니다.
    using MsgSender<COM>::sendClear;

    void sendClearMsg(const string& msg)
    {
        // 1. this 포인터를 이용해 상속된 함수임을 명시
        this->sendClear(msg);

        // 2. using 선언을 이용
        // 만약 sendClear() 가 가상 함수이고 자식에서 오버라이드 했다면, 자식 함수가 호출될 것.
        sendClear(msg);

        // 3. Scope 를 지정 (동적 바인딩이 무시되기 때문에 좋지 않은 방법)
        // 부모 함수의 사용을 강제한다.
        MsgSender<COM>::sendClear(msg);

        /* 어떤 로그 기록 작업 */
    }
};

int main(int argc, char* argv[])
{
    /* 템플릿 클래스가 실제 인스턴싱 될 때
     * 부모 함수 호출이 유효한지 검사하도록 한다. */

    LoggingMsgSender<Company> lms1;
    lms1.sendClearMsg("aaa");

    LoggingMsgSender<SecurityCompany> lms2;
    lms2.sendClearMsg("aaa");

    return 0;
}
