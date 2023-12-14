#include <iostream>
#include <vector>

using namespace std;

/*
 * 흔한 자기대입 실수들
 */

class Widget { };

int main(int argc, char* argv[])
{
    Widget w;

    // 이런 실수를 하는 사람은 잘 없다.
    w = w;

    int i = 3, j = 3;
    vector<Widget> v(4);

    // 프로그래머 모르게 발생할 수 있는 실수다.
    v[i] = v[j];

    Widget *p = &w, *q = &w;

    // 마찬가지로 발생할 수 있는 실수다.
    *p = *q;
}
