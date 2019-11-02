#ifndef DIRHELPER_H
#define DIRHELPER_H
#include <string>

using namespace std;

class DirHelper
{
public:
    explicit DirHelper();
    static int MoveFile(const string& strSrcPath,const string& strDestPath);
    static int CreateDir(const string& strDirName);
};

#endif // DIRHELPER_H
