#ifndef PIXHAWK_MANAGER_H
#define PIXHAWK_MANAGER_H

// Internal
#include "udp_link.h"
#include "serial_link.h"

#include "gcs_communicator_factory.h"
#include "mavlink_communicator.h"
#include "heartbeat_handler.h"
#include "attitude_handler.h"
#include "scaled_imu_handler.h"
#include "abstract_link.h"

// MAVLink
#include <mavlink.h>
#include <QDebug>

class PixhawkManager: public QObject{
    Q_OBJECT
    domain::MavLinkCommunicator communicator;
    domain::HeartbeatHandler heartbeatHandler;
    domain::AttitudeHandler attitudeHandler;
    domain::ScaledImuHandler scaledImuHandler;
    domain::SerialLink link;

public:
    PixhawkManager(const QString& path, qint32 speed);
    mavlink_heartbeat_t const& getHeartbeat();
    mavlink_attitude_t const& getAttitude();
    mavlink_scaled_imu_t const& getScaledImu();
    void setMsgFrequency(uint8_t msg_id, int8_t frequency);
    void setMsgFrequencySlot(const mavlink_message_t& message);
    void MySig();
    void logReceivedMsgs(bool print_once = 0);
};


#endif // PIXHAWK_MANAGER_H
