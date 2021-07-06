#include "framerecordtablewidget.h"
#include "paramlisttablewidget.h"
#include "uifactory.h"
#include <QVBoxLayout>
FrameRecordTableWidget::FrameRecordTableWidget(const QDomElement &doc_element, QWidget *parent)
    : QWidget(parent)
{
    frameTotal_      = 0;
    frameCurrent_    = 0;
    QDomNode docNode = doc_element.firstChild();
    while (!docNode.isNull()) {
        QDomElement sub_doc_element = docNode.toElement();
        if (!sub_doc_element.isNull()) {
            QString tag_name = sub_doc_element.tagName();
            if (tag_name == "Table") {
                paramListTableWidget_ = qobject_cast<ParamListTableWidget *>(
                    UiFactory::instance().createProduct("ParamListTableWidget", sub_doc_element));
                Q_ASSERT(paramListTableWidget_ != nullptr);
            }
        }
        docNode = docNode.nextSibling();
    }
    QVBoxLayout *vboxLayout = new QVBoxLayout(this);
    vboxLayout->addWidget(paramListTableWidget_);
}

QVariant FrameRecordTableWidget::frameTotal() const
{
    return QVariant(frameTotal_);
}

void FrameRecordTableWidget::setFrameTotal(const QVariant &param_vaule)
{
    if (param_vaule.canConvert<quint16>()) {
        quint16 frameTotalTemp = param_vaule.value<quint16>();
        //当前总帧数与以前的总帧数不同
        if (frameTotalTemp != frameTotal_ && frameTotalTemp > 0) {
            //清空文件列表，以及帧的接收记录map
            loop_param_value_list_.clear();
            frameRecord_.clear();
            frameTotal_ = frameTotalTemp;
        }
    }
}

QVariant FrameRecordTableWidget::frameCurrent() const
{
    return QVariant(frameCurrent_);
}

void FrameRecordTableWidget::setFrameCurrent(const QVariant &param_vaule)
{
    if (param_vaule.canConvert<quint16>()) {
        frameCurrent_ = param_vaule.value<quint16>();
        //当前帧数大于总帧数，丢弃
        if (frameCurrent_ <= frameTotal_ && frameCurrent_ > 0 && frameTotal_ > 0)
            return;

        frameCurrent_ = param_vaule.value<quint16>();
    }
}

QVariant FrameRecordTableWidget::paramVaule() const
{
    return QVariant(loop_param_value_list_);
}

void FrameRecordTableWidget::setParamVaule(const QVariant &param_vaule)
{
    //总帧数大于当前帧数
    if (frameTotal_ < frameCurrent_ && frameCurrent_ <= 0 && frameTotal_ <= 0)
        return;
    if (param_vaule.canConvert<QList<QVariant>>()) {
        QList<QVariant> loop_param_value_list_temp = param_vaule.value<QList<QVariant>>();
        if (frameRecord_.find(frameCurrent_) != frameRecord_.end()) {
            //不是续传的，是一次新的接收
            loop_param_value_list_.clear();
            frameRecord_.clear();
        }
        //需要按顺序接受内容到表格中,变了接受帧记录的map,获取前面帧接受到的文件总数
        int insertIndex = 0;
        for (int i = 1; i < frameCurrent_; ++i) {
            if (frameRecord_.find(i) != frameRecord_.end()) {
                insertIndex += frameRecord_.value(insertIndex);
            }
        }

        loop_param_value_list_.insert(insertIndex, loop_param_value_list_temp);
        frameRecord_.insert(frameCurrent_, loop_param_value_list_temp.size());
        paramListTableWidget_->setParamVaule(loop_param_value_list_);
    }
}

bool FrameRecordTableWidget::editMode() const
{
    return false;
}

void FrameRecordTableWidget::setEditMode(bool edit_mode)
{
    Q_UNUSED(edit_mode);
}
