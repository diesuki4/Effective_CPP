#include <iostream>
#include <mutex>
#include <algorithm>
#include <set>
#include <list>

using namespace std;

/*
 * has-a(...는 ...를 가짐) 혹은 is-implemented-in-terms-of(...는 ...를 써서 구현됨)를 모형화할 때는 객체 합성을 사용하자
 */

class Address {};
class PhoneNumber {};

/* 실세계를 본 뜬 응용 영역(Application domain) 에 속하는 개체
 * 응용 영역에서 일어나는 Composition 은 Has-A 관계다. */
class Person
{
    // Has-A 관계인 Composition
    string name;
    Address address;
    PhoneNumber voiceNumber;
    PhoneNumber faxNumber;
};

/* 시스템 구현만을 위한 인공물인 구현 영역(Implementation domain) 에 속하는 개체
 * 구현 영역에서 일어나는 Composition 은 Is-implemented-in-terms-of 관계다. */
class SomeClass
{
    // Is-implemented-in-terms-of 관계인 Composition
    char buffer[1024];
    mutex mtx;
    set<int> st;
};

/*
 * C++ 에서 set 은 레드-블랙 트리로 구현되어 있으므로, 원소 1개당 포인터 3개의 오버헤드를 갖는다.
 * 자기 자신, 왼쪽 자식, 오른쪽 자식
 *
 * 따라서, 속도보다 공간이 중요한 상황을 가정해
 * list 를 활용해 커스텀 set 을 구현한 경우다. */
class Set
{
    // Is-implemented-in-terms-of 관계인 Composition
    list<int> rep;

public:
    bool member(const int& item) const
    {
        return find(begin(rep), end(rep), item) != end(rep);
    }

    void insert(const int& item)
    {
        if (!member(item))
            rep.push_back(item);
    }

    void remove(const int& item)
    {
        if (list<int>::iterator it = find(begin(rep), end(rep), item); it != end(rep))
            rep.erase(it);
    }

    size_t size() const
    {
        return rep.size();
    }
};

int main(int argc, char* argv[])
{


    return 0;
}
