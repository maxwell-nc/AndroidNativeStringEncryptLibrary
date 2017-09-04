//
// 加密工具类
//

#include <jni.h>
#include <stdio.h>
#include<stdarg.h>
#include <assert.h>
#include <string.h>
#include <sys/ptrace.h>
#include <android/log.h>

#include "Tools.h"
#include "DecryptAPI.h"

//假的密码，实际上是用于定位结束
static const char* fakePass = "gg0a07d3kjbkk";

jstring decryptStr(JNIEnv*, jobject, ...);

__attribute__((section ("datas")))
JNICALL jstring getSamplePass(JNIEnv *env, jclass clazz, jobject object){
    //这里的 616263898b8a 为加密后的字符串（可以任意分割）
    return decryptStr(env,object,"616","263","8","98","b8a",fakePass);
}

//要寻找的类：配置你的包名
static char regClazz[] = "com/github/maxwell/nc/encryptlib/EncryptUtils";

//要寻找的方法：配置你的方法
static JNINativeMethod gMethods[] = {
        { "getSamplePass", "(Ljava/lang/Object;)Ljava/lang/String;", (void*)getSamplePass },
};
