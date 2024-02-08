#include "Person.h"
#include "RealPerson.h"

/* 레퍼런스, 포인터 타입에 대해서는 전방 선언만으로도
 * 크기를 알 수 있으므로 충분하다. */
shared_ptr<Person> Person::create(Type type, const string& name, const Date& birthday, const Address& addr)
{
    shared_ptr<Person> shPtr;

    switch (type)
    {
    case Type::RealPerson: shPtr.reset(new RealPerson(name, birthday, addr)); break;
    }

    return shPtr;
}
