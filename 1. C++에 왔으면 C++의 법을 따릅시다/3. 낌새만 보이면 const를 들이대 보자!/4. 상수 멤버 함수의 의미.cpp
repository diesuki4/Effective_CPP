#include <iostream>

using namespace std;

/*
 * 상수 멤버 함수의 의미
 */

class TextBlock
{
    string text;

public:
    TextBlock(string text) : text(text) { }

    // 멤버 함수의 const 선언은 오버로드 조건이 된다.
    char& operator[] (size_t position)
    {
        return text[position];
    }

    /*
     * 멤버 함수의 const 선언은
     * 상수 객체에 의해 호출될 함수라는 것을 알리는 것이다.
     * 
     * 1. 객체 변경이 가능한 함수가 어떤 것인지 알 수 있다.
     * 2. 상수 객체가 사용할 수 있도록 한다.
     * (상수 객체는 일반 함수를 호출할 수 없기 때문)
     */
    const char& operator[] (size_t position) const
    {
        return text[position];
    }

    // const 함수는 일반 객체도 호출할 수 있다.
    void Show() const
    {
        cout << text << endl;
    }
};

int main(int argc, char* argv[])
{
    TextBlock textBlock("HelloWorld!");

    textBlock[1] = 'i';
    textBlock.Show();

    const TextBlock cTextBlock("Programming!");

    /*
     * const 오버로드에서도
     * 반환 값이 const 가 아니라면
     * 다음이 허용된다.
     * 
     * cTextBlock[2] = 'j';
     */

    cTextBlock.Show();

    return 0;
}
