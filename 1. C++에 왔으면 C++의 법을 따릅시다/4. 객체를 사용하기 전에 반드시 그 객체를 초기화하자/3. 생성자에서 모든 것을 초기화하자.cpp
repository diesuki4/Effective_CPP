#include <iostream>

using namespace std;

/*
 * 생성자에서 모든 것을 초기화하자
 */

class PhoneNumber {  };

class ABEntry
{
    string theName;
    string theAddress;
    PhoneNumber thePhone;
    int numTimesConsulted;

public:
    ABEntry(const string& name, const string& address, const PhoneNumber& phone)
    /*
     * 이것은 초기화다.
     * 복사 생성자가 호출된다.
     * 
     * 어떤 멤버든지 생성자의 본문이 실행되기 전에 초기화되어 있어야 한다.
     * 
     * 멤버 이니셜라이저를 사용하지 않아도
     * 객체 멤버는 기본 생성자가 호출되지만, 기본 타입은 초기화되리란 보장이 없다.
     * 
     */
    : theName(name), theAddress(address), thePhone(phone), numTimesConsulted(0)
    {
        /*
         * 이것은 대입이다.
         * 생성자 호출 전에 기본 생성자를 호출한 객체 멤버들에
         * 다시 대입 연산을 수행한다.
         * 
         * theName    = name;
         * theAddress = address;
         * thePhone   = phone;
         * numTimesConsulted = 0;
         * 
         */
    }
};

int main(int argc, char* argv[])
{


    return 0;
}
