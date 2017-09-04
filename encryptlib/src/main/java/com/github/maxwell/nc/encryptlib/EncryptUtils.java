package com.github.maxwell.nc.encryptlib;

/**
 * 字符串加密工具类
 */
public class EncryptUtils {

    static {
        System.loadLibrary("maxwell_encrypt");
    }

    /**
     * 获取密码例子<br/>
     * 原密码：abcefg
     */
    public static native String getSamplePass(Object context);

}
