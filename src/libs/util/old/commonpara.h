#ifndef COMMONPARA_H
#define COMMONPARA_H

#include "util_global.h"

#include <QString>

struct _strUserData  //用户账号
{
    QString strUserName;  //用户名
    int IAuthority;       //权限
    QString strPassword;  //密码
    _strUserData()
    {
        strUserName = "";
        IAuthority = 0;
        strPassword = "";
    }
};

struct _strParaMacorData  //参数宏
{
    QString strParaMacorID;  //参数宏ID
    QString strSatelliteID;  //卫星ID
    QString strWorkMode;     //工作类型
    QString strDataTime;     //修改时间
    QString strMacorDesc;    //参数宏描述

    _strParaMacorData()
    {
        strParaMacorID = "";
        strSatelliteID = "";
        strMacorDesc = "";
    }
};

class UTILSHARED_EXPORT CommonPara
{
private:
    CommonPara();
    ~CommonPara();

public:
    static CommonPara* instance();

    QString CurrAuthorityShowValue(int IAut);  //得到当前权限的显示值

    void setCurrUserData(_strUserData strUserData);  //设置当前登录的用户数据

    _strUserData* CurrLoginUserData();  //获取当前登录的用户信息

    QString CurrMacroWorkModeValue(int IAut);  //当前参数宏工作模式的显示值

private:
    _strUserData m_CurrLoginUserData;  //当前登录的用户信息
};

#endif  // COMMONPARA_H
