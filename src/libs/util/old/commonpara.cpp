#include "commonpara.h"

CommonPara* pCommonPara = NULL;

CommonPara::CommonPara() {}

CommonPara::~CommonPara() {}

CommonPara* CommonPara::instance()
{
    if (NULL == pCommonPara)
    {
        pCommonPara = new CommonPara();
    }
    return pCommonPara;
}

QString CommonPara::CurrAuthorityShowValue(int IAut)  //得到当前权限的显示值
{
    QString strAuth = "观察员";
    switch (IAut)
    {
    case 0:  //管理员
    {
        strAuth = "管理员";
    }
    break;
    case 1:  //操作员
    {
        strAuth = "操作员";
    }
    break;
    case 2:  //观察员
    {
        strAuth = "观察员";
    }
    break;
    default:
        break;
    }
    return strAuth;
}

void CommonPara::setCurrUserData(_strUserData strUserData)  //设置当前登录的用户数据
{
    m_CurrLoginUserData = strUserData;
}

_strUserData* CommonPara::CurrLoginUserData()  //获取当前登录的用户信息
{
    return &m_CurrLoginUserData;
}

QString CommonPara::CurrMacroWorkModeValue(int IAut)  //当前参数宏工作模式的显示值
{
    QString strAuth = "S遥测(STM)";
    switch (IAut)
    {
    case 0:
    {
        strAuth = "S遥测(STM)";
    }
    break;
    case 1:
    {
        strAuth = "S遥控(STC)";
    }
    break;
    case 2:
    {
        strAuth = "X遥测(XTM)";
    }
    break;
    case 3:
    {
        strAuth = "X遥控(XTC)";
    }
    break;
    default:
        break;
    }
    return strAuth;
}
