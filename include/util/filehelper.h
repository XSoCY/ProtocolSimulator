#ifndef FILEHELPER_H
#define FILEHELPER_H

#include "util_global.h"

#include <QDir>
#include <QStringList>

class UTILSHARED_SELF_EXPORT FileHelper
{
public:
    static void GetDirFileByFilters(const QDir &fromDir,
                                    const QStringList &filters,
                                    QList<QString> &filePathList);
};

#endif  // FILEHELPER_H
