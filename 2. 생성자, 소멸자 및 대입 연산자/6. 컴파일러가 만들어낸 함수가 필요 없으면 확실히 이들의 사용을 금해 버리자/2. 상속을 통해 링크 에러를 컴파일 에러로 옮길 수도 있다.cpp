#include <iostream>

using namespace std;

/*
 * 상속을 통해 링크 에러를 컴파일 에러로 옮길 수도 있다
 */

// 이 부모 클래스는 복사 방지의 역할만 한다.
class Uncopyable
{
    /*
     * private 으로 선언돼 있는 기존 둘을
     * 그대로 부모로 가져오면 된다.
     * 
     * 자식의 내부와 friend 에서의 복사를 링크 에러에서
     * 컴파일 에러로 옮기는 것이 목표이므로,
     * 
     * 부모에서는 링크 에러를 그대로 두어도 된다.
     */
    Uncopyable(const Uncopyable&);
    Uncopyable& operator= (const Uncopyable&);

protected:
    /*
     * 생성자와 소멸자를 protected 로 설정하면
     * 추상 클래스와 유사하게
     * 객체의 직접 생성을 막을 수 있다.
     */
    Uncopyable() { }
    ~Uncopyable() { }
};

// 부모의 어떤 것도 외부에 노출할 필요가 없으므로 private 상속한다.
class HomeForSale : private Uncopyable
{
public:
    HomeForSale() { }

    /*
     * 이제 컴파일러는 기본 복사 생성자와 기본 복사 대입 연산자를
     * 만들 수 없다.
     * 
     * 둘은 부모의 복사 생성자와 복사 대입 연산자를 자동으로 호출하는데,
     * private 이라서 접근할 수가 없기 때문이다.
     */
};

int main(int argc, char* argv[])
{
    HomeForSale home1;

    /*
     * 부모로 인해 기본 복사 생성자를 만들 수 없으므로
     * 막힌다.
     *
     * HomeForSale home2(home1);
     */

    HomeForSale home2;
    /*
     * 부모로 인해 기본 복사 대입 연산자를 만들 수 없으므로
     * 막힌다.
     *
     * home2 = home1;
     */

    const HomeForSale cHome3;
    /*
     * 상수 객체에 대한 복사 대입 연산자가
     * 존재하지 않는다.
     *
     * cHome3 = home1;
     */

    return 0;
}
