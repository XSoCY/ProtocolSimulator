#ifndef FRAMERECORDTABLEWIDGET_H
#define FRAMERECORDTABLEWIDGET_H
#include <QDomElement>
#include <QMap>
#include <QVariant>
#include <QWidget>
/**
 * @brief The FrameRecordTableWidget class
 */
class ParamListTableWidget;
class FrameRecordTableWidget : public QWidget
{
    Q_OBJECT
    Q_PROPERTY(QVariant frameTotal READ frameTotal WRITE setFrameTotal)
    Q_PROPERTY(QVariant frameCurrent READ frameCurrent WRITE setFrameCurrent)
    Q_PROPERTY(QVariant paramVaule READ paramVaule WRITE setParamVaule)
    Q_PROPERTY(bool editMode READ editMode WRITE setEditMode)

public:
    explicit FrameRecordTableWidget(const QDomElement &doc_element, QWidget *parent = nullptr);

    QVariant frameTotal() const;
    void setFrameTotal(const QVariant &param_vaule);

    QVariant frameCurrent() const;
    void setFrameCurrent(const QVariant &param_vaule);

    QVariant paramVaule() const;
    void setParamVaule(const QVariant &param_vaule);

    bool editMode() const;
    void setEditMode(bool edit_mode);

private:
    quint16 frameTotal_;
    quint16 frameCurrent_;
    QList<QVariant> loop_param_value_list_;
    ParamListTableWidget *paramListTableWidget_;
    QMap<int, int> frameRecord_;
};

#endif  // FRAMERECORDTABLEWIDGET_H
