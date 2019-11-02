#ifndef IMAGEFACTORY_H
#define IMAGEFACTORY_H
#include "ImageBase.h"
#include "Reflactor.h"

class ImageFactory
{
public:
    ImageBase* CreateInstance(const string& strName){
        return (ImageBase*)Reflactor::NewInstance(strName);
    }
};
#endif