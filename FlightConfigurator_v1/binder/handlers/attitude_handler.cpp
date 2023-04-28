// Qt
#include <QtMath>
#include <QDebug>

// Internal
#include "attitude_handler.h"

using namespace domain;

AttitudeHandler::AttitudeHandler(MavLinkCommunicator* communicator):
    AbstractHandler(communicator)
{
    this->startTimer(1000); // 1 Hz
}

void AttitudeHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_ATTITUDE ||
        message.sysid == 0) {return;}

    c++;
    mavlink_msg_attitude_decode(&message, &attitude);

    if (c%2 && DEBUG){
        qDebug() << "pitch" << qRadiansToDegrees(attitude.pitch)
                 << "roll" << qRadiansToDegrees(attitude.roll)
                 << "yaw" << qRadiansToDegrees(attitude.yaw);
    }
}

mavlink_attitude_t const& AttitudeHandler::getData(){ return attitude; }
