#include <iostream>

using namespace std;

/*
 * Undefined behavior
 */

int main(int argc, char* argv[])
{
    int *ptr = 0;

    // Read Access Violation : Null Pointer
    cout << *ptr << endl;

    char name[] = "Darla";

    // 유효하지 않은 인덱스 접근
    char c = name[10];

    return 0;
}
