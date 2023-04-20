// Qt
#include <QDebug>

// Internal
#include "mavlink_communicator.h"
#include "global_position_int_handler.h"

using namespace domain;

GlobalPositionIntHandler::GlobalPositionIntHandler(MavLinkCommunicator* communicator):
    AbstractHandler(communicator) {}

mavlink_global_position_int_t const& GlobalPositionIntHandler::getData(){ return global_position_int; }

void GlobalPositionIntHandler::processMessage(const mavlink_message_t& message)
{
    if (message.msgid != MAVLINK_MSG_ID_GLOBAL_POSITION_INT){
	return;}

    c++;
    mavlink_msg_global_position_int_decode (&message, &global_position_int);
    if (c%2 && DEBUG){
    qDebug() << "Latitude, expressed as degrees:" << global_position_int.lat/pow(10, 7)
	         << "Longitude, expressed as degrees:" << global_position_int.lon/pow(10, 7);
    }

}
