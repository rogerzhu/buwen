#include <iostream>
#include <vector>
#include <string>

#include <memory>
#include <iomanip>
#include <unistd.h>
#include <dirent.h>
#include <sys/types.h>
#include <tuple>
#include <sys/stat.h>
#include <algorithm>
#include <cctype>

#include "cmdline.h"
#include "core/dirhelper.h"
#include "core/ImageFactory.h"


using namespace std;

int ProcessAllFiles(const string& strSrcDir,const string& strDstDir,const vector<string> &vFilter,int nChoice);
vector<string> GetAllFilesInDir(const string& strDir);
string GenerateDstPath(const string& strDstDir, string& strImageDate,int nChoice);
string UpperSuffix(string& strOriFileName);
string ConvertJPEGtoJPG(string& strOriFileName);

int main(int argc, char *argv[])
{
    cmdline::parser a;
    a.add<string>("source", 's', "source folder for the pictures that needs to be arranged.", true, "");
    a.add<string>("destination", 'd', "destination folder for the pictures that has been arranged.", true, "");
    a.add<int>("choice", 'c', "1.By Date, 2.By Month, 3.By Year", false, 1, cmdline::range(1, 3));

    a.parse_check(argc, argv); 

    string strSrcDir = a.get<string>("source");
    string strDstDir = a.get<string>("destination");
    int nChoice = a.get<int>("choice");

    vector<string> vFilter = {"JPG"};

    return ProcessAllFiles(strSrcDir,strDstDir,vFilter,nChoice);
    return 0;
}

vector<string> GetAllFilesInDir(const string& strDir)
{
    vector<string> vFileNames;
    struct stat s;
    struct dirent * filename;
    struct stat statbuf;

    lstat( strDir.c_str() , &s );
    if (! S_ISDIR( s.st_mode ))
    {
        return vFileNames;
    }
    DIR * dir = opendir( strDir.c_str() );
    if(  nullptr == dir )
    {
        return vFileNames;
    }

    while( ( filename = readdir(dir) ) != nullptr )
    {
        if (!strcmp(filename->d_name,".")||!strcmp(filename->d_name,".."))
            continue;
        string strFullPath = strDir + filename->d_name;
        if (strDir[strDir.length()-1] != '/')
        {
            strFullPath = strDir + "/" +filename->d_name;
        }
        lstat(strFullPath.c_str(),&statbuf);

        if (S_ISDIR(statbuf.st_mode))
        {
            GetAllFilesInDir(strDir);
        }

        vFileNames.emplace_back(filename->d_name);
     }

     return vFileNames;
}

int ProcessAllFiles(const string& strSrcDir,const string& strDstDir,const vector<string> &vFilter,int nChoice)
{
    vector<string> vStrImgFileNames = GetAllFilesInDir(strSrcDir);
    vector<ImageBase*> vAllFiles;

    string strFilePath,strFileName;

    ImageFactory imgFac;

    for (auto& strFileName:vStrImgFileNames)
    {
        string strFileNameWithUpperSuffix = UpperSuffix(strFileName);

        for (auto const &item:vFilter)
        {
            ImageBase * im = (ImageBase*)imgFac.CreateInstance(item);
            if (strFileNameWithUpperSuffix.find(item) != string::npos)
            {
                string strSrcPath = strSrcDir + strFileName;
                if(strSrcDir[strSrcDir.length()-1] != '/'){
                    strSrcPath = strSrcDir + "/" + strFileName;
                }
                string strImageDate = im->GetImageDate(strSrcPath.c_str());
                string strDstPath  = GenerateDstPath(strDstDir,strImageDate,nChoice);

                string strLog = "processing " + strSrcPath;
                
                DirHelper::CreateDir(strDstPath);
                DirHelper::MoveFile(strSrcPath,strDstPath + "/" + strFileName);
                cout<<"moving "<<strSrcPath<<" to "<<strDstPath<<endl;
            }
        }
    }

    return 0;
}

string GenerateDstPath(const string& strDstDir, string& strImageDate,int nChoice)
{
    string strFullDstPath = strDstDir;
    if (strFullDstPath[strFullDstPath.length()-1] != '/')
    {
        strFullDstPath += "/";
    }
    if (nChoice == 1)
    {
        strFullDstPath += strImageDate;
    }
    if (nChoice == 2)
    {
        strImageDate = strImageDate.substr(0,strImageDate.find_last_of("_"));
        strFullDstPath += strImageDate;
    }
    if (nChoice == 3)
    {
        strImageDate = strImageDate.substr(0,strImageDate.find("_"));
        strFullDstPath += strImageDate;
    }

    return strFullDstPath;
}

string UpperSuffix(string& strOriFileName)
{
    size_t nSuffixIndex = strOriFileName.find_last_of(".");
    if (nSuffixIndex == string::npos) return "";

    transform(strOriFileName.begin() + nSuffixIndex, strOriFileName.end(), strOriFileName.begin() + nSuffixIndex, ::toupper);

    if (strOriFileName.find("JPEG") != string::npos)
    {
        strOriFileName = ConvertJPEGtoJPG(strOriFileName);
    }

    return strOriFileName;
}

string ConvertJPEGtoJPG(string& strOriFileName)
{
    size_t nLen = strOriFileName.length();
    strOriFileName[nLen - 1] = '\0';
    strOriFileName[nLen - 2] = 'G';
    return strOriFileName;
}