// Internal
#include "pixhawk_manager.h"

PixhawkManager::PixhawkManager(const QString& path, qint32 speed) : message_hendler(&communicator),
                                            link (path, speed)
{
    QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
                     &message_hendler, &domain::MessageHandler::process_message);
    QObject::connect(&message_hendler, &domain::MessageHandler::param_received,
                     this, &PixhawkManager::param_received);

	communicator.addLink(&link, MAVLINK_COMM_3);
    int cs = link.up();
    if (cs == 0)
        connection_status = ConnectionStatus::successful;
    else {
        connection_status = ConnectionStatus::failed;
        return;
    }

    //out.open("params_list.txt");

    int FREQUENCY = 100000;
    set_msg_frequency(MAVLINK_MSG_ID_GLOBAL_POSITION_INT, FREQUENCY);
    set_msg_frequency(MAVLINK_MSG_ID_ATTITUDE, FREQUENCY);
    set_msg_frequency(MAVLINK_MSG_ID_SCALED_IMU, FREQUENCY);
}

void PixhawkManager::set_msg_frequency(uint8_t msg_id, int8_t frequency) {
    //msg_id - an int from 1 to 12920 (ex: 30 for ATTITUDE)
    //frequency - in "us" (-1 to stop sending)
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

void PixhawkManager::request_all_params() {
    mavlink_message_t message;
    mavlink_param_request_list_t param_request_list;
    param_request_list.target_system = 1;
    param_request_list.target_component = 1;
    mavlink_msg_param_request_list_encode_chan(communicator.systemId(), communicator.componentId(),
                        MAVLINK_COMM_3, &message, &param_request_list);
    communicator.sendMessageOnAllLinks(message);
    qDebug() << "params req sent ";
}

bool PixhawkManager::set_param(int param_index, float new_value){
    if (!all_params_received_flag) { qDebug() << "the full list of parameters has not been received yet, updating is not possible"; return 0;}
    mavlink_message_t message;
    mavlink_param_set_t param_set;
    param_set.target_system = 1;
    param_set.target_component = 1;
    if (params_list.count(param_index)){
        if (1) { qDebug() << "WRITED PARAMETR" << params_list[param_index].param_id; }
        memcpy(param_set.param_id, params_list[param_index].param_id, 16);
        param_set.param_value = new_value;
        param_set.param_type = params_list[param_index].param_type;
        mavlink_msg_param_set_encode_chan(communicator.systemId(), communicator.componentId(), MAVLINK_COMM_3, &message, &param_set);
        communicator.sendMessageOnAllLinks(message);
    }
    return 1;
}

void PixhawkManager::remember__new_param_value(int index, float new_value){
    qDebug() << "changed and remembered (start)" << index;
    if (params_list.find(index) == params_list.end()){
        //FIXME log: "значение параметра не обновлено"
        qDebug() << "error: no such file in params_list";
        return;
    }
    ParamInfo pi {"", params_list[index].param_type, new_value};
    memcpy(pi.param_id, params_list[index].param_id, sizeof(pi.param_id));
    updated_items_in_params_list[index] = pi;
    qDebug() << "changed and remembered" << index << pi.param_id << new_value;
}

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
///changed index 303
///changed and remembered 47 FBWB_CLIMB_RATE 10

void PixhawkManager::add_param_to_params_list(const mavlink_param_value_t &param){
    ParamInfo pi {"", param.param_type, param.param_value};
    memcpy(pi.param_id, param.param_id, sizeof(param.param_id));

    params_list.insert({param.param_index, pi});
    params_list[param.param_index] = pi;
}

void PixhawkManager::param_received(const mavlink_param_value_t &param){
    // FIXME -- STAT_RUNTIME ( 65535 ) : 0
    if (param.param_index > param.param_count) {
        qDebug() << "#" << param.param_id << "(" << param.param_index << ")" << ":" << param.param_value;
    }
    add_param_to_params_list(param);
    if (param.param_index == param.param_count-1) {
        message_hendler.log();
        all_params_received_flag = 1;
//        out.close();
        emit all_params_received();
    }
    qDebug() << params_list[param.param_index].param_id << "(" << param.param_index << ")" << ":" << param.param_value;
//    if (out.is_open())
//    {
//        out << params_list[param.param_index].param_id << std::endl;
//    }
}



float PixhawkManager::get_param_val(uint8_t index){
    if (params_list.find(index) != params_list.end()){
        return params_list[index].param_value;
    }
    return 0; //mb FIXME
}

const std::map<uint16_t, ParamInfo>& PixhawkManager::get_parametr_list()
{ return params_list; }

const std::map<uint16_t, ParamInfo>& PixhawkManager::get_updated_items_in_params_list()
{ return updated_items_in_params_list; }

bool PixhawkManager::is_all_params_received()
{ return all_params_received_flag; }

int PixhawkManager::get_connection_status()
{ return connection_status; }

mavlink_heartbeat_t PixhawkManager::get_heartbeat()
{ return message_hendler.get_heartbeat(); }

mavlink_attitude_t PixhawkManager::get_attitude()
{ return message_hendler.get_attitude(); }

mavlink_scaled_imu_t PixhawkManager::get_scaled_imu()
{ return message_hendler.get_scaled_imu(); }

mavlink_global_position_int_t PixhawkManager::get_global_position_int()
{ return message_hendler.get_global_position_int(); }
