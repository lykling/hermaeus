#include "participant.h"

#include <fastrtps/Domain.h>
#include <fastrtps/participant/Participant.h>

namespace hermaeus {
namespace core {

Participant::Participant(const std::string& name)
    : participant_(nullptr), name_(name) {
  Init();
}

Participant::~Participant() {}

bool Participant::Init() {
  eprosima::fastrtps::ParticipantAttributes pparam;
  pparam.rtps.builtin.discovery_config.discoveryProtocol =
      eprosima::fastrtps::rtps::DiscoveryProtocol_t::SIMPLE;
  pparam.rtps.builtin.discovery_config.use_SIMPLE_EndpointDiscoveryProtocol =
      true;
  pparam.rtps.builtin.discovery_config.m_simpleEDP
      .use_PublicationReaderANDSubscriptionWriter = true;
  pparam.rtps.builtin.discovery_config.m_simpleEDP
      .use_PublicationWriterANDSubscriptionReader = true;
  pparam.rtps.builtin.discovery_config.leaseDuration =
      eprosima::fastrtps::c_TimeInfinite;
  pparam.rtps.setName(name_.c_str());
  participant_ = eprosima::fastrtps::Domain::createParticipant(pparam);
  if (participant_ == nullptr) {
    return false;
  }
  eprosima::fastrtps::Domain::registerType(participant_, &type_);
  return true;
}

eprosima::fastrtps::Participant* Participant::RtpsParticipant() {
  return participant_;
}

}  // namespace core
}  // namespace hermaeus
