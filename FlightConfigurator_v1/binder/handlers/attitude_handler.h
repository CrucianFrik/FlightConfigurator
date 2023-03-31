#ifndef ATTITUDE_HANDLER_H
#define ATTITUDE_HANDLER_H

// MAVLink
#include <mavlink.h>

//Internal
#include "abstract_handler.h"

namespace domain
{
    class AttitudeHandler: public AbstractHandler
    {
        Q_OBJECT
        mavlink_attitude_t attitude;
        //костыль, пикс отправляет сигнал, видимо, пределжительное время и за него
        //qt успевает вызвать слот дважды (типа как если бы пользователь кнопку зажал)
        int c = 0; //FIXME

    public:
        AttitudeHandler(MavLinkCommunicator* communicator);
        mavlink_attitude_t const& getData();

    public slots:
        void processMessage(const mavlink_message_t& message) override;
    };
}

#endif // ATTITUDE_HANDLER_H
