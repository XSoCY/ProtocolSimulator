#ifndef UICONTROL_H
#define UICONTROL_H

#include <QObject>
#include <QWidget>
#include <QApplication>
#include <QLabel>
#include "util_global.h"
#include "labeldraw.h"

/**
 * @brief ColorType 颜色类型枚举
 */
enum ColorType
{
    ColorType_Invalid,      // 无效颜色 默认灰色
    ColorType_Red,          // 红色
    ColorType_Green,        // 绿色
    ColorType_Blue,         // 蓝色
    ColorType_Gray,         // 灰色
    ColorType_Yellow,       // 黄色
};


const QColor COLOR_GRAY      = QColor( 149, 149, 149 );  //灰色
const QColor COLOR_RED       = QColor( 244, 9 , 42 );    //红色
const QColor COLOR_GREEN     = QColor( 20, 222 , 96 );   //绿色
const QColor COLOR_YELLOW    = QColor( 255, 240 , 2 );   //黄色

class UTILSHARED_SELF_EXPORT UiControl : public QObject
{
    Q_OBJECT
public:
    explicit UiControl(QObject *parent = nullptr);

    /**
     * @brief getInstance 获取UiControl单例对象
     * @return UiControl 实例对象
     */
    static UiControl& getInstance()
    {
        static UiControl instance;

        return instance;
    }

    /**
     * @brief setImageColor 设置标签图片颜色
     * @param label 标签对象
     * @param color 颜色枚举ColorType
     * @return 无
     */
    void setImageColor(QLabel* label,ColorType color);

    /**
     * @brief setDrawColor 设置标签图片颜色
     * @param label 标签对象
     * @param color 颜色枚举ColorType
     * @param x x位置
     * @param y y位置
     * @param uiSize 圆形大小
     */
    void setDrawColor(LabelDraw* label,ColorType color, int x, int y, uint uiSize);

signals:

public slots:

private:

    QString m_ImageDirPath; // 图片素材文件夹路径：运行路径/images/
    QMap<ColorType, QPixmap> m_mapPixmap;
    QMap<ColorType, QColor> m_mapDraw;
};

#endif // UICONTROL_H
