// Qt
#include <QDebug>
#include <QtMath>

// Internal
#include "mavlink_communicator.h"
#include "message_handler.h"

using namespace domain;

MessageHandler::MessageHandler(MavLinkCommunicator* communicator):
    AbstractHandler(communicator) {}

mavlink_heartbeat_t MessageHandler::get_heartbeat()
{ return heartbeat; }

mavlink_global_position_int_t MessageHandler::get_global_position_int()
{ return global_position_int; }

mavlink_attitude_t MessageHandler::get_attitude()
{ return attitude; }

mavlink_scaled_imu_t MessageHandler::get_scaled_imu()
{ return scaled_imu; }

mavlink_param_value_t MessageHandler::get_param_value()
{ return param_value; }

void MessageHandler::process_message(const mavlink_message_t& message)
{
    if (message.sysid == 0) { return; }

    if (message.msgid == MAVLINK_MSG_ID_HEARTBEAT) {
        mavlink_msg_heartbeat_decode(&message, &heartbeat);
        if (DEBUG) { log(); }
    }

    if (message.msgid == MAVLINK_MSG_ID_GLOBAL_POSITION_INT){
        mavlink_msg_global_position_int_decode (&message, &global_position_int);
    }

    if (message.msgid == MAVLINK_MSG_ID_ATTITUDE){
        mavlink_msg_attitude_decode(&message, &attitude);
    }

    if (message.msgid == MAVLINK_MSG_ID_SCALED_IMU){
        mavlink_msg_scaled_imu_decode (&message, &scaled_imu);
    }

    if (message.msgid == MAVLINK_MSG_ID_PARAM_VALUE){
        mavlink_msg_param_value_decode(&message, &param_value);
        if (DEBUG){
            qDebug() << "param:" << param_value.param_index << " = " << param_value.param_value;
        }
        emit param_received(param_value);
    }

    if (message.msgid != MAVLINK_MSG_ID_COMMAND_ACK ||
        message.sysid == 0) {return;}

    mavlink_command_ack_t command_ack;
    mavlink_msg_command_ack_decode(&message, &command_ack);

    if (command_ack.result == MAV_RESULT_ACCEPTED)
        qDebug() << "seting frequency for command" << command_ack.command << "accepted";
    else
        qDebug() << "seting frequency for command" << command_ack.command << "failed with MAV_RESULT =" << command_ack.result;
}

void MessageHandler::log(){
    if (DEBUG){
            qDebug() << "xacc:" << scaled_imu.xacc
                     << "yacc:" << scaled_imu.yacc
                     << "zacc:" << scaled_imu.zacc;
            qDebug() << "xacc:" << scaled_imu.xgyro
                     << "yacc:" << scaled_imu.ygyro
                     << "zacc:" << scaled_imu.zgyro;
            qDebug() << "xacc:" << scaled_imu.xmag
                     << "yacc:" << scaled_imu.ymag
                     << "zacc:" << scaled_imu.zmag;

            qDebug() << "pitch:" << qRadiansToDegrees(attitude.pitch)
                     << "roll:" << qRadiansToDegrees(attitude.roll)
                     << "yaw:" << qRadiansToDegrees(attitude.yaw);

            qDebug() << "lat:" << global_position_int.lat/pow(10, 7)
                     << "lon:" << global_position_int.lon/pow(10, 7);

            qDebug() << "status:" << heartbeat.system_status << "type:" << heartbeat.type << "\n";
        }
}
