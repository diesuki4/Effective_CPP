#include <iostream>

using namespace std;

/*
 * 기본 타입은 임시 객체 대입이 불가능하다
 */

class TextBlock
{
    string text;

public:
    TextBlock(string text) : text(text) { }

    char& GetChar(size_t position)
    {
        return text[position];
    }

    /*
     * char& 가 아닌 char 를 반환하게 되면
     * 다음이 불가능해진다.
     *
     * textBlock[3] = 'A';
     *
     * 객체가 아닌 기본 타입이기 때문
     */
    char operator[] (size_t position)
    {
        return text[position];
    }

    /*
     * 객체는 값을 반환해도
     * 대입이 가능하다.
     */
    TextBlock GetCopy()
    {
        return *this;
    }
};

int main(int argc, char* argv[])
{
    TextBlock textBlock("HelloWorld!");

    textBlock.GetChar(1) = 'i';

    // 값 형식에, 기본 타입이므로 불가
    // textBlock[2] = 'o';

    TextBlock textBlock2("Programming!");

    // 값 형식이지만, 객체이므로 가능
    textBlock.GetCopy() = textBlock2;

    return 0;
}
