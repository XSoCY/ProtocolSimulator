#ifndef UIXMLMANAGER_H
#define UIXMLMANAGER_H

#include <QDomElement>
#include <QMap>
#include <QString>
#include "util_global.h"

class UTILSHARED_SELF_EXPORT UIXmlManager
{
public:
    static UIXmlManager& instance();

    /**
     * @brief settingParamWidget    通过设备ID单元ID获取参数设置窗口xml元素
     * @param device_id 设备ID
     * @param unit_id   单元ID
     * @return  参数设置窗口xml元素
     */
    QDomElement settingParamWidget(const unsigned short device_id, const unsigned char unit_id) const;
    /**
     * @brief statusParamWidget     通过设备ID单元ID获取设备状态窗口xml元素
     * @param device_id 设备ID
     * @param unit_id   单元ID
     * @return  设备状态窗口xml元素
     */
    QDomElement statusParamWidget(const unsigned short device_id, const unsigned char unit_id) const;
    /**
     * @brief settingProcessWidget  通过设备ID过程ID获取设置过程窗口xml元素
     * @param device_id     设备ID
     * @param process_id    过程ID
     * @return  设置过程窗口xml元素
     */
    QDomElement settingProcessWidget(const unsigned short device_id, const unsigned char process_id) const;
    /**
     * @brief statusProcessWidget   通过设备ID过程ID获取过程状态窗口xml元素
     * @param device_id     设备ID
     * @param process_id    过程ID
     * @return  过程状态窗口xml元素
     */
    QDomElement statusProcessWidget(const unsigned short device_id, const unsigned char process_id) const;

    /**
     * @brief statusProcessWidget   通过设备ID获取协议首部xml元素
     * @param device_id     设备ID
     * @return  协议首部xml元素
     */
    QDomElement deviceHead(const unsigned short device_id) const;
    /**
     * @brief statusProcessWidget   通过设备ID获取协议子部xml元素
     * @param device_id     设备ID
     * @return  协议子部xml元素
     */
    QDomElement deviceSubHead(const unsigned short device_id) const;

protected:
    UIXmlManager();

private:
    /**
     * @brief loadPath  加载Ui配置文件夹路径 DS/System/UI
     * @param config_path   配置文件夹路径
     */
    void loadPath(const QString& config_path);

    /**
     * @brief loadfile  加载Ui配置文件
     * @param config_file_path  配置文件路径 DS/System/UI/设备ID/XXX.xml
     */
    void loadfile(const QString& config_file_path);

private:

    /**
     * @brief device_id_to_Head 设备协议头QMap <设备ID，xml数据>
     */
    QMap<unsigned short, QDomElement> device_id_to_Head;
    /**
     * @brief device_id_to_SubHead 设备协议子头QMap <设备ID，xml数据>
     */
    QMap<unsigned short, QDomElement> device_id_to_SubHead;
    /**
     * @brief device_id_unit_id_to_setting_param_widget_ 设置命令部件xml数据QMap <设备ID_单元ID，xml数据>
     */
    QMap<QPair<unsigned short, unsigned char>, QDomElement> device_id_unit_id_to_setting_param_widget_;
    /**
     * @brief device_id_unit_id_to_status_param_widget_ 设备状态部件xml数据QMap <设备ID_单元ID，xml数据>
     */
    QMap<QPair<unsigned short, unsigned char>, QDomElement> device_id_unit_id_to_status_param_widget_;
    /**
     * @brief device_id_process_id_to_setting_process_widget_ 过程控制设置部件xml数据QMap <设备ID_过程ID，xml数据>
     */
    QMap<QPair<unsigned short, unsigned char>, QDomElement> device_id_process_id_to_setting_process_widget_;
    /**
     * @brief device_id_process_id_to_status_process_widget_ 过程控制结果部件xml数据QMap  <设备ID_过程ID，xml数据>
     */
    QMap<QPair<unsigned short, unsigned char>, QDomElement> device_id_process_id_to_status_process_widget_;
};

#endif  // UIXMLMANAGER_H
