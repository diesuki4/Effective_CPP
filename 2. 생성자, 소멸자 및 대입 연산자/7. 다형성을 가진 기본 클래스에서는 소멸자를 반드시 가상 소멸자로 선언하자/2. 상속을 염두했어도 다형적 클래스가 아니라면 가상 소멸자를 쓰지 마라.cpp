#include <iostream>

using namespace std;

/*
 * 상속을 염두했어도 다형적 클래스가 아니라면 가상 소멸자를 쓰지 마라
 */

/*
 * 복사를 방지하기 위해 상속하는 이런 클래스는
 * 애초에 부모 클래스를 통해 자식을 조작하려고 만들어진 것이 아니다.
 * 
 * 한 마디로, 자식 객체를 Uncopyable* 로 업 캐스팅해
 * 사용할 일이 없다는 뜻이다.
 * 
 * 따라서, 언제나 자식 객체를 통해 자식의 소멸자와 부모의 소멸자가 호출되므로
 * 부모를 가상 소멸자로 선언할 필요가 없다.
 */
class Uncopyable
{
    /*
     * 부모 클래스로 쓰일 수는 있지만, 다형성은 갖지 않는다.
     */
    Uncopyable(const Uncopyable&);
    Uncopyable& operator= (const Uncopyable&);

protected:
    Uncopyable() { }
    ~Uncopyable() { }
};

class HomeForSale : private Uncopyable
{
public:
    HomeForSale() { }
};

int main(int argc, char* argv[])
{

    return 0;
}
