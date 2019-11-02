#ifndef IMAGEBASE_H
#define IMAGEBASE_H
#include <string>
#include <vector>

using namespace std;


class ImageBase{
public:
    virtual const string GetImageDate(const char* fileName) = 0;
    const string GetMDateirectly(const char* fileName); // Get modified date, this would be used when the exif date is not avaiable.
    string m_fileName;
    vector<int> m_imgData;
};


#endif
