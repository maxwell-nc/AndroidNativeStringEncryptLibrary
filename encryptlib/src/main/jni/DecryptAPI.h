//
// 加密API
//

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>

#include "Tools.h"

#if DEBUG
/**
 * 加密接口
 */
__attribute__((section (".datas")))
char* encrypt(char* content,char *password);
#endif

/**
 * 解密接口
 */
__attribute__((section (".datas")))
char* decrypt(char* content,char *password);