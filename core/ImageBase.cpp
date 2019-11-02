#include "ImageBase.h"
#include <sys/stat.h>

const string ImageBase::GetMDateirectly(const char* fileName){
    struct stat buf;
    stat( fileName, &buf );

    char* format = "%Y_%m_%d";
    char caTime[50];
    strftime(caTime,sizeof(caTime),format,localtime(&buf.st_mtime));
    string strModifyTime(caTime);
    return strModifyTime;
}
