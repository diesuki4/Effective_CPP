#include <iostream>

using namespace std;

/*
 * 참조자와 상수 참조자의 오버로드 우선순위
 */

void Func(int& i)
{
    cout << "Func(int)" << endl;
}

void Func(const int& i)
{
    cout << "Func(const int)" << endl;
}

int main(int argc, char* argv[])
{
    int i = 3;
    const int ci = 5;

    // Func(int)
    Func(i);

    // Func(const int)
    Func(ci);

    return 0;
}
