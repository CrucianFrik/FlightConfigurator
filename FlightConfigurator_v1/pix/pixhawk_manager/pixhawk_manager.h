#ifndef PIXHAWK_MANAGER_H
#define PIXHAWK_MANAGER_H

#include <map>
#include <vector>

// Internal
#include "udp_link.h"
#include "serial_link.h"
#include "gcs_communicator_factory.h"
#include "mavlink_communicator.h"
#include "message_handler.h"
#include "abstract_link.h"
#include "param_info.h"

// MAVLink
#include <mavlink.h>
#include <QDebug>

class PixhawkManager: public QObject{
    Q_OBJECT
    domain::MavLinkCommunicator communicator;
    domain::MessageHandler message_hendler;
    domain::SerialLink link;
    std::map<uint16_t, ParamInfo> param_list;
    std::vector<int> updated_param_list_params;
    bool all_params_received_flag = 0;

    void add_param_to_param_list(const mavlink_param_value_t &param);

public:
    PixhawkManager(const QString& path, qint32 speed);

    void update_param_in_param_list(uint8_t index, float new_value);

    mavlink_heartbeat_t get_heartbeat();
    mavlink_attitude_t get_attitude();
    mavlink_scaled_imu_t get_scaled_imu();
    const std::map<uint16_t, ParamInfo>& get_parametr_list();
    bool is_all_params_received();

    void set_msg_frequency(uint8_t msg_id, int8_t frequency);
    bool set_param(uint16_t param_inndex, float new_value);

    void request_all_params();

public slots:
    void param_received(const mavlink_param_value_t& param_value);

signals:
    void all_params_received();
};


#endif // PIXHAWK_MANAGER_H
