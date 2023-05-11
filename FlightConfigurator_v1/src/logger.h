#ifndef LOGGER_H
#define LOGGER_H

#include <QString>
#include <QFile>
#include <QTextStream>
#include <mutex>


class Logger{
public:
    Logger(Logger &other) = delete;
    void operator= (const Logger&) = delete;

    static Logger *GetInstance();
    void log(const QString& msg);

private:
    Logger() {};
    static Logger* pinstance_;
    static std::mutex mutex_;

    ~Logger() {};
};

#endif // LOGGER_H
