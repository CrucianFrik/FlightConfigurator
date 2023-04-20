// Internal
#include "pixhawk_manager.h"

PixhawkManager::PixhawkManager(const QString& path, qint32 speed) : attitudeHandler(&communicator),
                                            heartbeatHandler(&communicator),
                                            scaledImuHandler (&communicator),
                                            link (path, speed)
{
    try{
	QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
	                 &heartbeatHandler, &domain::HeartbeatHandler::processMessage);
	QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
	                 &attitudeHandler, &domain::AttitudeHandler::processMessage);
	QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
	                 &scaledImuHandler, &domain::ScaledImuHandler::processMessage);
    QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
                     this, &PixhawkManager::setMsgFrequencySlot);

	communicator.addLink(&link, MAVLINK_COMM_3);
	link.up();
    }
    catch(const std::exception& e){
	qDebug() << "binding failed";
	qDebug() << e.what();
    }
}
mavlink_heartbeat_t const& PixhawkManager::getHeartbeat(){ return heartbeatHandler.getData(); }
mavlink_attitude_t const& PixhawkManager::getAttitude() { return attitudeHandler.getData(); }
mavlink_scaled_imu_t const& PixhawkManager::getScaledImu() { return scaledImuHandler.getData(); }

void PixhawkManager::setMsgFrequency(uint8_t msg_id, int8_t frequency) {
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

void PixhawkManager::setMsgFrequencySlot(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_COMMAND_ACK ||
        message.sysid == 0) {return;}

    mavlink_command_ack_t command_ack;
    mavlink_msg_command_ack_decode(&message, &command_ack);

    if (command_ack.result == MAV_RESULT_ACCEPTED)
        qDebug() << "seting frequency for command" << command_ack.command << "accepted";
    else
        qDebug() << "seting frequency for command" << command_ack.command << "failed with MAV_RESULT =" << command_ack.result;
}

void PixhawkManager::logReceivedMsgs(bool print_once){
    communicator.logReceivedMsgs(print_once);
}
