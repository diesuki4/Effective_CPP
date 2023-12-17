#include <iostream>

using namespace std;

/*
 * 암시적 형 변환이 불가능한 레퍼 타입을 만든다
 */

/*
 * 암시적 형 변환이 불가능한 explicit 생성자의
 * 간단한 레퍼(Wrapper) 타입을 만든다.
 */
struct Month { int val; explicit Month(int m) : val(m) { } };
struct Day   { int val; explicit Day(int d)   : val(d) { } };
struct Year  { int val; explicit Year(int y)  : val(y) { } };
/*
 * 클래스 생성자에서 이 타입들을 인자로 받도록 한다.
 */
class DateSafe
{
    int month;
    int day;
    int year;

public:
    DateSafe(const Month& m, const Day& d, const Year& y) : month(m.val), day(d.val), year(y.val) { }
};

int main(int argc, char* argv[])
{
    // 암시적 형 변환 불가
    // DateSafe ds1(30, 3, 1995);

    // 순서 실수 방지
    // DateSafe ds2(Day(30), Month(3), Year(1995));

    // 제대로 쓰임
    DateSafe ds3(Month(3), Day(30), Year(1995));

    return 0;
}
