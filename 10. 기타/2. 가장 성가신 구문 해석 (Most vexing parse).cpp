#include <iostream>

using namespace std;

/*
 * 가장 성가신 구문 해석 (Most vexing parse)
 *
 * 선언으로 해석할 수 있는 것은 항상 선언으로 해석해야 한다는 C++의 규칙
 */

class Widget { };

int main(int argc, char* argv[])
{
    // 프로그래머: 기본 생성자를 호출하는 Widget 타입의 객체 w
    // 컴파일러: Widget 객체를 반환하는 w() 라는 함수의 전방 선언
    Widget w();

    // 위의 Widget w(); 가 없다면, 컴파일 오류가 발생한다.
    w();

    return 0;
}

Widget w()
{
    cout << "w() 호출" << endl;

    return Widget();
}
