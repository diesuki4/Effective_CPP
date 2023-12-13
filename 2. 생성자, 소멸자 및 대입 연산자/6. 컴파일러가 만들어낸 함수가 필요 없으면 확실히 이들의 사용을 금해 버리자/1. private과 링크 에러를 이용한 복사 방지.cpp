#include <iostream>

using namespace std;

/*
 * private과 링크 에러를 이용한 복사 방지
 */

// 부동산 프로그램에서 동일한 집이 2개일 수는 없다.
class HomeForSale
{
private:
    /*
     * 어떤 클래스에서 특정 기능을 막는 방법은
     * 그런 기능을 제공하는 함수를 선언하지 않는 것이다.
     *
     * 기본 복사 생성자, 기본 복사 대입 연산자는
     * 컴파일러가 자동으로 만들 수도 있다.
     */

    /*
     * 컴파일러가 자동으로 만들지 못하도록 직접 정의하되,
     * private 으로 선언해 외부에서 호출을 막는다.
     */
    HomeForSale(const HomeForSale&);
    /*
     * 또, 함수의 정의부를 일부러 누락해서
     * 내부나 friend 에서 호출하면 링크 에러가 발생하도록 한다.
     *
     * 컴파일 에러는 발생하지 않고
     * iostream 라이브러리 등에서 실제로도 많이 쓰이는 기법이다.
     * 
     * 인자의 이름을 적지 않으면
     * 정의부가 존재하지 않는 함수라는 걸 알릴 수 있다.
     */
    HomeForSale& operator= (const HomeForSale&);

    /*
     * 컴파일러는 상수 객체에 대한 기본 복사 대입 연산자는
     * 만들지 않는다.
     * 
     * const HomeForSale& operator= (const HomeForSale&) const;
     */
public:
    HomeForSale() { }
};

int main(int argc, char* argv[])
{
    HomeForSale home1;

    /*
     * 복사 생성이 막힌다.
     *
     * HomeForSale home2(home1);
     */

    HomeForSale home2;
    /*
     * 복사 대입이 막힌다.
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
