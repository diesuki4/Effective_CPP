#include <iostream>

using namespace std;

/*
 * 사용자가 저지를 만한 실수를 인지하고 있어라
 */

/*
 * 어떤 인터페이스가 사용자가 생각한 대로 동작하지 않는다면
 * 그 코드는 컴파일되지 않는 게 맞다.
 * 
 * 제대로 쓰기엔 쉽고, 엉터리로 쓰기엔 어렵게 만들려면
 * 사용자가 저지를 만한 실수를 인지하고 있어야 한다.
 */

class Date
{
    int month;
    int day;
    int year;

public:
    Date(int m, int d, int y) : month(m), day(d), year(y) { }
};

int main(int argc, char* argv[])
{
    // 월, 일의 순서를 실수
    Date d1(30, 3, 1995);

    // 30을 40으로 오타
    Date d2(3, 40, 1995);

    return 0;
}
