#ifndef MAVLINK_COMMUNICATOR_H
#define MAVLINK_COMMUNICATOR_H

#include <set>

// MAVLink
#include <mavlink_types.h>

// Qt
#include <QObject>
#include <QMap>

#include <set>

namespace domain
{
    class AbstractLink;

    class MavLinkCommunicator: public QObject
    {
        Q_OBJECT
        std::set<uint32_t> receivedMsgId;

    public:
        MavLinkCommunicator(uint8_t systemId = 255, uint8_t componentId = 0,
                            QObject* parent = nullptr);

        QList<AbstractLink*> links() const;

        uint8_t systemId() const;
        uint8_t componentId() const;
        AbstractLink* getLastReceivedLink () const;
        quint8 linkChannel(AbstractLink*) const;
        void logReceivedMsgs(bool print_once = 0); //FIXME

    public slots:
        void addLink(AbstractLink* link, uint8_t channel);
        void removeLink(AbstractLink* link);

        void setSystemId(uint8_t systemId);
        void setComponentId(uint8_t componentId);

        void sendMessage(mavlink_message_t& message, AbstractLink* link);
        void sendMessageOnLastReceivedLink(mavlink_message_t& message);
        void sendMessageOnAllLinks(mavlink_message_t& message);

    signals:
        void messageReceived(const mavlink_message_t& message);

    protected slots:
        void onDataReceived(const QByteArray& data);

    protected:
        QMap<AbstractLink*, uint8_t> m_linkChannels;
        AbstractLink* m_lastReceivedLink;

        uint8_t m_systemId;
        uint8_t m_componentId;
    };
}

#endif // MAVLINK_COMMUNICATOR_H
