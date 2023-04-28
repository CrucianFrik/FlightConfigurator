#include "mavlink_communicator.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "abstract_link.h"
#include <QDebug>
#include <iostream>

using namespace domain;

MavLinkCommunicator::MavLinkCommunicator(uint8_t systemId, uint8_t componentId,
                                         QObject* parent):
    QObject(parent),
    m_lastReceivedLink(nullptr),
    m_systemId(systemId),
    m_componentId(componentId)
{
    qRegisterMetaType<mavlink_message_t>("mavlink_message_t");
}

QList<AbstractLink*> MavLinkCommunicator::links() const
{
    return m_linkChannels.keys();
}

uint8_t MavLinkCommunicator::systemId() const
{
    return m_systemId;
}

uint8_t MavLinkCommunicator::componentId() const
{
    return m_componentId;
}

AbstractLink* MavLinkCommunicator::getLastReceivedLink() const
{
    return m_lastReceivedLink;
}

quint8 MavLinkCommunicator::linkChannel(AbstractLink* link) const
{
    return m_linkChannels.value(link, 0);
}

void MavLinkCommunicator::addLink(AbstractLink* link, uint8_t channel)
{
    if (m_linkChannels.contains(link)) return;

    m_linkChannels[link] = channel;
    connect(link, &AbstractLink::dataReceived,
            this, &MavLinkCommunicator::onDataReceived);
}

void MavLinkCommunicator::removeLink(AbstractLink* link)
{
    if (!m_linkChannels.contains(link)) return;

    m_linkChannels.remove(link);
    disconnect(link, &AbstractLink::dataReceived,
            this, &MavLinkCommunicator::onDataReceived);
}

void MavLinkCommunicator::setSystemId(uint8_t systemId)
{
    m_systemId = systemId;
}

void MavLinkCommunicator::setComponentId(uint8_t componentId)
{
    m_componentId = componentId;
}

void MavLinkCommunicator::sendMessage(mavlink_message_t& message, AbstractLink* link)
{
    if (!link || !link->isUp()) {
        qDebug() << "the target link is not up!";
        return;
    }

    uint8_t buffer[MAVLINK_MAX_PACKET_LEN];
    int lenght = mavlink_msg_to_send_buffer(buffer, &message);

    if (!lenght) return;

    link->sendData(QByteArray((const char*)buffer, lenght));
}

void MavLinkCommunicator::sendMessageOnLastReceivedLink(mavlink_message_t& message)
{
    this->sendMessage(message, m_lastReceivedLink);
}

void MavLinkCommunicator::sendMessageOnAllLinks(mavlink_message_t& message)
{
    for (AbstractLink* link: m_linkChannels.keys()){
        this->sendMessage(message, link);
    }
}

void MavLinkCommunicator::onDataReceived(const QByteArray& data)
{
    mavlink_message_t message;
    mavlink_status_t status;

    m_lastReceivedLink = qobject_cast<AbstractLink*>(this->sender());
    if (!m_lastReceivedLink) return;

    uint8_t channel = m_linkChannels.value(m_lastReceivedLink);
    for (int pos = 0; pos < data.length(); ++pos)
    {
        if (!mavlink_parse_char(channel, (uint8_t)data[pos],
                                &message, &status))
            continue;

        if (message.sysid)
            receivedMsgId.insert(message.msgid);
        emit messageReceived(message);
    }
}

void MavLinkCommunicator::logReceivedMsgs(bool print_once){
    static int flag = 0;
    if (!print_once || (print_once && flag == 10)){
        std::cout << "[";
        for (std::set<uint32_t>::iterator it = receivedMsgId.begin(); it != receivedMsgId.end(); it++)
                std::cout << *it << ", ";
        std::cout << "]" << std::endl;
    }
    flag++;
}
