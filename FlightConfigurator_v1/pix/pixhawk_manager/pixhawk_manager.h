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
#include "hendler_structs.h"

// MAVLink
#include <mavlink.h>
#include <QDebug>

//#include <iostream>
//#include <fstream>

class PixhawkManager: public QObject{
    Q_OBJECT
    domain::MavLinkCommunicator communicator;
    domain::MessageHandler message_hendler;
    domain::SerialLink link;
    std::map<uint16_t, ParamInfo> params_list;
    std::map<uint16_t, ParamInfo> updated_items_in_params_list;
    bool all_params_received_flag = 0;
    ConnectionStatus connection_status = ConnectionStatus::none;
    //std::ofstream out;

    void add_param_to_params_list(const mavlink_param_value_t &param);

public:
    PixhawkManager(const QString& path, qint32 speed);

    void update_param_in_params_list();
    void remember__new_param_value(int index, float new_value);

    mavlink_heartbeat_t get_heartbeat();
    mavlink_attitude_t get_attitude();
    mavlink_scaled_imu_t get_scaled_imu();
    mavlink_global_position_int_t get_global_position_int();
    int get_connection_status();
    const std::map<uint16_t, ParamInfo>& get_parametr_list();
    const std::map<uint16_t, ParamInfo>& get_updated_items_in_params_list();
    float get_param_val(uint8_t index);
    bool is_all_params_received();

    void set_msg_frequency(uint8_t msg_id, int8_t frequency);
    bool set_param(int param_inndex, float new_value);
    int upload_new_params();

    void request_all_params();

public slots:
    void param_received(const mavlink_param_value_t& param_value);

signals:
    void all_params_received();
};


#endif // PIXHAWK_MANAGER_H
