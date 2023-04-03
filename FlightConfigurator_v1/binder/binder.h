// Internal
#include "udp_link.h"
#include "serial_link.h"

#include "gcs_communicator_factory.h"
#include "mavlink_communicator.h"
#include "heartbeat_handler.h"
#include "attitude_handler.h"

#include <QDebug>
#include <mavlink.h>

class Binder{
    domain::MavLinkCommunicator communicator;
    domain::HeartbeatHandler heartbeatHandler;
    domain::AttitudeHandler attitudeHandler;
    domain::SerialLink link;

public:
    Binder(const QString& path, qint32 speed) : attitudeHandler(&communicator),
                heartbeatHandler(0, &communicator), link (path, speed){
        try{
            QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
                             &heartbeatHandler, &domain::HeartbeatHandler::processMessage);
            QObject::connect(&communicator, &domain::MavLinkCommunicator::messageReceived,
                             &attitudeHandler, &domain::AttitudeHandler::processMessage);

            communicator.addLink(&link, MAVLINK_COMM_3);
            link.up();
        }
        catch(const std::exception& e){
            qDebug() << "binding failed";
            qDebug() << e.what();
        }
    }
    mavlink_heartbeat_t const& getHeartbeat(){ return heartbeatHandler.getData(); }
    mavlink_attitude_t const& getAttitude() { return attitudeHandler.getData(); }

signals:
    void MySig();
};
