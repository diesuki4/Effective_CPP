#include <iostream>
#include <algorithm>

using namespace std;

/*
 * [] 연산자보다는 반복자를 활용하자
 */

// string 클래스를 대략적으로 구현한 클래스
class MyString
{
    size_t len;
    char* str;

public:
    MyString(const string& s) : len(s.length()), str(new char[len + 1])
    {
        const char* c_str = s.c_str();

        copy(c_str, c_str + len + 1, str);
    }

    // [] 연산자는 매 접근마다 역참조가 발생한다.
    char& operator[] (int i) const { return *(str + i); }

    // 반복자는 문자열 버퍼를 바로 가리킨다.
    char* begin() const { return str; }
    char* end()   const { return str + len + 1; }

    size_t length() const { return len; }

    ~MyString() { delete[] str; }
};

int main(int argc, char* argv[])
{
    string s = "Hello World !!";
    MyString ms(s);

    for (int i = 0; i < ms.length(); ++i)
        // 레퍼런스의 사용도 실제로는 포인터의 역참조이다.
        cout << ms[i];
    cout << endl;

    for (char* it = ms.begin(); it != ms.end(); ++it)
        // 문자열 버퍼를 바로 역참조한다.
        cout << *it;
    cout << endl;

    return 0;
}
