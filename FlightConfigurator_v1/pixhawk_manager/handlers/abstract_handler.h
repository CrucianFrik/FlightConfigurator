#ifndef ABSTRACT_HANDLER_H
#define ABSTRACT_HANDLER_H

// MAVLink
#include <mavlink_types.h>

// Qt
#include <QObject>

#define DEBUG 0

namespace domain
{
    class MavLinkCommunicator;

    class AbstractHandler: public QObject
    {
        Q_OBJECT

    public:
        explicit AbstractHandler(MavLinkCommunicator* communicator);

    protected slots:
        virtual void process_message(const mavlink_message_t& message) = 0;

    protected:
        MavLinkCommunicator* const m_communicator;
    };
}

#endif // ABSTRACT_HANDLER_H
