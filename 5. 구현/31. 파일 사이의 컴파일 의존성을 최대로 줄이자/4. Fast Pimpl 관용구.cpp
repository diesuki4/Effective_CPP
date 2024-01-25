/*
 * https://www.ikpil.com/679
 * http://www.gotw.ca/gotw/028.htm
 * https://en.wikibooks.org/wiki/More_C%2B%2B_Idioms/Fast_Pimpl
 */
#include <iostream>
#include <memory>

using namespace std;

/*
 * Fast Pimpl 관용구
 *
 * 인터페이스 객체 내에 스택 버퍼를 만들고 그곳에 구현 세부를 할당해
 * Heal Allocation, Deallocation 오버헤드를 줄인 개선 버전
 */

class Address {};
class Date {};

struct PersonImpl
{
    string theName;
    Date theBirthDate;
    Address theAddress;

    // shared_ptr 소멸 시 delete 가 호출되므로, 오버로딩이 필요하다.
    void operator delete (void* p)
    {
        /* 힙이 아니라 스택을 활용하므로, 해제하지 않는다.
        delete[] p; */
    }
};

class Person
{
    // 구현 세부의 크기
    static const size_t sizeOfImpl = sizeof(PersonImpl);
    // 스택 버퍼
    char buffer[sizeOfImpl];
    shared_ptr<PersonImpl> pImpl;

public:
    Person(const string& name, const Date& birthDay, const Address& addr)
        // 힙이 아닌 스택의 buffer 를 활용한다.
        : pImpl(new (buffer) PersonImpl{name, birthDay, addr})
    {
        pImpl->theName      = name;
        pImpl->theBirthDate = birthDay;
        pImpl->theAddress   = addr;
    }

    string name()     const { return pImpl->theName; }
    Date birthDate()  const { return pImpl->theBirthDate; }
    Address address() const { return pImpl->theAddress; }
};

int main(int argc, char* argv[])
{
    string s;
    Date d;
    Address a;

    Person p(s, d, a);

    return 0;
}
