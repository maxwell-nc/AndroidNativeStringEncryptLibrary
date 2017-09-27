//
// 工具函数
// 部分代码修改自 http://blog.csdn.net/jeanphorn/article/details/45560697
//
#include "Tools.h"


/*
 * 两个字符转换成一个字符，长度为原来的1/2
 */
static void Hex2Char(char *szHex, unsigned char *rch){
    int i;
    for(i=0; i<2; i++)
    {
        if(*(szHex + i) >='0' && *(szHex + i) <= '9')
            *rch = (*rch << 4) + (*(szHex + i) - '0');
        else if(*(szHex + i) >='a' && *(szHex + i) <= 'f')
            *rch = (*rch << 4) + (*(szHex + i) - 'a' + 10);
        else
            break;
    }
}


/*
 * 十六进制char* 转 Binary char*函数
 */
void HexStr2CharStr(char *pszHexStr, int iSize, char *pucCharStr){
    int i;
    unsigned char ch;
    if (iSize%2 != 0) return;
    for(i=0; i<iSize/2; i++)
    {
        Hex2Char(pszHexStr+2*i, &ch);
        pucCharStr[i] = ch;
    }
    pucCharStr[iSize/2]='\0';//防止越界
}


/*
 * 单个字符转十六进制字符串，长度增大2倍
 */
static void Char2Hex(unsigned char ch, char *szHex){
    int i;
    unsigned char byte[2];
    byte[0] = ch/16;
    byte[1] = ch%16;
    for(i=0; i<2; i++){
        if(byte[i] >= 0 && byte[i] <= 9)
            szHex[i] = '0' + byte[i];
        else
            szHex[i] = 'a' + byte[i] - 10;
    }
    szHex[2] = 0;
}


/*
 * 字符串转换函数，中间调用上面的函数
 */
void CharStr2HexStr(char *pucCharStr, int iSize,  char *pszHexStr){
    int i;
    char szHex[3];
    pszHexStr[0] = 0;
    for(i=0; i<iSize; i++)
    {
        Char2Hex(pucCharStr[i], szHex);
        strcat(pszHexStr, szHex);
    }
}



/*
 * 校验App签名，防止二次打包
 */
bool validApp(JNIEnv * env,jobject contextObject){
    jclass contextClass = env->FindClass("android/content/Context");
    jclass signatureClass = env->FindClass("android/content/pm/Signature");
    jclass packageNameClass = env->FindClass("android/content/pm/PackageManager");
    jclass packageInfoClass = env->FindClass("android/content/pm/PackageInfo");

    jmethodID getPackageManagerId = env->GetMethodID(contextClass, "getPackageManager","()Landroid/content/pm/PackageManager;");
    jmethodID getPackageNameId = env->GetMethodID(contextClass, "getPackageName","()Ljava/lang/String;");
    jmethodID getPackageInfoId = env->GetMethodID(packageNameClass, "getPackageInfo","(Ljava/lang/String;I)Landroid/content/pm/PackageInfo;");
    jmethodID hashCodeId = env->GetMethodID(signatureClass,"hashCode", "()I");

    //获取包信息
    jobject packageManagerObject =  env->CallObjectMethod(contextObject, getPackageManagerId);
    jstring packNameString =  (jstring)env->CallObjectMethod(contextObject, getPackageNameId);
    jobject packageInfoObject = env->CallObjectMethod(packageManagerObject, getPackageInfoId, packNameString, 64);

    //获取签名
    jfieldID signaturefieldID =env->GetFieldID(packageInfoClass,"signatures", "[Landroid/content/pm/Signature;");
    jobjectArray signatureArray = (jobjectArray)env->GetObjectField(packageInfoObject, signaturefieldID);
    jobject signatureObject =  env->GetObjectArrayElement(signatureArray,0);

    //获取当前包名
    const char* packName = env->GetStringUTFChars(packNameString, 0);

    //获取当前签名的hashcode
    jint hashCode = env->CallIntMethod(signatureObject, hashCodeId);

    logInfo("current hashcode:%d",hashCode);//这是当前应用签名的hashcode，替换下方的正版签名hashcode
    logInfo("current packageName:%s",packName);//这是当前应用包名，替换下方的正版签名

    //正版签名hashcode，换签名请修改这个
    //忽略hashcode碰撞问题（另外有包名校验）
    //必须是使用tricks写法，直接int可以从so中静态反编译找到（容易被替换）
    char* sign = (char[]){'-','4','9','8','5','7','6','2','6','3','\0'};
    int vaildSignHash = atoi(sign);

    //正版包名
    //可以任意分割，见nstrcat
    const char* validPackage =  nstrcat("com","co","m",".","gi","thub",".","max","we","ll",
                                        ".","nc",".","native","str","encrypt","com");

    //包名并且签名一致
    if(hashCode == vaildSignHash && strcmp(packName, validPackage) == 0){
        return true;
    }

    return false;
}


/*
 * 合并任意长度字符串
 * 第一个slat参数必须要出现在最后一个可变参数中，作为标记起始和结束符号（不能与中间字符重复）
 */
__attribute__((section ("datas")))
char* nstrcat(const char* slat,...){
    char* dest = new char[128];
    va_list pi;
    char *p;
    va_start(pi, slat);
    int count = 0;
    while ((p = va_arg(pi, char *)) != slat){//通过va_arg(pi,char *)来提取参数列表中的变量
        logInfo("va char:%s",p);
        if(count==0){
            strcpy(dest,p);
        }else{
            strcat(dest, p);
        }
        count++;
    }
    va_end(pi);
    logInfo("va str:%s",dest);
    return dest;
}
