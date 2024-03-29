#include "serial_link.h"

// Qt
#include <QSerialPort>
#include <QDebug>

using namespace domain;

SerialLink::SerialLink(const QString& portName, qint32 baudRate,
                       QObject* parent):
    AbstractLink(parent),
    m_port(new QSerialPort(portName, this))
{
    m_port->setBaudRate(baudRate);

    connect(m_port, &QSerialPort::readyRead, this, &SerialLink::readSerialData);
}

bool SerialLink::isUp() const
{
    return m_port->isOpen();
}

QString SerialLink::portName() const
{
    return m_port->portName();
}

qint32 SerialLink::baudRate() const
{
    return m_port->baudRate();
}

int SerialLink::up()
{
    if (this->isUp()) return -2;

    if (!m_port->open(QIODevice::ReadWrite))
    {
        qWarning("Serial port connection error: '%s'!",
                 qPrintable(m_port->errorString()));

        m_port->close();
        return 0;
    }
    else
    {
        emit upChanged(true);
        return 1;
    }
}

int SerialLink::down()
{
    if (!this->isUp()) return 0;

    m_port->close();
    emit upChanged(false);
    return 1;
}

void SerialLink::sendData(const QByteArray& data)
{
    m_port->write(data, data.size());
}

void SerialLink::setPortName(QString portName)
{
    if (m_port->portName() == portName) return;

    m_port->setPortName(portName);
    emit portNameChanged(m_port->portName());
}

void SerialLink::setBaudRate(qint32 baudRate)
{
    if (m_port->baudRate() == baudRate) return;

    m_port->setBaudRate(baudRate);
    emit baudRateChanged(m_port->baudRate());
}

void SerialLink::readSerialData()
{
    emit dataReceived(m_port->readAll());
}
