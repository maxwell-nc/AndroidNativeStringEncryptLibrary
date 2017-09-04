//
// 工具类头文件
//
#include <jni.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <android/log.h>

//是否需要打印Log
#define DEBUG false

//打印标签
#define TAG "JNI_LOG"

#if DEBUG
#define logInfo(...) __android_log_print(ANDROID_LOG_INFO,TAG ,__VA_ARGS__)
#define logErr(...) __android_log_print(ANDROID_LOG_ERROR,TAG ,__VA_ARGS__)
#else
#define logInfo(...)
#define logErr(...)
#endif

void HexStr2CharStr(char *pszHexStr, int iSize, char *pucCharStr);
void CharStr2HexStr(char *pucCharStr, int iSize, char *pszHexStr);
bool validApp(JNIEnv * env,jobject contextObject);
char* nstrcat(const char* ,...);
