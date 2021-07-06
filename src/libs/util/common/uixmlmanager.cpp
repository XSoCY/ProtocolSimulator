#include "uixmlmanager.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QDomDocument>
#include <QMessageBox>

UIXmlManager& UIXmlManager::instance()
{
    static UIXmlManager instace;
    return instace;
}

QDomElement UIXmlManager::settingParamWidget(const unsigned short device_id, const unsigned char unit_id) const
{
    return device_id_unit_id_to_setting_param_widget_.value(qMakePair(device_id, unit_id));
}

QDomElement UIXmlManager::statusParamWidget(const unsigned short device_id, const unsigned char unit_id) const
{
    return device_id_unit_id_to_status_param_widget_.value(qMakePair(device_id, unit_id));
}

QDomElement UIXmlManager::settingProcessWidget(const unsigned short device_id, const unsigned char process_id) const
{
    return device_id_process_id_to_setting_process_widget_.value(qMakePair(device_id, process_id));
}

QDomElement UIXmlManager::statusProcessWidget(const unsigned short device_id, const unsigned char process_id) const
{
    return device_id_process_id_to_status_process_widget_.value(qMakePair(device_id, process_id));
}

/**
 * @brief statusProcessWidget   通过设备ID获取协议首部xml元素
 * @param device_id     设备ID
 * @return  协议首部xml元素
 */
QDomElement UIXmlManager::deviceHead(const unsigned short device_id) const
{
    return device_id_to_Head.value(device_id);
}
/**
 * @brief statusProcessWidget   通过设备ID获取协议子部xml元素
 * @param device_id     设备ID
 * @return  协议子部xml元素
 */
QDomElement UIXmlManager::deviceSubHead(const unsigned short device_id) const
{
    return device_id_to_SubHead.value(device_id);
}

UIXmlManager::UIXmlManager()
{
    device_id_to_Head.clear();
    device_id_to_SubHead.clear();
    device_id_unit_id_to_setting_param_widget_.clear();
    device_id_unit_id_to_status_param_widget_.clear();
    device_id_process_id_to_setting_process_widget_.clear();
    device_id_process_id_to_status_process_widget_.clear();

    // 加载设备协议配置文件夹路径DS/System/UI
    loadPath(QApplication::applicationDirPath() + QDir::separator() + "System" + QDir::separator() + "UI");
}

/**
 * @brief loadPath  加载Ui配置文件夹路径 DS/System/UI
 * @param config_path   配置文件夹路径
 */
void UIXmlManager::loadPath(const QString& config_path)
{
    for (auto file : QDir(config_path).entryInfoList(QStringList() << "*.xml", QDir::Files)) {
        qDebug() << "files" << file.absoluteFilePath();
        loadfile(file.absoluteFilePath());
    }

    for (auto sub_dir : QDir(config_path).entryInfoList(QDir::AllDirs | QDir::NoDotAndDotDot)) {
        qDebug() << "dir" << sub_dir.absoluteFilePath();
        if (sub_dir.isDir()) {
            loadPath(sub_dir.absoluteFilePath());
        }
    }
}

/**
 * @brief loadfile  加载Ui配置文件
 * @param config_file_path  配置文件路径 DS/System/UI/设备ID/XXX.xml
 */
