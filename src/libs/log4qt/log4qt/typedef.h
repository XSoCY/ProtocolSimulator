#ifndef TYPEDEF_H
#define TYPEDEF_H

namespace Log4Qt
{
namespace TagStr {
    static const char *NullTag = "NULL";
    static const char *AllTag = "ALL";
    static const char *TraceTag = "TRACE";
    static const char *DebugTag = "DEBUG";
    static const char *InfoTag = "INFO";
    static const char *WarnTag = "WARN";
    static const char *ErrorTag = "ERROR";
    static const char *FatalTag = "FATAL";
    static const char *OffTag = "OFF";
    static const char *UncapturedTag = "Uncaptured";
}

namespace AttrName {
    static const char *DateTime = "DateTime";
    static const char *Logger = "Logger";
    static const char *Message = "Message";
    static const char *Level = "Level";
}

namespace HeaderFooter
{
    static const char *XmlHeader = "<?xml version='1.0' encoding='UTF-8'?>\n<log>";
    static const char *XmlFooter = "\n</log>";
    static const char *JsonHeader = "{\"log\":[";
    static const char *JsonFooter = "\n]}";
}
}

#endif // TYPEDEF_H
