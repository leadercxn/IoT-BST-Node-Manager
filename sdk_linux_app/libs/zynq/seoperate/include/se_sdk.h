#ifndef __SE_SDK_H__
#define __SE_SDK_H__

//#include "errcode.h"

#ifdef __cplusplus
extern "C" {
#endif


/**
 * 枚举功能：对称加密算法类型
 */
typedef enum 
{
    SYMMETRICAL_DES = 0,
    SYMMETRICAL_AES,
    SYMMETRICAL_SM4,
    SYMMETRICAL_SM1,

    SYMMETRICAL_ID
}E_SYMMETRICAL_TYPE;

/**
 * 枚举功能：非对称加密算法类型
 */
typedef enum 
{
    ASYMMETRICAL_ECC = 0,
    ASYMMETRICAL_RSA,
    ASYMMETRICAL_SM2,

    ASYMMETRICAL_ID
}E_ASYMMETRICAL_TYPE;

typedef struct
{
    char            cDev[64];   //spi 设备节点路径
    unsigned int    uiMode;     //spi 设备模式
    unsigned char   ucBits;     //spi 单字位数
    unsigned int    uiMaxSpeed; //spi 最高传输速率
}SPI_DEV_S;
/*********************************************************************************************************************
//============================================= 对称加密算法的算法类型枚举 ==========================================
*********************************************************************************************************************/
/**
 * 枚举功能：3DES 加解密算法类型
 * 枚举说明：当加解密函数的对称加密算法类型为 SYMMETRICAL_3DES（即函数 typeID == SYMMETRICAL_3DES）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_DES_CBC = 0,
    ALG_DES_ECB
}E_DES_CRYPT_ALG_MODE;

/**
 * 枚举功能：3DES MAC计算或验证的算法类型
 * 枚举说明：当MAC 计算或验证函数的对称加密算法类型为 SYMMETRICAL_3DES（即函数 typeID == SYMMETRICAL_3DES）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_DES_CBC_NOPADDING = 0,
    ALG_DES_CBC_ISO9797_M1,
    ALG_DES_CBC_ISO9797_M2,
}E_DES_MAC_ALG_MODE;

/**
 * 枚举功能：AES 加解密算法类型
 * 枚举说明：当加解密函数的对称加密算法类型为 SYMMETRICAL_AES（即函数 typeID == SYMMETRICAL_AES）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_AES_CBC = 0,
    ALG_AES_ECB
}E_AES_CRYPT_ALG_MODE;

/**
 * 枚举功能：AES MAC计算或验证的算法类型
 * 枚举说明：当MAC 计算或验证函数的对称加密算法类型为 SYMMETRICAL_AES（即函数 typeID == SYMMETRICAL_AES）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_AES_CBC_NOPADDING = 0,
    ALG_AES_CBC_ISO9797_M1,
    ALG_AES_CBC_ISO9797_M2,
}E_AES_MAC_ALG_MODE;

/**
 * 枚举功能：SM4 加解密算法类型
 * 枚举说明：当加解密函数的对称加密算法类型为 SYMMETRICAL_SM4（即函数 typeID == SYMMETRICAL_SM4）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_SM4_CBC = 0,
    ALG_SM4_ECB
}E_SM4_CRYPT_ALG_MODE;

/**
 * 枚举功能：SM4 MAC计算或验证的算法类型
 * 枚举说明：当MAC 计算或验证函数的对称加密算法类型为 SYMMETRICAL_SM4（即函数 typeID == SYMMETRICAL_SM4）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_SM4_CBC_NOPADDING = 0,
    ALG_SM4_CBC_ISO9797_M1,
    ALG_SM4_CBC_ISO9797_M2,
}E_SM4_MAC_ALG_MODE;

/**
 * 枚举功能：SM1 加解密算法类型
 * 枚举说明：当加解密函数的对称加密算法类型为 SYMMETRICAL_SM1（即函数 typeID == SYMMETRICAL_SM1）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_SM1_CBC = 0,
    ALG_SM1_ECB
}E_SM1_CRYPT_ALG_MODE;

/**
 * 枚举功能：SM1 MAC计算或验证的算法类型
 * 枚举说明：当MAC 计算或验证函数的对称加密算法类型为 SYMMETRICAL_SM1（即函数 typeID == SYMMETRICAL_SM1）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_SM1_CBC_NOPADDING = 0,
    ALG_SM1_CBC_ISO9797_M1,
    ALG_SM1_CBC_ISO9797_M2,
}E_SM1_MAC_ALG_MODE;


/*********************************************************************************************************************
//============================================= 非对称加密算法的算法类型枚举 ========================================
*********************************************************************************************************************/
/**
 * 枚举功能：ECC 加解密算法类型
 * 枚举说明：当加解密函数的非对称加密算法类型为 ASYMMETRICAL_ECC（即函数 typeID == ASYMMETRICAL_ECC ）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_ECC_NOPADDING = 0,
}E_ECC_CRYPT_ALG_MODE;

/**
 * 枚举功能：EEC 签名或验签的算法类型
 * 枚举说明：当签名或验签函数的非对称加密算法类型为 ASYMMETRICAL_ECC（即函数 typeID == ASYMMETRICAL_ECC ）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_ECC256_SHA256 = 0,
}E_ECC_SIGN_ALG_MODE;

/**
 * 枚举功能：RSA 加解密算法类型
 * 枚举说明：当加解密函数的非对称加密算法类型为 ASYMMETRICAL_RSA（即函数 typeID == ASYMMETRICAL_RSA）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_RSA_NOPADDING = 0,
    ALG_RSA_PKCS1,
}E_RSA_CRYPT_ALG_MODE;

/**
 * 枚举功能：RSA 签名或验签的算法类型
 * 枚举说明：当签名或验签函数的非对称加密算法类型为 ASYMMETRICAL_RSA（即函数 typeID == ASYMMETRICAL_RSA）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_RSA_SHA1 = 0,//ALG_RSA_PKCS1
    ALG_RSA_SHA256,
    ALG_RSA_SHA384,
    ALG_RSA_SHA512,
}E_RSA_SIGN_ALG_MODE;

/**
 * 枚举功能：SM2 加解密算法类型
 * 枚举说明：当加解密函数的非对称加密算法类型为 ASYMMETRICAL_SM2（即函数 typeID == ASYMMETRICAL_SM2）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_SM2_NOPADDING = 0,
}E_SM2_CRYPT_ALG_MODE;

/**
 * 枚举功能：SM2 签名或验签的算法类型
 * 枚举说明：当签名或验签函数的非对称加密算法类型为 ASYMMETRICAL_SM2（即函数 typeID == ASYMMETRICAL_SM2）时，参数 alg_mode 使用该枚举类型
 */
typedef enum
{
    ALG_SM2_SM3 = 0,
}E_SM2_SIGN_ALG_MODE;

/*********************************************************************************************************************
//=================================================== 会话密钥算法类型枚举 ===========================================
*********************************************************************************************************************/
typedef enum
{
    //Asymmetric Alg-Session key
    SESSION_ALG_RSA = 0x00,

    //Symmetric Alg-Session key
    SESSION_ALG_SM4 = 0x02,

    SESSION_ALG_DES = 0x04,
    SESSION_ALG_3DES128 = 0x05,
    SESSION_ALG_3DES192,
    SESSION_ALG_SM1,
    SESSION_ALG_AES128,
    SESSION_ALG_AES192,
    SESSION_ALG_AES256,

    //Asymmetric Alg-Session key
    SESSION_ALG_SM2 = 0x20,
    SESSION_ALG_ECC = 0x40,

}E_SESSION_KEY_ALG_MODE;

//对称密钥数据类型
typedef enum
{
    SESSION_SYM_CLEARTEXT_DATA = 0x00,  //明文
    SESSION_SYM_CIPHERTEXT_DATA,        //密文
}E_SESSION_KEY_DATA_TYPE;

/*********************************************************************************************************************
//=================================================== 函数接口 ======================================================
*********************************************************************************************************************/
/**
 * 函数功能：se芯片初始化
 * 参数说明：
 *      输入参数：
 *      无
 * 返回值：0-成功，非0失败（具体错误码参见枚举E_SE_ERROR ）
 */
unsigned int se_conn(void);

/**
 * 函数功能：se芯片反初始化
 * 参数说明：
 *      输入参数：
 *      无
 * 返回值：0-成功，非0失败（具体错误码参见枚举E_SE_ERROR ）
 */
unsigned int se_disconn(void);

/**
 * 函数功能：获取se设备句柄，实际就是spi设备句柄
 * 参数说明：
 *      输入参数：
 *      无
 * 返回值：se设备句柄
 */
int se_get_hndl(void);



/**
 * 函数功能：对明文进行对称算法加密
 * 参数说明：
 *      输入参数：
 *      typeID          对称加密算法类型（详见枚举 E_SYMMETRICAL_TYPE ）
 *      alg_mode        算法类型（详见对应对称加密算法的算法类型枚举）
 *      input           明文数据
 *      input_len       明文数据长度
 *
 *      输出参数：
 *      output          密文数据
 *      output_len      密文数据长度
 * 返回值：0-成功，非0失败（具体错误码参见枚举E_SE_ERROR 和 errcode.h定义）
 * 说明  ：该函数采用 PKCS#7 标准对明文数据进行填充补位。
 */
unsigned long se_symmetrical_encrypt(E_SYMMETRICAL_TYPE typeID, unsigned char alg_mode,
                        unsigned char *input, unsigned int input_len,
                        unsigned char *output, unsigned int *output_len);

/**
 * 函数功能：对密文进行对称算法解密
 * 参数说明：
 *      输入参数：
 *      typeID          对称加密算法类型（详见枚举 E_SYMMETRICAL_TYPE ）
 *      alg_mode        算法类型（详见对应对称加密算法的算法类型枚举）
 *      input           密文数据
 *      input_len       密文数据长度
 *
 *      输出参数：
 *      output          明文数据
 *      output_len      明文数据长度
 * 返回值：0-成功，非0失败（具体错误码参见枚举E_SE_ERROR 和 errcode.h定义）
 * 说明  ：该函数密文需为经过 PKCS#7 填充补位后的加密数据。明文数据为经过 PKCS#7 去除补位后的解密数据。
 */
unsigned long se_symmetrical_decrypt(E_SYMMETRICAL_TYPE typeID, unsigned char alg_mode,
                        unsigned char *input, unsigned int input_len,
                        unsigned char *output, unsigned int *output_len);


/**
 * 函数功能：对明文进行非对称算法加密
 * 参数说明：
 *      输入参数：
 *      typeID          非对称加密算法类型（详见枚举 E_ASYMMETRICAL_TYPE ）
 *      alg_mode        算法类型（详见对应非对称加密算法的算法类型枚举）
 *      msg             数据明文，数据长度不超过 256 字节
 *      msg_len         数据明文长度
 *
 *      输出参数：
 *      cipher          密文数据
 *      cipher_len      密文数据长度
 * 返回值：0-成功，非0失败（具体错误码参见枚举E_SE_ERROR 和 errcode.h定义）
 * 说明  ：ECC 密文数据组成为 R+X+T;
           RSA 算法类型为 0 时，数据明文长度应为模长;类型为 1 时，数据明文长度不大于（模长-11）字节;
           SM2 密文数据组成为 C1+C3+C2.
 */
unsigned long se_asymmetrical_encrypt(E_ASYMMETRICAL_TYPE typeID, unsigned char alg_mode, 
                        unsigned char *msg,unsigned int msg_len, 
                        unsigned char *cipher, unsigned int *cipher_len);

/**
 * 函数功能：对密文进行非对称算法解密
 * 参数说明：
 *      输入参数：
 *      typeID          非对称加密算法类型（详见枚举 E_ASYMMETRICAL_TYPE ）
 *      alg_mode        算法类型（详见对应非对称加密算法的算法类型枚举）
 *      cipher          密文数据
 *      cipher_len      密文数据长度
 *
 *      输出参数：
 *      msg             数据明文，数据长度不超过 256 字节
 *      msg_len         数据明文长度
 * 返回值：0-成功，非0失败（具体错误码参见枚举E_SE_ERROR 和 errcode.h定义）
 */
unsigned long se_asymmetrical_decrypt(E_ASYMMETRICAL_TYPE typeID, unsigned char alg_mode, 
                        unsigned char *cipher, unsigned int cipher_len,
                        unsigned char *msg, unsigned int *msg_len);

/**
 * 函数功能：接口用于完成SE-SDK版本信息
 * 参数说明：
 *      输入参数：
 *      无

 *      输出参数：
 *      string          版本信息字符串
 * 返回值：0-成功，非0失败（具体错误码参见枚举E_SE_ERROR 和 errcode.h 定义）
 * 说明  : string 传入的空间大小最小应不小于32个字节
 */
unsigned long se_sdk_version(char *string);

/**
 * 函数功能：更新SM4加密的密钥
 * 参数说明：
 *      输入参数：
 *      无
 * 返回值：0-成功，非0失败（具体错误码参见枚举E_SE_ERROR 和 errcode.h 定义）
 */
void se_key_update(void);

#ifdef __cplusplus
}
#endif

#endif//__SE_SDK_H__

