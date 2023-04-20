#ifndef SCALED_IMU_HANDLER_H
#define SCALED_IMU_HANDLER_H

// MAVLink
#include <mavlink.h>

// Internal
#include "abstract_handler.h"

namespace domain
{
    class ScaledImuHandler: public AbstractHandler
    {
	Q_OBJECT
    mavlink_scaled_imu_t scaled_imu;

    public:
        ScaledImuHandler(MavLinkCommunicator* communicator);
    mavlink_scaled_imu_t const& getData();

    public slots:
        void processMessage(const mavlink_message_t& message) override;

    private:
	//костыль, пикс отправляет сигнал, видимо, пределжительное время и за него
	//qt успевает вызвать слот дважды (типа как если бы пользователь кнопку зажал)
	int c = 0; //FIXME
    };
}

#endif // SCALED_IMU_HANDLER_H
