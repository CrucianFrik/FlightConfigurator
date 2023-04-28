#ifndef PIXHAWK_MANAGER_H
#define PIXHAWK_MANAGER_H

#include <map>

// Internal
#include "udp_link.h"
#include "serial_link.h"
#include "gcs_communicator_factory.h"
#include "mavlink_communicator.h"
#include "message_handler.h"
#include "abstract_link.h"

// MAVLink
#include <mavlink.h>
#include <QDebug>

struct ParamInfo{
        char param_id[16];
        uint16_t param_type;
        float param_value;
};

class PixhawkManager: public QObject{
    Q_OBJECT
    domain::MavLinkCommunicator communicator;
    domain::MessageHandler message_hendler;
    domain::SerialLink link;
    std::map<uint16_t, ParamInfo> param_list;
    bool all_params_received_flag = 0;

    void update_param_list(const mavlink_param_value_t &param, float new_value);
    void add_to_param_list(const mavlink_param_value_t &param);

public:
    PixhawkManager(const QString& path, qint32 speed);
    mavlink_heartbeat_t get_heartbeat();
    mavlink_attitude_t get_attitude();
    mavlink_scaled_imu_t get_scaled_imu();
    void set_msg_frequency(uint8_t msg_id, int8_t frequency);
    void request_all_params();
    bool set_param(uint16_t param_inndex, float new_value);
    void log_received_msgs(bool print_once = 0);

public slots:
    void request_params_slot(const mavlink_param_value_t& param_value);
};


#endif // PIXHAWK_MANAGER_H
