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
    link.up();
}

mavlink_heartbeat_t PixhawkManager::get_heartbeat()
{ return message_hendler.get_heartbeat(); }

mavlink_attitude_t PixhawkManager::get_attitude()
{ return message_hendler.get_attitude(); }

mavlink_scaled_imu_t PixhawkManager::get_scaled_imu()
{ return message_hendler.get_scaled_imu(); }

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
    mavlink_msg_command_long_encode_chan(communicator.systemId(),
                                         communicator.componentId(),
                                         MAVLINK_COMM_3,
                                         &message, &command_long);
    communicator.sendMessageOnAllLinks(message);
}

void PixhawkManager::request_all_params() {
    mavlink_message_t message;
    mavlink_param_request_list_t param_request_list;
    param_request_list.target_system = 1;
    param_request_list.target_component = 1;
    mavlink_msg_param_request_list_encode_chan(communicator.systemId(),
                                         communicator.componentId(),
                                         MAVLINK_COMM_3,
                                         &message, &param_request_list);
    communicator.sendMessageOnAllLinks(message);
}

bool PixhawkManager::set_param(uint16_t param_inndex, float new_value){
    qDebug() << "+";
    if (!all_params_received_flag) { qDebug() << "the full list of parameters has not been received yet, updating is not possible"; return 0;}
    mavlink_message_t message;
    mavlink_param_set_t param_set;
    param_set.target_system = 1;
    param_set.target_component = 1;
    qDebug() << "PARAMETR COUNT" << param_list.count(param_inndex);
    if (param_list.count(param_inndex)){
        if (1) { qDebug() << "WRITED PARAMETR" << param_list[param_inndex].param_id; }
        memcpy(param_set.param_id, param_list[param_inndex].param_id, 16);
        param_set.param_value = new_value;
        param_set.param_type = param_list[param_inndex].param_type;
        mavlink_msg_param_set_encode_chan(communicator.systemId(),
                                             communicator.componentId(),
                                             MAVLINK_COMM_3,
                                             &message, &param_set);
        communicator.sendMessageOnAllLinks(message);
    }
    return 1;
}

void PixhawkManager::update_param_in_param_list(uint8_t index, float new_value){
    //log: "значение параметра не обновлено"
    if (param_list.find(index) == param_list.end()){
        //FIXME
        qDebug() << "error: no such file in param_list";
        return;
    }
    updated_param_list_params.push_back(index);
    param_list[index].param_value = new_value;
}

void PixhawkManager::add_param_to_param_list(const mavlink_param_value_t &param){
    ParamInfo pi {"", param.param_type, param.param_value};
    memcpy(pi.param_id, param.param_id, sizeof(param.param_id));

    param_list.insert({param.param_index, pi});
    param_list[param.param_index] = pi;
}

void PixhawkManager::param_received(const mavlink_param_value_t &param){
    qDebug() << "pr";
    add_param_to_param_list(param);
    if (param.param_index == param.param_count-1) {
        all_params_received_flag = 1;
        emit all_params_received();
    }
    qDebug() << param_list[param.param_index].param_id << "(" << param.param_index << ")" << ":" << param.param_value;
}

const std::map<uint16_t, ParamInfo>& PixhawkManager::get_parametr_list(){
    return param_list;
}

bool PixhawkManager::is_all_params_received(){
    return all_params_received_flag;
}
