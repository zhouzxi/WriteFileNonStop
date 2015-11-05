/**********************************************************************
* 版权所有 (C)2015, Zhou Zhaoxiong。
*
* 文件名称：WriteFileNonStop.c
* 文件标识：无
* 内容摘要：不停地写文件
* 其它说明：无
* 当前版本：V1.0
* 作    者：Zhou Zhaoxiong
* 完成日期：20150917
*
**********************************************************************/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include <sys/time.h>

// 数据类型重定义
typedef signed   int        INT32;
typedef signed   char       INT8;
typedef unsigned char       UINT8;
typedef unsigned short int  UINT16;
typedef unsigned int        UINT32;


// 函数声明
void Sleep(UINT32 iCountMs);
void WriteFileNonStop(void);


/**********************************************************************
* 功能描述：主函数
* 输入参数：无
* 输出参数：无
* 返 回 值：无
* 其它说明：无
* 修改日期        版本号     修改人            修改内容
* -------------------------------------------------------------------
* 20150917       V1.0   Zhou Zhaoxiong        创建
*********************************************************************/
INT32 main()
{
    WriteFileNonStop();   // 写文件

    return 0;             // main函数返回0
}


/**********************************************************************
 * 功能描述： 把内容写到本地文件中
 * 输入参数： pszContentLine-一条文件记录
 * 输出参数： 无
 * 返 回 值： 无
 * 其它说明： 无
 * 修改日期            版本号            修改人           修改内容
 * ----------------------------------------------------------------------
 * 20150917           V1.0          Zhou Zhaoxiong        创建
 ************************************************************************/
void WriteFileNonStop(void)
{
    FILE  *fp                  = NULL;
    INT8   szLocalFile[500]    = {0};
    INT8   szCurDate[20]       = {0};
    INT8   szContentBuf[200]   = {0};

    snprintf(szLocalFile, sizeof(szLocalFile)-1, "%s/zhouzhaoxiong/zzx/WriteFileNonStop/File/File.txt", getenv("HOME"));
    fp = fopen(szLocalFile, "a+");
    if (fp == NULL)
    {
         printf("WriteFileNonStop: open local file failed, file=%s\n", szLocalFile);
         return;
    }

    while (1)      // 不停地写文件
    {
        strcpy(szContentBuf, "hello, world!\n");
        printf("WriteFileNonStop: LocalFile=%s, ContentBuf=%s", szLocalFile, szContentBuf);

        fputs(szContentBuf, fp);
        fflush(fp);

        Sleep(10 * 1000);   // 每10s写一次
    }

    fclose(fp);
    fp = NULL;

    return;
}


/**********************************************************************
* 功能描述： 程序休眠
* 输入参数： iCountMs-休眠时间(单位:ms)
* 输出参数： 无
* 返 回 值： 无
* 其它说明： 无
* 修改日期          版本号       修改人              修改内容
* ------------------------------------------------------------------
* 20150917         V1.0     Zhou Zhaoxiong           创建
********************************************************************/
void Sleep(UINT32 iCountMs)
{
    struct timeval t_timeout = {0};

    if (iCountMs < 1000)
    {
        t_timeout.tv_sec = 0;
        t_timeout.tv_usec = iCountMs * 1000;
    }
    else
    {
        t_timeout.tv_sec = iCountMs / 1000;
        t_timeout.tv_usec = (iCountMs % 1000) * 1000;
    }
    select(0, NULL, NULL, NULL, &t_timeout);   // 调用select函数阻塞程序
}
