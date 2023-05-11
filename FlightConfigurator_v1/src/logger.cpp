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
    return pinstance_;
}

void Logger::log(const QString& msg){
    QString filename="Logs";
    QFile file(filename);
    if ( file.open(QIODevice::ReadWrite) ){
        QTextStream stream( &file );
        stream << msg << "\n";
    }
    file.close();
}
