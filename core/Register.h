#ifndef REGISTER_H
#define REGISTER_H

#include "Reflactor.h"

using namespace std;
class Register
{
public:
    Register(const string& strClassName, register_func func){
        Reflactor::RegisterClass(strClassName,func);
    }
};

#define REGISTER_CLASS(strClassName) \
    class strClassName##Register{ \
    public: \
        static void* NewInstance(){ \
            return new strClassName; \
        } \
    private: \
        static const Register m_reg; \
    }; \
const Register strClassName##Register::m_reg(#strClassName,strClassName##Register::NewInstance);
#endif