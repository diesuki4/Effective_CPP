#include <iostream>

using namespace std;

/*
 * 값에 의한 전달과 상수객체 참조자에 의한 전달의 차이
 */

class Person
{
    string name = "";
    string address = "";

public:
    Person() { }
    virtual ~Person() { }
};

class Student : public Person
{
    string schoolName = "";
    string schoolAddress = "";

public:
    Student() { }
    ~Student() { }
};

/*
 * 엄청난 비용이 발생한다.
 * 
 * name 생성자
 * address 생성자
 * Person 생성자
 * schoolName 생성자
 * schoolAddress 생성자
 * Student 생성자
 * 
 * Student 소멸자
 * schoolAddress 소멸자
 * schoolName 소멸자
 * Person 소멸자
 * address 소멸자
 * name 소멸자
 * 
 * 하지만, s 는 사본이기 때문에
 * 원본에 변화가 없음을 보장할 수 있다.
 */
bool validateStudent(Student s)
{
    return true;
}

/*
 * 원본 객체를 그대로 사용하기 때문에
 * 생성, 소멸 비용이 전혀 발생하지 않는다.
 *
 * 하지만, s 는 원본 자체이기 때문에
 * const 를 붙여 원본에 변화가 없음을 보장해야 한다.
 * 
 * 또, 원본을 그대로 쓰기 때문에 사본에 비해
 * 자식 객체를 부모 타입으로 받을 떄
 * 
 * 객체 슬라이싱(복사손실, Object slicing) 문제가 발생하지 않는다.
 */
bool validateStudentEfficient(const Student& s)
{
    return true;
}

int main(int argc, char* argv[])
{
    Student plato;

    bool platoIsOk = validateStudent(plato);

    platoIsOk = validateStudentEfficient(plato);

    return 0;
}
