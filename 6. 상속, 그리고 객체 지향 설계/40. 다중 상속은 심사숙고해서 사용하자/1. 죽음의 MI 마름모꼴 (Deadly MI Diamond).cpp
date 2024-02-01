#include <iostream>

using namespace std;

/*
 * 죽음의 MI 마름모꼴 (Deadly MI Diamond)
 *
 * 둘 이상의 부모 클래스로부터 같은 이름을 물려받을 가능성이 생긴다.
 * 
 * 가상 상속을 통해 해결할 수 있다.
 */

namespace mi_ambiguous
{
    class BorrowableItem
    {
    public:
        void checkOut() {}
    };

    class ElectronicGadget
    {
    private:
        bool checkOut() const {}
    };

    class MP3Player : public BorrowableItem, public ElectronicGadget
    {
    };
}

namespace diamond_inheritance
{
    class File
    {
    // 예시를 든 것일 뿐, 이렇게 쓰면 안 된다.
    public:
        string fileName;
    };

    class InputFile : public File {};
    class OutputFile : public File {};

    class IOFile : public InputFile, public OutputFile {};
}

namespace diamond_virtual_inheritance
{
    class File
    {
    public:
        string fileName;
    };

    /* 표준 라이브러리의 basic_ios, basic_istream, basic_ostream, basic_iostream 이
     * 이렇게 가상 상속으로 구현되어 있다. */
    class InputFile : virtual public File {};
    class OutputFile : virtual public File {};

    class IOFile : public InputFile, public OutputFile {};
}

int main(int argc, char* argv[])
{
    {
        using namespace mi_ambiguous;

        MP3Player mp3;

        /* MP3Player::checkOut() 이 모호합니다.
         *
         * public 인 BorrowableItem::checkOut() 을
         * 써야함이 자명한데도 모호성이 생긴다.
         *
         * C++ 의 함수 결정 규칙은 최적으로 일치하는(Best-match)
         * 함수를 먼저 확인한 후 접근성을 확인하기 때문.
         *
         * 접근성을 확인하기 전에 모호성이 생겨버린 것이다.
        mp3.checkOut(); */
        mp3.BorrowableItem::checkOut();
    }
    cout << endl;
    {
        using namespace diamond_inheritance;

        IOFile ioFile;

        /* IOFile::fileName 이 모호합니다.
         *
         * 함수뿐만 아니라, 변수도 마찬가지다.
         *
        cout << ioFile.fileName << endl; */
        cout << ioFile.OutputFile::fileName << endl;
    }
    cout << endl;
    {
        using namespace diamond_virtual_inheritance;

        IOFile ioFile;

        // 가상 상속에서는 이런 모호성 문제가 해결된다.
        cout << ioFile.fileName << endl;
    }

    return 0;
}
