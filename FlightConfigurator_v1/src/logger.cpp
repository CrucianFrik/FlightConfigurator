#include "logger.h"

Logger* Logger::pinstance_{nullptr};

std::mutex Logger::mutex_;

Logger *Logger::GetInstance()
{
    std::lock_guard<std::mutex> lock(mutex_);
    if (pinstance_ == nullptr)
    {
        pinstance_ = new Logger();
    }

    QString filename="../../config/Logs.txt";
    QFile file(filename);
    if ( file.open(QIODevice::WriteOnly) ){
        QTextStream stream( &file );
        stream << "logs" << endl;
    }
    file.close();

    return pinstance_;
}

void Logger::log(const QString& msg){
    QString filename="../../config/Logs.txt";
    QFile file(filename);
    if ( file.open(QIODevice::Append) ){
        QTextStream stream( &file );
        stream << msg << endl;
    }
    file.close();
}
