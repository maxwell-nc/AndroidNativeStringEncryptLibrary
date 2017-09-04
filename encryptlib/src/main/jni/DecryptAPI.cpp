//
// 加密API
// 随便写的加密，!!!十分不安全!!!
// 这里只是提供两个接口，可以选择安全的加密方法
// 另外建议不要留下加密方法，防止碰撞
//
#include "DecryptAPI.h"


#if DEBUG
char* encrypt(char* content,char* password){
    int clen = strlen(content);
    int plen = strlen(password);

    logInfo("encrypt 1 clen:%d c:%s",clen,content);
    logInfo("encrypt 2 plen:%d p:%s",plen,password);

    for(int i=0;i<clen;i++){
        if(content[i]==password[i%plen]){//防止strlen遇到空格问题
            continue;
        }
        content[i]+=password[i%plen];
    }

    int c2len = strlen(content);
    logInfo("encrypt 3 c2len:%d c2:%s",c2len,content);
    //转换成hex
    char* szHex = new char[c2len*2+2];//两倍+‘\0’
    CharStr2HexStr(content,c2len,szHex);

    logInfo("encrypt 4 slen:%d s:%s",strlen(szHex),szHex);
	return szHex;
}
#endif


char* decrypt(char* content,char* password){

    int clen = strlen(content);
    int plen = strlen(password);

    logInfo("decrypt 1 clen:%d c:%s",clen,content);
    logInfo("decrypt 2 plen:%d p:%s",plen,password);

    //转换成char
    char* szChar = new char[clen/2+1];
    HexStr2CharStr(content,clen,szChar);

    int slen = strlen(szChar);
    logInfo("decrypt 3 slen:%d s:%s",slen,szChar);

    for(int i=0;i<slen;i++){
        if(szChar[i]==password[i%plen]){
            continue;
        }
        szChar[i]-=password[i%plen];
    }
    logInfo("decrypt 4 s2len:%d s2:%s",strlen(szChar),szChar);
	return szChar;
}





