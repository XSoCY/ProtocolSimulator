#ifndef RELATIONXMLMANAGER_H
#define RELATIONXMLMANAGER_H

#include <QDomElement>
#include <QMap>
#include <QString>
#include "util_global.h"

class UTILSHARED_SELF_EXPORT RelationXmlManager
{
public:
    static RelationXmlManager& instance();

    QDomElement settingParamRelation(const unsigned short device_id, const unsigned char unit_id) const;
    QDomElement settingProcessRelation(const unsigned short device_id, const unsigned char process_id) const;

protected:
    RelationXmlManager();

private:
    void loadPath(const QString& config_path);
    void loadfile(const QString& config_file_path);

private:
    QMap<QPair<unsigned short, unsigned char>, QDomElement> device_id_unit_id_to_setting_param_relation_;
    QMap<QPair<unsigned short, unsigned char>, QDomElement> device_id_process_id_to_setting_process_relation_;
};

#endif // RELATIONXMLMANAGER_H
