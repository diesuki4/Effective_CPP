#pragma once

#include <string>
#include "Person.h"
#include "Date.h"
#include "Address.h"

using namespace std;

// 구체 클래스 (Concrete class)
class RealPerson : public Person
{
    string theName;
    Date theBirthDate;
    Address theAddress;

public:
    RealPerson(const string& name, const Date& birthday, const Address& addr)
        : theName(name), theBirthDate(birthday), theAddress(addr)
    {
    }

    string name() const override { return theName; }
    Date birthDate() const override { return theBirthDate; }
    Address address() const override { return theAddress; }

    virtual ~RealPerson() {}
};
