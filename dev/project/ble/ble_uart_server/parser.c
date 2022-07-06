/*
 * @Description:
 * @Author: hecai
 * @Date: 2021-11-02 10:00:47
 * @LastEditTime: 2022-07-07 02:19:09
 * @FilePath: \battery\dev\project\ble\ble_uart_server\parser.c
 */
#include "parser.h"
#include "Tools.h"
#include "lscrypt.h"
#include "log.h"
#include "md5.h"
#include <string.h>

u8 buff[64];
u8 tmpBuff[64];
SYS_STATE curState = SYS_IDEL;
u8 lastTime[11] = {0};
u8 pw[20] = {0};


MD5_CTX md5c;

//密钥
const char *aes_key = "Ffkk6AWivOsLE4NI";
u32 cbc_ecb_key_128[] = {
    0x45344E49,
    0x764F734C,
    0x36415769,
    0x46666B6B};
/**
 * @description:
 * @param {*}
 * @return {*}
 */
void crypt_init(void)
{
    HAL_LSCRYPT_Init();
    HAL_LSCRYPT_AES_Key_Config(cbc_ecb_key_128, AES_KEY_128);
}

void crypt_deinit(void)
{
    HAL_LSCRYPT_DeInit();
}
/**
 * @description: 解码数据
 * @param {u8 *} dat
 * @param {u8} len 长度为16的整数倍，最大不超过64
 * @return {*}
 */
void decodeInfo(const u8 *dat, u8 len)
{
    u8 l, i, j;
    crypt_init();
    l = len / 16;
    memset(buff, '\0', 64);
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < 16; j++)
        {
            buff[i * 16 + j] = dat[i * 16 + 15 - j];
        }
    }
    HAL_LSCRYPT_AES_ECB_Decrypt(buff, len, tmpBuff);
    for (i = 0; i < l; i++)
    {
        for (j = 0; j < 16; j++)
        {
            buff[i * 16 + j] = tmpBuff[i * 16 + 15 - j];
        }
    }
    crypt_deinit();
}

void SetSysState(SYS_STATE state)
{
    curState = state;
}
// /**
//  * @description: 编码数据,空位补0
//  * @param {u8 *} dat
//  * @param {u8} len 最大不超过64
//  * @return {*}
//  */
// void encodeInfo(u8 * dat,u8 len,u8 * info)
// {
//     u8 l,i,j;

//     l=len/16;
//     if(len%16>0)
//         l++;
//     for(i=0;i<l;i++)
//     {
//         if(i==l-1 && len%16>0)
//         {
//             for(j=0;j<16-len%16;j++)
//             {
//                 buff[]
//             }
//         }else{
//             for(j=0;j<16;j++)
//             {
//                 buff[i*16+j]=dat[i*16+15-j];
//             }
//         }
//     }
//     HAL_LSCRYPT_AES_ECB_Encrypt(buff, len, rebuff);
//     for(i=0;i<l;i++)
//     {
//         for(j=0;j<16;j++)
//         {
//             info[i*16+j]=rebuff[i*16+15-j];
//         }
//     }
// }

bool checkMd5()
{
    u8 read_len;
    char md5str[8];
    char src[80];
    unsigned char decrypt[16] = {0};

    memcpy(src, aes_key, 16);
    memcpy(src + 16, buff+8, strlen((char *)buff));

    MD5Init(&md5c); //初始化
    read_len = strlen(src);
    MD5Update(&md5c, (unsigned char *)src, read_len);

    MD5Final(&md5c, decrypt);

    sprintf(md5str, "%02X%02X%02X%02X", decrypt[0],decrypt[1],decrypt[2],decrypt[3]);
    LOG_I("Md5 check:%s\0",md5str);
    if(memcmp(buff,md5str,8)==0)
    {
        LOG_I("check success");
	    return true;
    }
    else
    {
        LOG_I("check error");
        return false;
    }
}

/**
 * @description: 解析指令
 * 指令格式：时间戳（10位），加密码md5签名（16位小写），A：动作，P:参数
 * A:OPEN  开门
 * A:PW    修改密码  P:新密码的md5签名（16位小写）
 * 16376319554621d373cade4e83A:OPEN;
 * 16376319554621d373cade4e83A:PW;P:1859cb5ca6da0c48;
 * @param {u8 *} dat
 * @param {u8} len
 * @return {*}
 */
CMD_TYPE ParseCmd(const u8 *dat, u8 len, char *para)
{
    char *posBegin;
    char *posEnd;
    char curTime[10] = {0};
    char action[10] = {0};
    
    LOG_I("CMD Len:%d",len);
    if (len < 20 || len % 16 > 0 || len > 64)
    {
        LOG_I("CMD_ERROR");
        return CMD_ERROR;
    }
    if (curState != SYS_IDEL)
    {
        LOG_I("CMD_BUSY");
        return CMD_BUSY;
    }

    LOG_I("decodeInfo");
    decodeInfo(dat, len);
    LOG_I("cmd:%s\0", buff);
    memcpy(curTime, buff+8, 10);
    //对比时间
    LOG_I("curTime:%s", curTime);
    LOG_I("lastTime:%s", lastTime);

    //校验md5签名
    if(!checkMd5())
    {
        LOG_I("CMD_ERRORSIGN");
        return CMD_ERRORSIGN;        
    }
    LOG_I("CMD_SIGN_OK");
    //检查时间戳
    if (strcmp((const char *)curTime, (const char *)lastTime) <= 0)
    {
        LOG_I("CMD_OVERTIME");
        return CMD_OVERTIME;
    }else
        memcpy(lastTime, curTime, 10);
    LOG_I("CMD_TIME_OK");
    //比对密码,密码为设备地址
    if (memcmp(buff+18,pw,12) != 0)
    {
        LOG_I("CMD_PWERROR");
        return CMD_PWERROR;
    }
    LOG_I("CMD_PW_OK");
    //获取action
    posBegin = strstr((const char *)buff, "A:");
    if (posBegin != NULL)
    {
        posEnd = strstr(posBegin, ";");
        if (posEnd != NULL)
        {
            memcpy(action, posBegin + 2, posEnd - posBegin - 2);
        }
        else
        {
            LOG_I("CMD_ERROR A");
            return CMD_ERROR;
        }
    }
    else
    {
        LOG_I("CMD_ERROR A");
        return CMD_ERROR;
    }
    LOG_I("CMD_OK");
    //获取para,参数可以为空
    posBegin = strstr((const char *)buff, "P:");
    if (posBegin != NULL)
    {
        posEnd = strstr((const char *)posBegin, ";");
        if (posEnd != NULL)
        {
            memcpy(para, posBegin + 2, posEnd - posBegin - 2);
        }
        else
        {
            para = NULL;
        }
    }
    else
    {
        para = NULL;
    }

    

    //open指令
    if (strcmp((const char *)action, "OPEN") == 0)
    {
        LOG_I("CMD_OPEN");
        return CMD_OPEN;
    }
    //sale指令
    else if (strcmp((const char *)action, "SALE") == 0)
    {
        LOG_I("CMD_SALE");
        return CMD_SALE;
    }
    //close指令
    else if (strcmp((const char *)action, "CLOSE") == 0)
    {
        LOG_I("CMD_CLOSE");
        return CMD_CLOSE;
    }
    else
    {
        LOG_I("CMD_UNDEFINE");
        return CMD_UNDEFINE;
    }
}
