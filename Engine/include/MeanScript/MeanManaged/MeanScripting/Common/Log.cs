using Microsoft.VisualBasic;

namespace MeanScriptEngine
{
    public enum LogLevel
    {
        INFO,
        TRACE,
        DEBUG,
        WARN,
        ERROR
    };

    public static class Log
    {
        public static void Info(string message)
        {
            MeanNativeApi.LogMsg(message, LogLevel.INFO);
        }

        public static void Trace(string message)
        {
            MeanNativeApi.LogMsg(message, LogLevel.TRACE);
        }

        public static void Debug(string message)
        {
            MeanNativeApi.LogMsg(message, LogLevel.DEBUG);
        }

        public static void Warn(string message)
        {
            MeanNativeApi.LogMsg(message, LogLevel.WARN);
        }

        public static void Error(string message)
        {
            MeanNativeApi.LogMsg(message, LogLevel.ERROR);
        }
    }
}