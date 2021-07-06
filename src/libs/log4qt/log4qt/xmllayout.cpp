/******************************************************************************
 * Dependencies
 ******************************************************************************/


#include "log4qt/xmllayout.h"
#include "log4qt/typedef.h"

#include <QtCore/QDebug>
#include <QtCore/QDateTime>
#include <qxmlstream.h>
#include "log4qt/helpers/datetime.h"
#include "log4qt/helpers/patternformatter.h"
#include "log4qt/logger.h"
#include "log4qt/loggingevent.h"



namespace Log4Qt
{


    /**************************************************************************
     * Declarations
     **************************************************************************/



    /**************************************************************************
     * C helper functions
     **************************************************************************/



    /**************************************************************************
     * Class implementation: TTCCLayout
     **************************************************************************/
    XMLLayout::XMLLayout(QObject *pParent) :
        Layout(pParent),
        mCategoryPrefixing(true),
        mContextPrinting(true),
        mThreadPrinting(true),
        m_timeFormat("yyyy-MM-dd hh:mm:ss.zzz")
    {
        setHeader(HeaderFooter::XmlHeader);
        setFooter(HeaderFooter::XmlFooter);
    }

    XMLLayout::~XMLLayout()
    {
    }

    QString XMLLayout::format(const LoggingEvent &rEvent)
    {
        QString tagStr;
        Level level = rEvent.level();
        switch(level.toInt())
        {
        case Level::NULL_INT:
            tagStr = TagStr::NullTag;
            break;
        case Level::ALL_INT:
            tagStr = TagStr::AllTag;
            break;
        case Level::TRACE_INT:
            tagStr = TagStr::TraceTag;
            break;
        case Level::DEBUG_INT:
            tagStr = TagStr::DebugTag;
            break;
        case Level::INFO_INT:
            tagStr = TagStr::InfoTag;
            break;
        case Level::WARN_INT:
            tagStr = TagStr::WarnTag;
            break;
        case Level::ERROR_INT:
            tagStr = TagStr::ErrorTag;
            break;
        case Level::FATAL_INT:
            tagStr = TagStr::FatalTag;
            break;
        case Level::OFF_INT:
            tagStr = TagStr::OffTag;
            break;
        default:
            tagStr = TagStr::UncapturedTag;
//            Q_ASSERT_X(false, __func__, "uncaptured log event level");
            break;
        }

        QString result;
        QXmlStreamWriter writer(&result);
        writer.setAutoFormatting(true);
        writer.setAutoFormattingIndent(2);
        writer.setCodec("UTF-8");
        writer.writeStartElement(tagStr);
        writer.writeAttribute(AttrName::DateTime,
                              DateTime::fromMilliSeconds(rEvent.timeStamp()).toString(m_timeFormat));
        writer.writeAttribute(AttrName::Logger, rEvent.loggerName());
        writer.writeAttribute(AttrName::Message, rEvent.message());
        writer.writeEndElement();
        return result;
    }

#ifndef QT_NO_DEBUG_STREAM
    QDebug XMLLayout::debug(QDebug &rDebug) const
    {
        rDebug.nospace() << "XMLLayout("
            << "name:" << name() << " "
            << "categoryprefixing:" << categoryPrefixing() << " "
            << "contextprinting:" << contextPrinting() << " "
            << "referencecount:" << referenceCount() << " "
            << "threadprinting:" << threadPrinting()
            << ")";
        return rDebug.space();
    }
#endif // QT_NO_DEBUG_STREAM



    /**************************************************************************
     * Implementation: Operators, Helper
     **************************************************************************/


} // namespace Log4Qt
