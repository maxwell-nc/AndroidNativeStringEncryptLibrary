//
// JNI加密工具类
//
#include "EncryptUtils.h"


/*
 * 解密逻辑
 * 可以替换成任意解密算法，调用DecryptAPI
 */
__attribute__((section (".datas")))
jstring decryptInside(JNIEnv *env, jstring str){
    char* ecpStr;
    ecpStr = (char*)env->GetStringUTFChars(str,NULL);

    //解密用key: abc$%#1234
    //下面写法是tricks，防止静态编译寻找字符串（DCB指令）
    char* strop = (char[]){'a','b','c','$','%','#','\0'};
    int intop = 1234;

    //生成操作密码
    char opInt[strlen(strop)+sizeof(intop)];
    sprintf(opInt, "%s%d", strop, intop);

    //加密用利用日志查看生产的加密密钥
    #if DEBUG
        char enWord[] = "password";
        encrypt(enWord,opInt);
    #endif

    return env->NewStringUTF(decrypt(ecpStr,opInt));
}


/*
 * 解密字符串
 */
__attribute__((section ("datas")))
jstring decryptStr(JNIEnv *env, jobject object, ...){
    if(validApp(env,object)){//正版应用
        char* dest = new char[100];
        va_list pi;
        char *p;
        va_start(pi, object);
        int count = 0;
        while ((p = va_arg(pi, char *)) != fakePass){//通过va_arg(pi,char *)来提取参数列表中的变量
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
        jstring jstr = env->NewStringUTF(dest);
        free(dest);//回收
        return decryptInside(env,jstr);
    }
    //tricks 防止根据关键字hack
    char* failStr = (char[]){'e','r','r','o','r','\0'};
    return env->NewStringUTF(failStr);
}


jint JNI_OnLoad(JavaVM* vm,void* reserved){

    //防止调试
    ptrace(PTRACE_TRACEME,0,0,0);

    JNIEnv* env;
    if (vm->GetEnv((void**)(&env), JNI_VERSION_1_6) != JNI_OK){
        return -1;
    }
    assert(env != NULL);

    //寻找类
    jclass clazz = env->FindClass(regClazz);
    if (clazz == NULL) {
        return -1;
    }

    //注册方法
    int numMethods = sizeof(gMethods) / sizeof(gMethods[0]);
    if (env->RegisterNatives(clazz, gMethods, numMethods) < 0) {
        return -1;
    }

    return JNI_VERSION_1_6;
}
