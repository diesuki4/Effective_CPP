#include <iostream>
#include <algorithm>

using namespace std;

/*
 * 값에 의한 전달이 저비용이라고 가정해도 괜찮은 3가지 경우
 * 
 * 1. 기본 타입
 * 2. STL 반복자
 * 3. 펑터 (함수 객체)
 * 
 */

/*
 * 기본적으로 C++ 는 함수에 객체를 전달하거나 받을 때,
 * 값에 의한 전달(Pass by Value) 을 수행한다.
 *
 * 이것은 C에서 물려받은 특성 중 하나다.
 *
 * STL 반복자와 펑터도 마찬가지로
 * 값으로 전달되도록 설계돼 있다.
 *
 * 참고로, 반복자와 펑터를 설계할 때는
 * 반드시 2가지를 고려해야 한다.
 *
 * 1. 복사 효율이 높아야 한다.
 * 2. 복사손실 문제에 노출되지 않아야 한다.
 */

/*
 * 레퍼런스는 컴파일러에 의해
 * 포인터로 번역된다.
 */
void StringFunc(const string& s)
{
    return;
}

/*
 * 따라서, 포인터와 크기가 동일한 기본 타입에 대해서는
 * 레퍼런스보다 값으로 넘기는 게 효율적일 때가 많다.
 */
void NumFunc(int num)
{
    return;
}

/*
 * 그렇다고 크기가 작은 타입을 항상 값으로 전달하는 게
 * 효율적이 것은 아니다.
 */
class MyString
{
    /*
     * 이 객체의 크기는 x64 에서의 포인터 크기와 동일한
     * 고작 8바이트지만
     */
    size_t len;
    char* str;

public:
    MyString(const string& s) : len(s.length()), str(new char[len + 1])
    {
        const char* c_str = s.c_str();

        copy(c_str, c_str + len + 1, str);
    }

    /*
     * 값 타입 객체의 인자 전달, 반환은 항상
     * 복사 생성자를 통하기 때문에,
     * 
     * 복사 생성자에서 포인터가 가리키는 대상도 복사하기 위한
     * 깊은 복사를 진행하게 되면, 비용은 8바이트보다 훨씬 크다.
     */
    MyString(const MyString& rhs)
    {
        len = rhs.len;

        str = new char[len + 1];

        copy(rhs.str, rhs.str + len + 1, str);
    }

    char& operator[] (int i) const { return *(str + i); }

    char* begin() const { return str; }
    char* end()   const { return str + len + 1; }

    size_t length() const { return len; }

    ~MyString() { delete[] str; }
};

/*
 * 그럼 이런 타입은 값으로 전달하는 게 더 좋을까?
 * 
 * 그렇지 않다.
 * 
 * 컴파일러 중에는 기본 타입과 사용자 정의 타입을
 * 아예 다르게 취급하는 것들도 있다.
 * 
 * int 형은 레지스터에 넣어 주지만,
 * 아래 같은 클래스는 넣지 않는 것이다.
 * 
 * 따라서, 레퍼런스는 포인터로 번역되고
 * 포인터는 확실히 레지스터에 들어갈 수 있기 때문에
 * 
 * 차라리 레퍼런스를 쓰는 게 낫다.
 */
class LightWeightClass
{
    int data;
};

int main(int argc, char* argv[])
{
    /*
     * 크기가 작은 사용자 정의 타입을
     * 항상 값으로 전달할 수 없는 또 다른 이유는,
     * 
     * 구현 환경마다 크기가 다를 수 있다는 것이다.
     * 
     * string 클래스만 해도 환경마다 최대 7배까지
     * 크기가 차이난다고 한다.
     */
    cout << sizeof(string) << endl;

    return 0;
}
