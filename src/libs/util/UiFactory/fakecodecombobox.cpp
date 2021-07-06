#include "fakecodecombobox.h"
#include <QEvent>
#include <QDebug>
#include <QSqlQuery>
#include <QSqlRecord>
#include <QSqlError>
#include <QSqlDatabase>
#include <QUuid>
#include <QTextCodec>

FakeCodeComboBox::FakeCodeComboBox(const QDomElement& doc_element, QWidget* parent) : QComboBox(parent)
{
    qRegisterMetaType<QPair<quint64, quint8>>("QPair<quint64, quint8>");
    QMetaType::registerComparators<QPair<quint64, quint8>>();
    addItem("无此参数", QVariant());

    auto db = QSqlDatabase::cloneDatabase(QSqlDatabase::database(), QUuid::createUuid().toString());
    if (!db.open()) {
        qDebug() << "数据库打开失败";
    }

    QSqlQuery query(db);
    if (query.exec(tr("SELECT * FROM FAKECODE"))){

        while (query.next()){
            auto code = query.value("CODE").value<quint8>();
            auto desc = query.value("DESC").toByteArray();
            auto phase_a = query.value("PHASE_A").value<quint16>();
            auto phase_b = query.value("PHASE_B").value<quint16>();
            auto poly_a = query.value("POLY_A").value<quint16>();
            auto poly_b = query.value("POLY_B").value<quint16>();

            QTextCodec* utf8 = QTextCodec::codecForName("UTF-8");
            QTextCodec* encode = QTextCodec::codecForName("gb2312");

            auto unicode_str = encode->toUnicode(desc);
            auto utf8_bytearray = utf8->fromUnicode(unicode_str);

            quint64 value = 0;
            value = (value << 16) | poly_b;
            value = (value << 16) | phase_b;
            value = (value << 16) | poly_a;
            value = (value << 16) | phase_a;

//            qDebug() << QString::number(value, 16) << QString::number(code, 16);
            addItem(QString::fromUtf8(utf8_bytearray), QVariant::fromValue(qMakePair(value, code)));
        }
    } else {
        qDebug() << "数据库查询失败" << query.lastError();
    }
    installEventFilter(this);
}

QVariant FakeCodeComboBox::fakeCodeDesc() const
{
    auto desc_code_pair = currentData().value<QPair<quint64, quint8>>();
    auto desc = desc_code_pair.first;
    return desc;
}

void FakeCodeComboBox::setFakeCodeDesc(const QVariant& param_vaule)
{
    if (!param_vaule.canConvert<quint64>()) {
        return;
    }

    cur_fake_code_desc_ = param_vaule.value<quint64>();
    int index = findData(QVariant::fromValue(qMakePair(cur_fake_code_desc_, cur_fake_code_)));
    if (index == -1){
        setCurrentIndex(0);
    } else {
        setCurrentIndex(index);
    }
}

QVariant FakeCodeComboBox::fakeCode() const
{
    auto desc_code_pair = currentData().value<QPair<quint64, quint8>>();
    auto code = desc_code_pair.second;
    return code;
}

void FakeCodeComboBox::setFakeCode(const QVariant &param_vaule)
{
    if (!param_vaule.canConvert<quint8>()) {
        return;
    }

    cur_fake_code_ = param_vaule.value<quint8>();

    int index = findData(QVariant::fromValue(qMakePair(cur_fake_code_desc_, cur_fake_code_)));
    if (index == -1){
        setCurrentIndex(0);
    } else {
        setCurrentIndex(index);
    }
}

bool FakeCodeComboBox::editMode() const
{
    return edit_mode_;
}

void FakeCodeComboBox::setEditMode(bool edit_mode)
{
    edit_mode_ = edit_mode;
}

bool FakeCodeComboBox::eventFilter(QObject *obj, QEvent *event)
{
    if (edit_mode_){
        return QObject::eventFilter(obj, event);
    }
    if (event->type() == QEvent::Wheel) {
        return true;
    }
    else if (event->type() == QEvent::KeyPress) {
        return true;
    }
    else if (event->type() == QEvent::KeyRelease) {
        return true;
    }
    else if (event->type() == QEvent::MouseButtonPress) {
        return true;
    }
    else if (event->type() == QEvent::MouseButtonRelease) {
        return true;
    }
    else if (event->type() == QEvent::MouseButtonDblClick) {
        return true;
    }
    else {
        return QObject::eventFilter(obj, event);
    }
}
