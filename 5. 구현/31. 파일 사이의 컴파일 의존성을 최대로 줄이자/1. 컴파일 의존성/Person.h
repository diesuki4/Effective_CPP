#pragma once

#include <string>
/* 이 헤더들이 문제다.
 *
 * 이들로 인해 컴파일 의존성이 강해져서
 * 이들 중 일부, 혹은 이들과 관련된 또 다른 헤더가 바뀌기만 해도
 *
 * 이 헤더를 포함해 Person 클래스를 쓰는 다른 파일들까지
 * 몽땅 다시 컴파일되어야 한다. */
#include "Date.h"
#include "Address.h"

using namespace std;

/* C++의 클래스 정의는 인터페이스 뿐만 아니라
 * 구현 세부 사항까지 상당히 많이 지정하고 있다. */
class Person
{    
    string theName;      // 구현 세부 사항
    Date theBirthDate;   // 구현 세부 사항
    Address theAddress;  // 구현 세부 사항

public:
    Person(const string& name, const Date& birthDay, const Address& addr);

    string name()     const;
    Date birthDate()  const;
    Address address() const;
};
