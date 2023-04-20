#ifndef GLOBAL_POSITION_INT_HANDLER_H
#define GLOBAL_POSITION_INT_HANDLER_H

// MAVLink
#include <mavlink.h>

// Internal
#include "abstract_handler.h"

namespace domain
{
    class GlobalPositionIntHandler: public AbstractHandler
    {
	Q_OBJECT
    mavlink_global_position_int_t global_position_int;

    public:
	GlobalPositionIntHandler(MavLinkCommunicator* communicator);
    mavlink_global_position_int_t const& getData();

    public slots:
	void processMessage(const mavlink_message_t& message) override;

    private:
	//костыль, пикс отправляет сигнал, видимо, пределжительное время и за него
	//qt успевает вызвать слот дважды (типа как если бы пользователь кнопку зажал)
	int c = 0; //FIXME
    };
}

#endif // GLOBAL_POSITION_INT_HANDLER_H
