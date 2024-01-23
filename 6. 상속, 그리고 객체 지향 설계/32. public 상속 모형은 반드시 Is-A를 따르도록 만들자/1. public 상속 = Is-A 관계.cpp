#include <iostream>

using namespace std;

/*
 * public 상속 = Is-A 관계
 */

// 모든 학생은 사람이지만
class Person {};

// 모든 사람이 학생은 아니다.
class Student : public Person {};

class ProtectedPerson : protected Person {};

void eat(const Person* p) {}
void study(const Student& s) {}

int main(int argc, char* argv[])
{
    Person p;
    Student s;
    ProtectedPerson pp;

    eat(&p);
    eat(&s);
    /* Is-A 관계인 public 상속이 아니면, 부모에 자식을 담을 수 없다.
     * 이유는 부모 부분에 접근이 불가능하기 때문.
     *
    eat(&pp); */

    // study(p);
    study(s);
    // study(pp);

    return 0;
}
