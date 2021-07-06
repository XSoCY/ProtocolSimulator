#ifndef XMLLAYOUT_H
#define XMLLAYOUT_H

#include "log4qt_global.h"

/******************************************************************************
 * Dependencies
 ******************************************************************************/

#include "log4qt/layout.h"


/******************************************************************************
 * Declarations
 ******************************************************************************/

namespace Log4Qt
{

    class LoggingEvent;
    class PatternFormatter;

    /*!
     * \brief The class XMLLayout outputs the time, thread, logger and nested
     *        diagnostic context information of a logging event.
     *
     * \note The ownership and lifetime of objects of this class are managed.
     *       See \ref Ownership "Object ownership" for more details.
     */
class LIBLOG4QTSHARED_EXPORT XMLLayout : public Layout
{
    Q_OBJECT

    /*!
     * The property holds if the logger name is part of the formatted output.
     *
     * The default value is true for including the logger name.
     *
     * \sa categoryPrefixing(), setCategoryPrefixing()
     */
    Q_PROPERTY(bool categoryPrefixing READ categoryPrefixing WRITE setCategoryPrefixing)

    /*!
     * The property holds if the nested context information is part of the
     * formatted output.
     *
     * The default value it true for including the nested context information.
     *
     * \sa contextPrinting(), setContextPrinting()
     */
    Q_PROPERTY(bool contextPrinting READ contextPrinting WRITE setContextPrinting)

    /*!
     * The property holds if the thread name is part of the formatted output.
     *
     * The default value it true for including the thread name.
     *
     * \sa threadPrinting(), setThreadPrinting()
     */
    Q_PROPERTY(bool threadPrinting READ threadPrinting WRITE setThreadPrinting)

public:
    XMLLayout(QObject *pParent = 0);
    virtual ~XMLLayout();
private:
    XMLLayout(const XMLLayout &rOther); // Not implemented
    XMLLayout &operator=(const XMLLayout &rOther); // Not implemented

public:
    virtual QString contentType() const;
    bool categoryPrefixing() const;
    bool contextPrinting() const;
    // JAVA: bool ignoresThrowable() const;
    bool threadPrinting() const;
    void setCategoryPrefixing(bool categoryPrefixing);
    void setContextPrinting(bool contextPrinting);
    // JAVA: setIgnoresThrowable(bool ignoresThrowable);
    void setThreadPrinting(bool threadPrinting);
    virtual QString format(const LoggingEvent &rEvent);

protected:
#ifndef QT_NO_DEBUG_STREAM
    /*!
     * Writes all object member variables to the given debug stream
     * \a rDebug and returns the stream.
     *
     * <tt>
     * %XMLLayout(name:"TTCC" categoryprefixing:true
     *             contextprinting:true dateformat:"ISO8601"
     *             referencecount:1 threadprinting:true)
     * </tt>
     * \sa QDebug, operator<<(QDebug debug, const LogObject &rLogObject)
     */
    virtual QDebug debug(QDebug &rDebug) const;
#endif // QT_NO_DEBUG_STREAM

private:
    bool mCategoryPrefixing;
    bool mContextPrinting;
    bool mThreadPrinting;
    QString m_timeFormat;
};


/**************************************************************************
 * Operators, Helper
 **************************************************************************/


/**************************************************************************
 * Inline
 **************************************************************************/

inline QString XMLLayout::contentType() const
{
    return QString::fromLatin1("text/xml");
}

inline bool XMLLayout::categoryPrefixing() const
{	return mCategoryPrefixing;	}

inline bool XMLLayout::contextPrinting() const
{	return mContextPrinting;	}

inline bool XMLLayout::threadPrinting() const
{	return mThreadPrinting;	}

inline void XMLLayout::setCategoryPrefixing(bool categoryPrefixing)
{	mCategoryPrefixing = categoryPrefixing;
}

inline void XMLLayout::setContextPrinting(bool contextPrinting)
{	mContextPrinting = contextPrinting;
}

inline void XMLLayout::setThreadPrinting(bool threadPrinting)
{	mThreadPrinting = threadPrinting;
}

} // namespace Log4Qt
#endif // XMLLAYOUT_H

// Q_DECLARE_TYPEINFO(Log4Qt::XMLLayout, Q_COMPLEX_TYPE); // Use default
