#ifndef HEARTBEAT_HANDLER_H
#define HEARTBEAT_HANDLER_H

// MAVLink
#include <mavlink.h>

// Internal
#include "abstract_handler.h"

namespace domain
{
    class MessageHandler: public AbstractHandler
    {
        Q_OBJECT
        mavlink_heartbeat_t heartbeat;
        mavlink_global_position_int_t global_position_int;
        mavlink_attitude_t attitude;
        mavlink_scaled_imu_t scaled_imu;
        mavlink_param_value_t param_value;

    public:
        MessageHandler(MavLinkCommunicator* communicator);

        mavlink_heartbeat_t get_heartbeat();
        mavlink_global_position_int_t get_global_position_int();
        mavlink_attitude_t get_attitude();
        mavlink_scaled_imu_t get_scaled_imu();
        mavlink_param_value_t get_param_value();

        void log();

    public slots:
        void process_message(const mavlink_message_t& message) override;

    signals:
        void param_received(const mavlink_param_value_t& param_value);
    };
}

#endif // HEARTBEAT_HANDLER_H
