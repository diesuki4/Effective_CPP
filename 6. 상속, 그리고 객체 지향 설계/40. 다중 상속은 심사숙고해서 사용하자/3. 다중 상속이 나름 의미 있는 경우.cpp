#include <iostream>

using namespace std;

/*
 * 다중 상속이 나름 의미 있는 경우
 * 
 * public 상속한 인터페이스 클래스, 그리고 인터페이스의 구현을 돕는 private 상속 클래스
 * 
 * 단일 상속으로 동등한 효과를 낼 수 있다면, 다중 상속을 안 쓰는 게 좋다.
 */

string getNameByPid(int pid) { return "DefaultName"; }

// 인터페이스 클래스
class IPerson
{
public:
    enum class Type
    {
        Student
    };

    // 팩토리 함수 or 가상 생성자
    static shared_ptr<IPerson> create(Type type, int pid);

    virtual string name() const = 0;

    virtual ~IPerson() {}
};

// IPerson 의 인터페이스를 구현하는 데 유용한 함수들을 포함한 클래스
class PersonInfo
{
public:
    explicit PersonInfo(int pid) : PersonId(pid)
    {
    }

    virtual string theName() const
    {
        string value;

        value += valueDelimOpen();
        value += getNameByPid(PersonId);
        value += valueDelimClose();

        return value;
    }

    virtual ~PersonInfo() {}

private:
    int PersonId;

    virtual string valueDelimOpen()  const { return "["; }
    virtual string valueDelimClose() const { return "]"; }
};

/* IPerson 의 인터페이스를 구현하는 데 유용한 기능들을
 * PersonInfo 클래스가 갖고 있다.
 * 
 * IPerson 과 Student 는 Realization 관계다.
 * 
 * PersonInfo 와 Student 는 Is-implemented-in-terms-of 관계다.
 *
 * PersonInfo 를 써서 Student 가 구현됐다.
 * 
 * 이 관계를 표현하는 <public 상속 + 객체 합성> 과 <private 상속> 중
 * 여기서는 <private 상속> 을 사용했다. */
class Student : public IPerson, private PersonInfo
{
public:
    explicit Student(int pid) : PersonInfo(pid)
    {
    }

    virtual string name() const override
    {
        return PersonInfo::theName();
    }

private:
    virtual string valueDelimOpen()  const override { return "<"; }
    virtual string valueDelimClose() const override { return ">"; }
};

shared_ptr<IPerson> IPerson::create(Type type, int pid)
{
    shared_ptr<IPerson> shPtr;

    switch (type)
    {
    case Type::Student: shPtr.reset(new Student(pid)); break;
    }

    return shPtr;
}

int main(int argc, char* argv[])
{
    shared_ptr<IPerson> shPtr = IPerson::create(IPerson::Type::Student, 100);

    cout << shPtr->name() << endl;

    return 0;
}
