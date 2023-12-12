#include <iostream>

using namespace std;

/*
 * const 오버로드로 인한 중복을 줄이는 방법
 */

class CTextBlock
{
    string text;

public:
    CTextBlock(string text) : text(text) { }

    /*
     * 상수 객체를 위한 상수 함수 오버로드 때문에
     * 코드 중복이 발생한다.
     */
    const char& operator[] (size_t position) const
    {
        if (text.length() <= position)
            exit(-1);

        if (text[position] < 'A' || 'z' < text[position])
            exit(-1);

        cout << "text[" << position << "] 접근" << endl;

        return text[position];
    }

    char& operator[] (size_t position)
    {
/*
        if (text.length() <= position)
            exit(-1);

        if (text[position] < 'A' || 'z' < text[position])
            exit(-1);

        cout << "text[" << position << "] 접근" << endl;

        return text[position];
 *
 *      static_cast 를 통해 상수 레퍼런스 타입으로 변환해
 *      상수 함수가 호출될 수 있게 하고
 * 
 *      const_cast 를 통해 반환 값의 const 를 날려 반환하면 된다.
 * 
 *      비상수 객체가 const 함수를 호출하는 것이므로 안전성 문제는 없다.
 *      절대 상수 객체 -> 비상수 함수 호출 같은 역순으로는 구현하지 말 것!
 */
        return const_cast<char&>(
            static_cast<const CTextBlock&>(*this)[position]
        );
    }
};

int main(int argc, char* argv[])
{
    const CTextBlock cctb("Hello");

    cout << cctb[0] << endl;

    CTextBlock ctb(cctb);

    cout << ctb[2] << endl;

    return 0;
}
