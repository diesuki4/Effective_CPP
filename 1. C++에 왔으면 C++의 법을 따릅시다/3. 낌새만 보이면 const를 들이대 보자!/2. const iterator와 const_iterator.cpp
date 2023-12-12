#include <iostream>
#include <vector>

using namespace std;

/*
 * const iterator와 const_iterator
 */

int main(int argc, char* argv[])
{
    vector<int> vec(5);

    // int* const iter
    // 처럼 동작한다.
    const vector<int>::iterator iter = vec.begin();

    *iter = 10;
    // 불가
    // ++iter;

    // const int* iter
    // 처럼 동작한다.
    vector<int>::const_iterator cIter = vec.begin();

    // 불가
    // *cIter = 10;
    ++cIter;

    return 0;
}
