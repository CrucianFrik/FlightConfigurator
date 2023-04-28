#include "gcs_communicator_factory.h"

// MAVLink
#include <mavlink.h>

// Internal
#include "mavlink_communicator.h"

#include "message_handler.h"

using namespace domain;

GcsCommunicatorFactory::GcsCommunicatorFactory()
{}

MavLinkCommunicator* GcsCommunicatorFactory::create()
{
    MavLinkCommunicator* communicator = new MavLinkCommunicator(255, 0);

    new domain::MessageHandler(communicator);

    return communicator;
}
