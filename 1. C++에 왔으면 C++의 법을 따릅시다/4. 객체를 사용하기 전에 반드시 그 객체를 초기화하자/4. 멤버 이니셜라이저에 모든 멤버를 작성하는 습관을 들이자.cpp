#include <iostream>

using namespace std;

/*
 * 멤버 이니셜라이저에 모든 멤버를 작성하는 습관을 들이자
 */

class PhoneNumber {  };

class ABEntry
{
    string theName;
    string theAddress;
    PhoneNumber thePhone;
    int numTimesConsulted;

public:
    ABEntry()
    /*
    * 멤버 이니셜라이저에 적어주지 않아도
    * 객체 멤버는 기본 생성자가 호출되지만, 기본 타입은 초기화되리란 보장이 없다.
    *
    * 따라서, 나중에 기본 타입을 빼먹어 문제가 생기기보다는
    * 객체든 기본 타입이든 그냥 빼먹지 말고 모두 이니셜라이저에 올려주자.
    */

    // 객체 멤버를 인자 없이 올려줄 때는
    // 아래처럼 비워두면 된다.
    : theName(), theAddress(), thePhone(), numTimesConsulted(0) { }
};

int main(int argc, char* argv[])
{


    return 0;
}
