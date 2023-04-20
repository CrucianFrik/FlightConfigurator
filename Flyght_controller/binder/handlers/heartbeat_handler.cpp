// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"
#include "heartbeat_handler.h"

using namespace domain;

HeartbeatHandler::HeartbeatHandler(MavLinkCommunicator* communicator):
    AbstractHandler(communicator) {}

mavlink_heartbeat_t const& HeartbeatHandler::getData(){ return heartbeat; }

void HeartbeatHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid == MAVLINK_MSG_ID_COMMAND_ACK){

    mavlink_command_ack_t command_ack;
    mavlink_msg_command_ack_decode(&message, &command_ack);

    if (command_ack.result == MAV_RESULT_ACCEPTED)
        qDebug() << "seting frequency for command" << command_ack.command << "accepted";
    else
        qDebug() << "seting frequency for command" << command_ack.command << "failed with MAV_RESULT =" << command_ack.result;
    }

    c++;
    mavlink_msg_heartbeat_decode(&message, &heartbeat);
    if (c%2 && DEBUG){
        qDebug() << "Heartbeat received, system type:" << heartbeat.type
                 << "autopilot :" << heartbeat.autopilot;
    }

}
