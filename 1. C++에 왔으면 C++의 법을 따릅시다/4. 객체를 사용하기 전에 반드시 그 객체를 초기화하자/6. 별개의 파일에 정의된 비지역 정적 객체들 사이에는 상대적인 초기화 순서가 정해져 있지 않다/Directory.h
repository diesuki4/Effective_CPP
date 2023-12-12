#pragma once

class Directory
{
public:
    Directory(string dirName = "New Folder");
};

extern Directory tempDir;

Directory& GetTempDir();
