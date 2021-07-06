#include "uifactory.h"
#include "bcddateedit.h"
#include "bitcombobox.h"
#include "bitstatuslabel.h"
#include "bittimesetting.h"
#include "comboboxwithdouble.h"
#include "datacombobox.h"
#include "doublespinbox.h"
#include "fakecodecombobox.h"
#include "framerecordtablewidget.h"
#include "hexlineedit.h"
#include "integerdoublespinbox.h"
#include "integerspinbox.h"
#include "integerstatuslabel.h"
#include "layoutwidget.h"
#include "modeswitchwidget.h"
#include "paramlisttablewidget.h"
#include "snrdisplay.h"
#include "specialnagativedoublespinbox.h"
#include "standardtimesetting.h"
#include "stringlineedit.h"
#include "t0timesetting.h"
#include "timestampdisplay.h"
#include <QDebug>

UiFactory::UiFactory() {}

UiFactory& UiFactory::instance()
{
    static UiFactory instance;
    return instance;
}

QWidget* UiFactory::createProduct(const QString& type, const QDomElement& ui_xml, const QDomElement& relation_xml)
{
    if (ui_xml.isNull()) {
        return nullptr;
    }
    if (type == "StringLineEdit") {
        return new StringLineEdit(ui_xml);
    }
    else if (type == "HexLineEdit") {
        return new HexLineEdit(ui_xml);
    }
    else if (type == "DataComboBox") {
        return new DataComboBox(ui_xml);
    }
    else if (type == "IntegerDoubleSpinBox") {
        return new IntegerDoubleSpinBox(ui_xml);
    }
    else if (type == "IntegerSpinBox") {
        return new IntegerSpinBox(ui_xml);
    }
    else if (type == "BitStatusLabel") {
        return new BitStatusLabel(ui_xml);
    }
    else if (type == "ParamListTableWidget") {
        return new ParamListTableWidget(ui_xml);
    }
    else if (type == "LayoutWidget") {
        return new LayoutWidget(ui_xml, relation_xml);
    }
    else if (type == "ModeSwitch") {
        return new ModeSwitchWidget(ui_xml);
    }
    else if (type == "SNRDisplay") {
        return new SNRDisplay(ui_xml);
    }
    else if (type == "TimeStampDisplay") {
        return new TimeStampDisplay(ui_xml);
    }
    else if (type == "IntegerStatusLabel") {
        return new IntegerStatusLabel(ui_xml);
    }
    else if (type == "T0TimeSetting") {
        return new T0TimeSetting(ui_xml);
    }
    else if (type == "FakeCodeComboBox") {
        return new FakeCodeComboBox(ui_xml);
    }
    else if (type == "BitTimeSetting") {
        return new BitTimeSetting(ui_xml);
    }
    else if (type == "SpecialNagativeDoubleSpinbox") {
        return new SpecialNagativeDoubleSpinbox(ui_xml);
    }
    else if (type == "ComboboxWithDouble") {
        return new ComboboxWithDouble(ui_xml);
    }
    else if (type == "BitCombobox") {
        return new BitCombobox(ui_xml);
    }
    else if (type == "DoubleSpinBox") {
        return new DoubleSpinBox(ui_xml);
    }
    else if (type == "BcdDateEdit") {
        return new BcdDateEdit(ui_xml);
    }
    else if (type == "StandardTimeSetting") {
        return new StandardTimeSetting(ui_xml);
    }
    else if (type == "FrameRecordTableWidget") {
        return new FrameRecordTableWidget(ui_xml);
    }
    else {
        qDebug() << "未知控件类型";
        return nullptr;
    }
}
