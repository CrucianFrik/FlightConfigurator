#include "pixhawk_manager.h"

PixhawkManager::PixhawkManager(const QString& path, qint32 speed) : message_hendler(&communicator),
                                            link (path, speed)
{
    communicator.addLink(&link, MAVLINK_COMM_3);
    if (link.up())
        connection_status = ConnectionStatus::successful;
    else {
        connection_status = ConnectionStatus::failed;
        return;
    }

    QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
                     &message_hendler, &domain::MessageHandler::process_message);
    QObject::connect(&message_hendler, &domain::MessageHandler::param_received,
                     this, &PixhawkManager::param_received);
    QObject::connect(&message_hendler, &domain::MessageHandler::mission_req_received,
                     this, &PixhawkManager::set_mission_point);
    QObject::connect(&message_hendler, &domain::MessageHandler::mission_accepted,
                     this, &PixhawkManager::process_mission_status);

    int FREQUENCY = 100000;
    set_msg_frequency(MAVLINK_MSG_ID_GLOBAL_POSITION_INT, FREQUENCY);
    set_msg_frequency(MAVLINK_MSG_ID_ATTITUDE, FREQUENCY);
    set_msg_frequency(MAVLINK_MSG_ID_SCALED_IMU, FREQUENCY);
}


//////////////////////////////////////////////////////////////PARAMS//////////////////////////////////////////////////////////////////
int PixhawkManager::upload_new_params(){
    for (const auto &param_pair : updated_items_in_params_list){
        ParamInfo param = param_pair.second;
        uint8_t index = param_pair.first;
        params_list[index] = param;
        set_param(index, param.param_value);
    }
    updated_items_in_params_list = std::map<uint16_t, ParamInfo>{};
    return 0;
}

bool PixhawkManager::set_param(int param_index, float new_value){
    if (!all_params_received_flag) {
        qDebug() << "ERROR from PixhawkManager::set_param: the full "
                    "list of parameters has not been received "
                    "yet, updating is not possible";
        return 0;
    }
    if (params_list.count(param_index)){
        mavlink_message_t message;
        mavlink_param_set_t param_set;
        param_set.target_system = 1;
        param_set.target_component = 1;
        memcpy(param_set.param_id, params_list[param_index].param_id, sizeof(param_set.param_id));
        param_set.param_value = new_value;
        param_set.param_type = params_list[param_index].param_type;
        mavlink_msg_param_set_encode_chan(communicator.systemId(),
            communicator.componentId(), MAVLINK_COMM_3, &message, &param_set);
        communicator.sendMessageOnAllLinks(message);
        qDebug() << "WRITED PARAMETR" << params_list[param_index].param_id;
    }
    return 1;
}

void PixhawkManager::remember_new_param_value(int index, float new_value){
    if (params_list.find(index) == params_list.end()){
        qDebug() << "ERROR from PixhawkManager::remember_new_param_value: "
                    "no such file in params_list";
        return;
    }
    ParamInfo pi {"", params_list[index].param_type, new_value};
    memcpy(pi.param_id, params_list[index].param_id, sizeof(pi.param_id));
    updated_items_in_params_list[index] = pi;
    qDebug() << "CHANGE IS REMEMBERED" << index << pi.param_id << new_value;
}

void PixhawkManager::reset_new_param_values(){
    updated_items_in_params_list = std::map<uint16_t, ParamInfo>{};
}

void PixhawkManager::request_all_params() {
    mavlink_message_t message;
    mavlink_param_request_list_t param_request_list;
    param_request_list.target_system = 1;
    param_request_list.target_component = 1;
    mavlink_msg_param_request_list_encode_chan(communicator.systemId(), communicator.componentId(),
                        MAVLINK_COMM_3, &message, &param_request_list);
    communicator.sendMessageOnAllLinks(message);
    qDebug() << "ALL PARAMS REQESTED";
}

float PixhawkManager::get_param_val(uint8_t index){
    if (params_list.find(index) != params_list.end()){
        return params_list[index].param_value;
    }
    return 0;
}

int PixhawkManager::get_param_id_from_index(QString s){
    if (id_from_index.find(s) != id_from_index.end()){
        return id_from_index[s];
    }
    return -1;
}

void PixhawkManager::add_param_to_params_list(const mavlink_param_value_t &param){
    ParamInfo pi {"", param.param_type, param.param_value};
    memcpy(pi.param_id, param.param_id, sizeof(param.param_id));

    params_list.insert({param.param_index, pi});
    params_list[param.param_index] = pi;

    QString s{param.param_id};
    id_from_index[s] = param.param_index;
}

void PixhawkManager::param_received(const mavlink_param_value_t &param){
    if (param.param_index > param.param_count) {
        qDebug() << "#" << param.param_id << "(" << param.param_index
                 << ")" << ":" << param.param_value;
        return;
    }
    add_param_to_params_list(param);
    if (param.param_index == param.param_count-1) {
        message_hendler.log();
        all_params_received_flag = 1;
        emit all_params_received();
    }
    qDebug() << params_list[param.param_index].param_id << "(" << param.param_index
                << ")" << ":" << param.param_value;
}


