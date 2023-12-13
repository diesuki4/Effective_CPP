#include <iostream>

using namespace std;

/*
 * STL 컨테이너를 상속해 쓰지 마라
 */

/*
 * vector, list, set, unordered_map 등 STL 컨테이너는
 * 상속을 염두에 두지 않아 가상 소멸자가 아니기 때문
 */
class MyString : public string
{
public:
    MyString(const char* text) : string(text) { cout << "MyString::생성자" << endl; }
    ~MyString() { cout << "MyString::소멸자" << endl; }
};

int main(int argc, char* argv[])
{
    string* ps = static_cast<string*>(new MyString("Hello World !!"));

    cout << *ps << endl;

    // MyString 의 소멸자가 호출되지 않는다.
    delete ps;

    return 0;
}
