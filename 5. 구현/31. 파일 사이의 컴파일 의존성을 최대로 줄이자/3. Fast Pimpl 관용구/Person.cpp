/*
 * https://www.ikpil.com/679
 * http://www.gotw.ca/gotw/028.htm
 */
#include "Person.h"
#include "Date.h"
#include "Address.h"

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

Person::Person(const string& name, const Date& birthDay, const Address& addr) : pImpl(nullptr)
{
    // 구현 세부가 buffer 에 들어갈 수 없으면 오류
    static_assert(sizeof(PersonImpl) <= SIZE, "Object can't fit into buffer");
    // 힙이 아닌 스택의 buffer 를 활용한다.
    pImpl.reset(new (buffer) PersonImpl{name, birthDay, addr});
}

string Person::name() const
{
    return pImpl->theName;
}

Date Person::birthDate() const
{
    return pImpl->theBirthDate;
}

Address Person::address() const
{
    return pImpl->theAddress;
}
