#include "jpg.h"
#include "Register.h"

const string JPG::GetImageDate(const char* fileName){
    FILE* fp = fopen(fileName,"rb");  
    string strCreatedDate = "";
    if(fp){
        unique_ptr<char[]> ipFirstN(new char[BUFFER_SIZE]);
        fread(ipFirstN.get(),BUFFER_SIZE,sizeof(char),fp);
        int nStartPos = 0;
        unsigned short nTagDate = static_cast<unsigned short>(TAG_DATE_PART1<<8 | TAG_DATE_PART2);
        bool bLittle = false;
        //int nOffset = 0;
        
        for(int i = 0; i < BUFFER_SIZE/2; i += 2){
            unsigned short value = ((ipFirstN[i]<<8)&0xff00) | (ipFirstN[i+1]&0xff);
            if(value == BYTE_ORDER_BIG || value == BYTE_ORDER_LITTLE){
                nStartPos = i;
                bLittle = (value == BYTE_ORDER_LITTLE);
            }
            if(bLittle)
                nTagDate = TAG_DATE_PART2<<8 | TAG_DATE_PART1;

            if(value == nTagDate){
                unsigned short v1 = ((ipFirstN[i+8]<<8)&0xff00) | (ipFirstN[i+9]&0xff);
                unsigned short v2 = ((ipFirstN[i+10]<<8)&0xff00) | (ipFirstN[i+11]&0xff);
                if(bLittle){
                    v1 = ((ipFirstN[i+9]<<8)&0xff00) | (ipFirstN[i+8]&0xff);
                    v2 = ((ipFirstN[i+11]<<8)&0xff00) | (ipFirstN[i+10]&0xff);
                }
                unsigned int nRealVal = v1<<16 | v2;
                if(bLittle){
                    nRealVal = v2<<16 | v1;
                }
                for(int j = 0; j < 10; j++){ 
                     char chDigit = static_cast<char>(ipFirstN[nRealVal+nStartPos+j]);
                     if(chDigit == ':'){
                         chDigit = '_';
                     }
                     strCreatedDate += chDigit;
                }
                break;      
            }     
        }
    }
    fclose(fp);
    if(strCreatedDate == ""){
        strCreatedDate = ImageBase::GetMDateirectly(fileName);
    }
    return strCreatedDate;
}

REGISTER_CLASS(JPG);
