// Internal
#include "pixhawk_manager.h"

PixhawkManager::PixhawkManager(const QString& path, qint32 speed) : message_hendler(&communicator),
                                            link (path, speed)
{
    QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
                     &message_hendler, &domain::MessageHandler::process_message);
    QObject::connect(&message_hendler, &domain::MessageHandler::param_received,
                     this, &PixhawkManager::request_params_slot);

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

void PixhawkManager::log_received_msgs(bool print_once){
    communicator.logReceivedMsgs(print_once);
}

void PixhawkManager::update_param_list(const mavlink_param_value_t &param, float new_value){
    add_to_param_list(param);
    param_list[param.param_index].param_value = new_value;
}

void PixhawkManager::add_to_param_list(const mavlink_param_value_t &param){
    ParamInfo pi {"", param.param_type, param.param_value};
    memcpy(pi.param_id, param.param_id, sizeof(param.param_id));

    param_list.insert({param.param_index, pi});
    param_list[param.param_index] = pi;
}

void PixhawkManager::request_params_slot(const mavlink_param_value_t &param){
    add_to_param_list(param);
    if (param.param_index == param.param_count-1) { all_params_received_flag = 1; }
    qDebug() << param_list[param.param_index].param_id << "(" << param.param_index << ")" << ":" << param.param_value;
}
