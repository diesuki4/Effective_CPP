/*
 * Directory.cpp
 */
#include <iostream>
using namespace std;
#include "Directory.h"
#include "FileSystem.h"

/*
 * Directroy 단위에서 비지역 FileSystem 정적 객체 tfs 를 사용하고 있지만,
 * 둘 사이의 초기화 순서는 정해질 수 없으므로
 *
 * tfs 가 초기화되어 있음을 보장할 수 없다.
 */
Directory::Directory(string dirName)
{
    size_t nDisks = tfs.numDisks();
}

// 비지역 Directory 정적 객체
Directory tempDir;

Directory& GetTempDir()
{
    static Directory td;
    return td;
}
