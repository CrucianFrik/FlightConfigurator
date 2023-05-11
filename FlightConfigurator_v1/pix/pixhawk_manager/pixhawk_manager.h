#ifndef PIXHAWK_MANAGER_H
#define PIXHAWK_MANAGER_H

#include <map>
#include <vector>
#include <array>
#include <mavlink.h>
#include <QDebug>
#include <QList>

#include "udp_link.h"
#include "serial_link.h"
#include "gcs_communicator_factory.h"
#include "mavlink_communicator.h"
#include "message_handler.h"
#include "abstract_link.h"
#include "hendler_structs.h"

class PixhawkManager: public QObject{
    Q_OBJECT
    domain::MavLinkCommunicator communicator;
    domain::MessageHandler message_hendler;
    domain::SerialLink link;

    std::map<uint16_t, ParamInfo> params_list;
    std::map<uint16_t, ParamInfo> updated_items_in_params_list;
    std::map<QString, uint16_t> id_from_index;
    QList<std::array<double, 3>> mission_seq;

    ConnectionStatus connection_status = ConnectionStatus::none;
    bool all_params_received_flag = 0;

    // PARAMS
    void add_param_to_params_list(const mavlink_param_value_t &param);

public:
    PixhawkManager(const QString& path, qint32 speed);

    // PARAMS
    int upload_new_params();
    bool set_param(int param_inndex, float new_value);
    void remember_new_param_value(int index, float new_value);
    void reset_new_param_values();
    void request_all_params();
    float get_param_val(uint8_t index);
    int get_param_id_from_index(QString s);


    //MSGS
    void set_msg_frequency(uint8_t msg_id, int8_t frequency);
    mavlink_heartbeat_t get_heartbeat();
    mavlink_attitude_t get_attitude();
    mavlink_scaled_imu_t get_scaled_imu();
    mavlink_global_position_int_t get_global_position_int();

    //CHECKERS
    bool is_all_params_received();

    //DATA GETTERS
    const std::map<uint16_t, ParamInfo>& get_parametr_list();
    const std::map<uint16_t, ParamInfo>& get_updated_items_in_params_list();

    //MISSION
    void upload_flight_mission(QList<std::array<double, 3>>& arr);
    int set_mission_items_count(int count);

    //CONNECTION
    int disconnect();
    ConnectionStatus get_connection_status();

public slots:
    void param_received(const mavlink_param_value_t& param_value);
    void set_mission_point(uint16_t n);
    void process_mission_status(mavlink_mission_ack_t);

signals:
    void all_params_received();
};


#endif // PIXHAWK_MANAGER_H
