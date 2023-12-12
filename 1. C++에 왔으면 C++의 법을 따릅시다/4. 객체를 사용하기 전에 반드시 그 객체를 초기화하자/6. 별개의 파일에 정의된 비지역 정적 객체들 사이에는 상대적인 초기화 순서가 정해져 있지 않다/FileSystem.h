#pragma once

class FileSystem
{
    int nDisks;

public:
    size_t numDisks() const;
};

extern FileSystem tfs;

FileSystem& GetTfs();
