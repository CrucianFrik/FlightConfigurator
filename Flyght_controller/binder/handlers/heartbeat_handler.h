#ifndef HEARTBEAT_HANDLER_H
#define HEARTBEAT_HANDLER_H

// MAVLink
#include <mavlink.h>

// Internal
#include "abstract_handler.h"

namespace domain
{
    class HeartbeatHandler: public AbstractHandler
    {
        Q_OBJECT
        mavlink_heartbeat_t heartbeat;

    public:
        HeartbeatHandler(MavLinkCommunicator* communicator);
        mavlink_heartbeat_t const& getData();

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
        //костыль, пикс отправляет сигнал, видимо, пределжительное время и за него
        //qt успевает вызвать слот дважды (типа как если бы пользователь кнопку зажал)
        int c = 0; //FIXME
    };
}

#endif // HEARTBEAT_HANDLER_H
