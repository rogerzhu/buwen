#include "dirhelper.h"

#include <iomanip>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <sys/stat.h>

DirHelper::DirHelper()
{

}

int DirHelper::CreateDir(const string& strDirName)
{
    int nCreate = -1;
    if(access(strDirName.c_str(),0)){
        nCreate = mkdir(strDirName.c_str(),S_IRUSR | S_IWUSR | S_IXUSR | S_IRWXG | S_IRWXO);
    }

    return nCreate;
}

int DirHelper::MoveFile(const string& strSrcPath,const string& strDestPath){
    char cBuff[1024];
    int nLen;

    rename(strSrcPath.c_str(),strDestPath.c_str());

    return 0;
}
