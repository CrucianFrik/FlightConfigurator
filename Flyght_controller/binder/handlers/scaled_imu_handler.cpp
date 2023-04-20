// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"
#include "scaled_imu_handler.h"

using namespace domain;

ScaledImuHandler::ScaledImuHandler(MavLinkCommunicator* communicator):
    AbstractHandler(communicator) {
    scaled_imu.xacc = -1;
    scaled_imu.yacc = -1;
    scaled_imu.zacc = -1;
}

mavlink_scaled_imu_t const& ScaledImuHandler::getData(){ return scaled_imu; }

void ScaledImuHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_SCALED_IMU){
	return;}

    c++;
    mavlink_msg_scaled_imu_decode (&message, &scaled_imu);
    if (c%2 && DEBUG){
    qDebug() << "xacc:" << scaled_imu.xacc
             << "yacc:" << scaled_imu.yacc
             << "zacc:" << scaled_imu.zacc;
    qDebug() << "xacc:" << scaled_imu.xgyro
             << "yacc:" << scaled_imu.ygyro
             << "zacc:" << scaled_imu.zgyro;
    qDebug() << "xacc:" << scaled_imu.xmag
             << "yacc:" << scaled_imu.ymag
             << "zacc:" << scaled_imu.zmag;
    }

}
