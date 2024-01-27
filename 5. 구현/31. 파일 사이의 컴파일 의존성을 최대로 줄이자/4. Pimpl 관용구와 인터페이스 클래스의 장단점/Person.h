#pragma once

#include <string>
#include <memory>

using namespace std;

class Date;
class Address;

/* Pimpl 에서 인터페이스 클래스로 변경됐다.
 *
 * Pimpl 과 마찬가지로, 자식 클래스의 구현 세부 변경으로는
 * 재컴파일이 일어나지 않는다. */
class Person
{
public:
    enum class Type
    {
        RealPerson
    };

    virtual string name()     const = 0;
    virtual Date birthDate()  const = 0;
    virtual Address address() const = 0;

    // 팩토리 함수 or 가상 생성자
    static shared_ptr<Person> create(Type type, const string& name, const Date& birthday, const Address& addr);

    virtual ~Person() {}
};