void UIXmlManager::loadfile(const QString& config_file_path)
{
    QFile file(config_file_path);
    // 打开xml文件
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "", QObject::tr("Open %1 error.").arg(config_file_path), QMessageBox::Ok);
        return;
    }
    qDebug() << QString("解析设备协议xml文件：%1").arg(config_file_path);
    // 解析xml数据
    QDomDocument dom_doc("mydocument");
    if (!dom_doc.setContent(&file)) {
        file.close();
        QMessageBox::critical(nullptr, "", QObject::tr("Analyzing %1 error.").arg(config_file_path), QMessageBox::Ok);
        return;
    }
    file.close();

    QDomNode docNode = dom_doc.documentElement().firstChild();
    while (!docNode.isNull()) {
        QDomElement docElement = docNode.toElement();
        if (!docElement.isNull()) {
            QString strTagName = docElement.tagName();
            // 参数设置
            if (strTagName == "SettingParamWidget") {
                auto device_id_list = docElement.attribute("deviceID").split(",");
                unsigned char unit_id = static_cast<unsigned char>(docElement.attribute("unitID").toInt());
                for (auto str_device_id : device_id_list) {
                    unsigned short device_id = str_device_id.toUShort(nullptr, 16);
                    if (device_id_unit_id_to_setting_param_widget_.contains(qMakePair(device_id, unit_id))) {
                        qDebug() << QString("%1分机%2单元参数设置xml配置重复").arg(device_id, 0, 16).arg(unit_id);
                    }
                    device_id_unit_id_to_setting_param_widget_.insert(qMakePair(device_id, unit_id), docElement);
                }
            }
            // 设备状态
            else if (strTagName == "StatusParamWidget") {
                auto device_id_list = docElement.attribute("deviceID").split(",");
                unsigned char unit_id = static_cast<unsigned char>(docElement.attribute("unitID").toInt());
                for (auto str_device_id : device_id_list) {
                    unsigned short device_id = str_device_id.toUShort(nullptr, 16);
                    if (device_id_unit_id_to_status_param_widget_.contains(qMakePair(device_id, unit_id))) {
                        qDebug() << QString("%1分机%2单元参数状态xml配置重复").arg(device_id, 0, 16).arg(unit_id);
                    }
                    device_id_unit_id_to_status_param_widget_.insert(qMakePair(device_id, unit_id), docElement);
                }
            }
            // 过程控制设置
            else if (strTagName == "SettingProcessWidget") {
                auto device_id_list = docElement.attribute("deviceID").split(",");
                unsigned char process_id = static_cast<unsigned char>(docElement.attribute("processID").toInt());
                for (auto str_device_id : device_id_list) {
                    unsigned short device_id = str_device_id.toUShort(nullptr, 16);
                    if (device_id_process_id_to_setting_process_widget_.contains(qMakePair(device_id, process_id))) {
                        qDebug() << QString("%1分机%2号过程控制设置xml配置重复").arg(device_id, 0, 16).arg(process_id);
                    }
                    device_id_process_id_to_setting_process_widget_.insert(qMakePair(device_id, process_id),
                                                                           docElement);
                }
            }
            // 过程控制结果
            else if (strTagName == "StatusProcessWidget") {
                auto device_id_list = docElement.attribute("deviceID").split(",");
                unsigned char process_id = static_cast<unsigned char>(docElement.attribute("processID").toInt());
                for (auto str_device_id : device_id_list) {
                    unsigned short device_id = str_device_id.toUShort(nullptr, 16);
                    if (device_id_process_id_to_status_process_widget_.contains(qMakePair(device_id, process_id))) {
                        qDebug() << QString("%1分机%2号过程控制结果xml配置重复").arg(device_id, 0, 16).arg(process_id);
                    }
                    device_id_process_id_to_status_process_widget_.insert(qMakePair(device_id, process_id), docElement);
                }
            }
            // 设备协议首部
            else if (strTagName == "Head") {
                auto device_id_list = docElement.attribute("deviceID").split(",");
                for (auto str_device_id : device_id_list) {
                    unsigned short device_id = str_device_id.toUShort(nullptr, 16);
                    if (device_id_to_Head.contains(device_id)) {
                        qDebug() << QString("%1分机协议首部xml配置重复").arg(device_id, 0, 16);
                    }
                    device_id_to_Head.insert(device_id, docElement);
                }
            }

            // 设备协议子部
            else if (strTagName == "SubHead") {
                auto device_id_list = docElement.attribute("deviceID").split(",");
                for (auto str_device_id : device_id_list) {
                    unsigned short device_id = str_device_id.toUShort(nullptr, 16);
                    if (device_id_to_SubHead.contains(device_id)) {
                        qDebug() << QString("%1分机协议子部xml配置重复").arg(device_id, 0, 16);
                    }
                    device_id_to_SubHead.insert(device_id, docElement);
                }
            }
        }
        docNode = docNode.nextSibling();
    }
}
