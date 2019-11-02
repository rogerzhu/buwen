#ifndef REFLACTOR_H
#define REFLACTOR_H

#include <map>
#include <string>
#include <iostream>
#include <algorithm>
#include <cctype>

using namespace std;
typedef void* (*register_func)();

class Reflactor
{
public:
    static void* NewInstance(const string& strClassName){
        string strKeyName = strClassName;
        transform(strClassName.begin(), strClassName.end(), strKeyName.begin(), ::toupper);
        map<string ,register_func>::iterator it = m_register.find(strKeyName);
        if(it == m_register.end()){
            return nullptr;
        }
        else{
            return it->second();
        }
    }
    static void RegisterClass(const string& strClassName, register_func func){
        m_register.insert(pair<string,register_func>(strClassName, func)); 
    }
private:
    static map<string,register_func> m_register;
};

__attribute ((weak)) map<string,register_func>Reflactor::m_register;
#endif
