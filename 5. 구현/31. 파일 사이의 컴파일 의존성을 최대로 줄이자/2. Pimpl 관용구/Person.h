#pragma once

// 표준 라이브러리는 전방 선언을 하면 안 된다.
#include <string>
#include <memory>

using namespace std;

// Pimpl 관용구를 이용해 구현 세부를 숨겼다.
class PersonImpl;
// 헤더 포함도 전방 선언으로 변경
class Date;
class Address;

/* 인터페이스만 제공하도록 변경됐다.
 *
 * Pimpl 에서 이런 클래스를 <핸들 클래스> 라고 한다. */
class Person
{
    /* 구현 세부를 숨김
     * 
     * 1. 포인터, 레퍼런스는 전방 선언만으로 충분하다. */
    shared_ptr<PersonImpl> pImpl;

public:
    Person(const string& name, const Date& birthDay, const Address& addr);

    // 2. 함수 선언에 사용되는 클래스도 전방 선언만으로 충분하다.
    string name() const;
    Date birthDate() const;
    Address address() const;
};
