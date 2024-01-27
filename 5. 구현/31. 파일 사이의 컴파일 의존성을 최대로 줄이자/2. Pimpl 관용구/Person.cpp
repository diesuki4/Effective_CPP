/*
 * 숨겨진 실제 구현 세부
 */
#include "Person.h"
#include "Date.h"
#include "Address.h"

/* 이제 구현 세부를 마음대로 변경해도
 * Person 의 사용자 측에서는 다시 컴파일하지 않아도 된다. */

struct PersonImpl
{
    string theName;
    Date theBirthDate;
    Address theAddress;
};

// 생성자를 호출하고
Person::Person(const string& name, const Date& birthDay, const Address& addr)
    : pImpl(new PersonImpl{name, birthDay, addr})
{
}

// 멤버에 접근하는 방식이 모두 동일하다.
string Person::name() const
{
    return pImpl->theName;
}

// 즉 접근 방식이 바뀌었을 뿐, 동작이 바뀐 것은 아니다.
Date Person::birthDate() const
{
    return pImpl->theBirthDate;
}

Address Person::address() const
{
    return pImpl->theAddress;
}
