#ifndef JPG_H
#define JPG_H

#include "ImageBase.h"
using namespace std;

#define BYTE_ORDER_BIG 0x4d4d
#define BYTE_ORDER_LITTLE 0x4949
#define TAG_DATE_PART1 0x90
#define TAG_DATE_PART2 0x03
#define BUFFER_SIZE 1024

class JPG:public ImageBase{
public:
    static const string TypeName(){return "jpg";}
    const string GetImageDate(const char* fileName);

};

#endif
