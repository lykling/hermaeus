#pragma once

#include <fastrtps/attributes/ParticipantAttributes.h>
#include <fastrtps/participant/Participant.h>

#include "core/dock/carrier_message_pub_sub_types.h"

namespace hermaeus {
namespace core {

class Participant {
 public:
  Participant(const std::string& name);
  virtual ~Participant();
  bool Init();
  eprosima::fastrtps::Participant* RtpsParticipant();

 private:
  eprosima::fastrtps::Participant* participant_;
  const std::string name_;
  CarrierMessagePubSubType type_;
};

}  // namespace core
}  // namespace hermaeus
