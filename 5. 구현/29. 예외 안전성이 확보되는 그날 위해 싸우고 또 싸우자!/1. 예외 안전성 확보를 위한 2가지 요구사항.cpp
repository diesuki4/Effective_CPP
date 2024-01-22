#include <iostream>
#include <mutex>

using namespace std;

/*
 * 예외 안전성 확보를 위한 2가지 요구사항
 * 
 * 1. 자원 누수가 없어야 한다.
 * 2. 자료구조가 더럽혀지지 않아야 한다.
 */

class Image
{
    istream& src;

public:
    Image(istream& imgSrc) : src(imgSrc) {}
};

class PrettyMenu
{
    mutex mtx;
    Image *bgImage;
    int imageChanges;

public:
    // 예외 안전성에 있어 매우 나쁜 함수
    void changeBackground(istream& imgSrc)
    {
        // 2. mutex 가 잠긴 상태로 자원 누수가 발생한다.
        mtx.lock();

        // 3. 새로운 이미지가 설정되지 않았는데, 기존 것이 삭제되는 등 자료가 더럽혀진다.
        delete bgImage;
        ++imageChanges;

        // 1. 여기서 예외가 발생하면
        bgImage = new Image(imgSrc);

        mtx.unlock();
    }

    // 예외에 좀 더 안전한 함수
    void changeBackground_Better(istream& imgSrc)
    {
        // 예외 발생 시에도 mutex 가 해제된다.
        lock_guard<mutex> lg(mtx);

        // 이 부분은 아직 해결되지 않았다.
        delete bgImage;
        ++imageChanges;

        bgImage = new Image(imgSrc);
    }
};

int main(int argc, char* argv[])
{
    

    return 0;
}
