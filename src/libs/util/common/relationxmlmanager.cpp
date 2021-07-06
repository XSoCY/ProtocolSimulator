#include "relationxmlmanager.h"
#include <QApplication>
#include <QDebug>
#include <QDir>
#include <QDomDocument>
#include <QMessageBox>

RelationXmlManager &RelationXmlManager::instance()
{
    static RelationXmlManager instace;
    return instace;
}

QDomElement RelationXmlManager::settingParamRelation(const unsigned short device_id, const unsigned char unit_id) const
{
    return device_id_unit_id_to_setting_param_relation_.value(qMakePair(device_id, unit_id));
}

QDomElement RelationXmlManager::settingProcessRelation(const unsigned short device_id, const unsigned char process_id) const
{
    return device_id_process_id_to_setting_process_relation_.value(qMakePair(device_id, process_id));
}

RelationXmlManager::RelationXmlManager()
{
    device_id_unit_id_to_setting_param_relation_.clear();
    device_id_process_id_to_setting_process_relation_.clear();

    loadPath(QApplication::applicationDirPath() + QDir::separator() + "System" + QDir::separator() + "Relation");
}

void RelationXmlManager::loadPath(const QString &config_path)
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

void RelationXmlManager::loadfile(const QString &config_file_path)
{
    QFile file(config_file_path);
    if (!file.open(QIODevice::ReadOnly)) {
        QMessageBox::critical(nullptr, "", QObject::tr("Open %1 error.").arg(config_file_path), QMessageBox::Ok);
        return;
    }

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
            if (strTagName == "ParamRelation") {
                auto          device_id_list = docElement.attribute("deviceID").split(",");
                unsigned char unit_id        = static_cast<unsigned char>(docElement.attribute("unitID").toInt());
                for (auto str_device_id : device_id_list) {
                    unsigned short device_id = str_device_id.toUShort(nullptr, 16);
                    if (device_id_unit_id_to_setting_param_relation_.contains(qMakePair(device_id, unit_id))) {
                        qDebug() << QString("%1分机%2单元参数设置关联关系xml配置重复").arg(device_id, 0, 16).arg(unit_id);
                    }
                    device_id_unit_id_to_setting_param_relation_.insert(qMakePair(device_id, unit_id), docElement);
                }
            }
            else if (strTagName == "ProcessRelation") {
                auto          device_id_list = docElement.attribute("deviceID").split(",");
                unsigned char unit_id        = static_cast<unsigned char>(docElement.attribute("processID").toInt());
                for (auto str_device_id : device_id_list) {
                    unsigned short device_id = str_device_id.toUShort(nullptr, 16);
                    if (device_id_process_id_to_setting_process_relation_.contains(qMakePair(device_id, unit_id))) {
                        qDebug() << QString("%1分机%2号过程控制关联关系xml配置重复").arg(device_id, 0, 16).arg(unit_id);
                    }
                    device_id_process_id_to_setting_process_relation_.insert(qMakePair(device_id, unit_id), docElement);
                }
            }
        }
        docNode = docNode.nextSibling();
    }
}
