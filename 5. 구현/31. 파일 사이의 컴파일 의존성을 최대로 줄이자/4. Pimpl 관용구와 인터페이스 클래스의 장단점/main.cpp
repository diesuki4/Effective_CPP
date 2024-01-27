/*
 * https://www.cppstories.com/2018/01/pimpl/
 * https://stackoverflow.com/questions/44483643/pimpl-idiom-memory-usage
 * https://www.reddit.com/r/cpp/comments/66t2qg/reduce_c_build_times_with_the_pimpl_idiom/
 * https://news.ycombinator.com/item?id=37015906
 */
#include <iostream>
#include "Date.h"
#include "Address.h"
#include "Person.h"

using namespace std;

/*
 * Pimpl 관용구와 인터페이스 클래스의 장단점
 * 
 * <장점>
 * 구현부로부터 인터페이스를 떼어 놓음으로써
 * 파일들 사이의 컴파일 의존성을 완화시킨다.
 * 
 * <단점>
 * Pimpl 의 경우 포인터의 생성, 소멸, 역참조, 크기 비용이 추가된다.
 * 또, 여러 작은 동적 할당들로 인해 메모리 단편화가 발생할 수 있다.
 * 인터페이스 클래스의 경우 동적 바인딩 비용이 추가된다.
 * 둘 다 구현부가 헤더에 존재하지 않기 때문에, inline 최적화가 힘들다.
 * 
 * 단점이 많아 쓰면 안 될 것 같지만, 그렇진 않다.
 * 런타임 비용이 따른다고 해서 가상 함수를 안 써야 하는 것은 아닌 것처럼.
 * 
 * 구현부가 바뀌었을 때 사용자에게 미칠 파급 효과를 최소화하기 위해서는
 * 둘 중 하나를 써야 한다.
 */

int main(int argc, char* argv[])
{
    string name;
    Date dateOfBirth;
    Address address;

    shared_ptr<Person> pp(Person::create(Person::Type::RealPerson, name, dateOfBirth, address));

    cout << pp->name() << endl;
    cout << pp->birthDate().toString() << endl;
    cout << pp->address().toString() << endl;

    return 0;
}
