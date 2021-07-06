#include "UiControl.h"

#include <QSize>
#include <QPixmap>


// 图片大小
const QSize PitctrueSize = QSize(16, 16);

UiControl::UiControl(QObject *parent) : QObject(parent)
  , m_ImageDirPath("")
{
    // 图片文件夹路径
    m_ImageDirPath = QApplication::applicationDirPath();
    m_ImageDirPath += "/images/";

    QPixmap pixmap;
    pixmap = QPixmap(m_ImageDirPath + "yellow.png").scaled(PitctrueSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_mapPixmap.insert(ColorType_Yellow, pixmap);

    pixmap = QPixmap(m_ImageDirPath + "green.png").scaled(PitctrueSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_mapPixmap.insert(ColorType_Green, pixmap);

    pixmap = QPixmap(m_ImageDirPath + "red.png").scaled(PitctrueSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_mapPixmap.insert(ColorType_Red, pixmap);

    pixmap = QPixmap(m_ImageDirPath + "gray.png").scaled(PitctrueSize, Qt::KeepAspectRatio, Qt::SmoothTransformation);
    m_mapPixmap.insert(ColorType_Gray, pixmap);

    m_mapDraw.insert(ColorType_Yellow, COLOR_YELLOW);
    m_mapDraw.insert(ColorType_Green, COLOR_GREEN);
    m_mapDraw.insert(ColorType_Red, COLOR_RED);
    m_mapDraw.insert(ColorType_Gray, COLOR_GRAY);
}

/**
 * @brief setImageColor 设置标签图片颜色
 * @param label 标签对象
 * @param color 颜色枚举ColorType
 * @return 无
 */
void UiControl::setImageColor(QLabel* label, ColorType color)
{
    if( Q_NULLPTR == label)
    {
        return ;
    }

    label->setPixmap(m_mapPixmap[ColorType_Gray]);
    if( m_mapPixmap.contains(color))
    {
        label->setPixmap(m_mapPixmap[color]);
    }
    else
    {
        label->setPixmap(m_mapPixmap[ColorType_Gray]);
    }
}

void UiControl::setDrawColor(LabelDraw *label, ColorType color, int x, int y, uint uiSize)
{
    if( Q_NULLPTR == label)
    {
        return ;
    }

    if( m_mapDraw.contains(color))
    {
        label->SetColorAndSize(m_mapDraw[color], x, y, uiSize);
    }
    else
    {
        label->SetColorAndSize(m_mapDraw[ColorType_Gray], x, y, uiSize);
    }
}
