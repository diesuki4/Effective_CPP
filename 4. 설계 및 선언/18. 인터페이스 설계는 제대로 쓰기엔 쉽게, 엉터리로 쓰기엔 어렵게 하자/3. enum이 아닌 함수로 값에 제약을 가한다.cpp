#include <iostream>

using namespace std;

/*
 * enum이 아닌 함수로 값에 제약을 가한다
 */

class Month
{
public:
    int val;

    /*
     * 유요한 월은 12개 뿐이므로,
     * 값의 제약에 함수를 고려할 수 있다.
     *
     * enum 은 int 처럼 사용될 수 있기에
     * 주의가 필요하다.
     */

    /*
     * 또한, Month g_Jan(1); 과 같이
     * 비지역 정적 객체를 사용해선 안 되는 이유는
     *
     * 항목 4 에서 설명한
     *
     * "별개의 파일에 정의된
     * 비지역 정적 객체들 사이에는
     * 상대적인 초기화 순서가 정해져 있지 않다"
     *
     * 를 참고하면 된다.
     *
     */
    static Month Jan() { return Month(1); }
    static Month Feb() { return Month(2); }
    static Month Mar() { return Month(3); }
    static Month Apr() { return Month(4); }
    static Month May() { return Month(5); }
    static Month Jun() { return Month(6); }
    static Month Jul() { return Month(7); }
    static Month Aug() { return Month(8); }
    static Month Sep() { return Month(9); }
    static Month Oct() { return Month(10); }
    static Month Nov() { return Month(11); }
    static Month Dev() { return Month(12); }

/*
 * 이제 외부에서는 함수를 통해 월을 확인하므로
 * 밖에서 생성자를 호출할 일은 없다.
 */
private:
    explicit Month(int m) : val(m) { }
};

struct Day   { int val; explicit Day(int d)  : val(d) { } };
struct Year  { int val; explicit Year(int y) : val(y) { } };

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
    // 유효하지 않은 월을 입력
    // DateSafe ds3(Month(15), Day(30), Year(1995));

    // 제대로 쓰임
    DateSafe ds3(Month::Mar(), Day(30), Year(1995));

    return 0;
}