//////////////////////////////////////////////////////////////MSGS//////////////////////////////////////////////////////////////////
void PixhawkManager::set_msg_frequency(uint8_t msg_id, int8_t frequency) {
    mavlink_message_t message;
    mavlink_command_long_t command_long;
    command_long.target_system = 1;
    command_long.target_component = 0;
    command_long.confirmation = 0;
    command_long.command = MAV_CMD_SET_MESSAGE_INTERVAL;
    command_long.param1 = msg_id;
    command_long.param2 = frequency;
    command_long.param3 = 0;
    command_long.param4 = 0;
    command_long.param5 = 0;
    command_long.param6 = 0;
    command_long.param7 = 0;
    mavlink_msg_command_long_encode_chan(communicator.systemId(), communicator.componentId(),
                        MAVLINK_COMM_3, &message, &command_long);
    communicator.sendMessageOnAllLinks(message);
}

mavlink_heartbeat_t PixhawkManager::get_heartbeat()
{ return message_hendler.get_heartbeat(); }

mavlink_attitude_t PixhawkManager::get_attitude()
{ return message_hendler.get_attitude(); }

mavlink_scaled_imu_t PixhawkManager::get_scaled_imu()
{ return message_hendler.get_scaled_imu(); }

mavlink_global_position_int_t PixhawkManager::get_global_position_int()
{ return message_hendler.get_global_position_int(); }


//////////////////////////////////////////////////////////////CHECKERS//////////////////////////////////////////////////////////////////
bool PixhawkManager::is_all_params_received()
{ return all_params_received_flag; }


///////////////////////////////////////////////////////////DATA GETTERS//////////////////////////////////////////////////////////////////
const std::map<uint16_t, ParamInfo>& PixhawkManager::get_parametr_list()
{ return params_list; }

const std::map<uint16_t, ParamInfo>& PixhawkManager::get_updated_items_in_params_list()
{ return updated_items_in_params_list; }

/////////////////////////////////////////////////////////////////MISSION//////////////////////////////////////////////////////////////////
void PixhawkManager::upload_flight_mission(QList<std::array<double, 3>>& arr){
    set_mission_items_count(arr.size());
    mission_seq = QList<std::array<double, 3>>{{0, 0, 0}} + arr;
}

int PixhawkManager::set_mission_items_count(int count){
    mavlink_message_t message;
    mavlink_mission_count_t mission_count;
    mission_count.target_system = 1;
    mission_count.target_component = 1;
    mission_count.count = count;
    mission_count.mission_type = MAV_MISSION_TYPE_MISSION;

    mavlink_msg_mission_count_encode_chan(communicator.systemId(), communicator.componentId(),
                        MAVLINK_COMM_3, &message, &mission_count);
    communicator.sendMessageOnAllLinks(message);
    qDebug() << "MISSION COUNT UPLOADED";
    //for (const auto &point : points_seq){}
    return 0;
}

void PixhawkManager::set_mission_point(uint16_t n){
    mavlink_message_t message;
    mavlink_mission_item_int_t mission_item_int;
    mission_item_int.target_system = 1;
    mission_item_int.target_component = 1;
    mission_item_int.seq = n;
    mission_item_int.frame = MAV_FRAME_GLOBAL_RELATIVE_ALT;
    mission_item_int.command = MAV_CMD_NAV_WAYPOINT;
    mission_item_int.x = mission_seq[n][0]*pow(10, 7);
    mission_item_int.y = mission_seq[n][1]*pow(10, 7);
    mission_item_int.z = mission_seq[n][2];
    mission_item_int.autocontinue = 1;
    mission_item_int.current = 1;
    mission_item_int.param1 = 10;
    mission_item_int.param2 = 10;
    mission_item_int.mission_type = MAV_MISSION_TYPE_MISSION;
    mavlink_msg_mission_item_int_encode_chan(communicator.systemId(), communicator.componentId(),
                        MAVLINK_COMM_3, &message, &mission_item_int);
    communicator.sendMessageOnAllLinks(message);
    qDebug() << "SENT" << n;
    if (n == mission_seq.size()-1) { qDebug() << "SENT MISSION"; return; }
}

void PixhawkManager::process_mission_status(mavlink_mission_ack_t mission_ack){
    if (mission_ack.type ==  MAV_MISSION_ACCEPTED){
        qDebug() << "MISSION ACCEPTED";
        mission_seq = QList<std::array<double, 3>>{{}};
    }
}

/////////////////////////////////////////////////////////////////CONNECTION//////////////////////////////////////////////////////////////////
ConnectionStatus PixhawkManager::get_connection_status()
{ return connection_status; }

int PixhawkManager::disconnect(){
    connection_status = ConnectionStatus::none;
    return link.down();
}
