#pragma once

#include <fastrtps/Domain.h>
#include <fastrtps/attributes/PublisherAttributes.h>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/publisher/Publisher.h>
#include <fastrtps/publisher/PublisherListener.h>

#include <memory>

#include "core/dock/carrier_message.h"
#include "core/dock/participant.h"
#include "core/dock/writer_base.h"

namespace hermaeus {
namespace core {
class PublisherListener : public eprosima::fastrtps::PublisherListener {
 public:
  PublisherListener() : matched_(0){};
  ~PublisherListener(){};

  void onPublicationMatched(eprosima::fastrtps::Publisher* pub,
                            eprosima::fastrtps::rtps::MatchingInfo& info) {
    if (info.status == eprosima::fastrtps::rtps::MATCHED_MATCHING) {
      matched_++;
    } else {
      matched_--;
    }
  };

 private:
  int matched_;
};

template <typename MessageT>
class Writer : public WriterBase {
 public:
  Writer(const std::shared_ptr<Participant>& participant,
         const std::string& channel_name)
      : channel_name_(channel_name),
        participant_(participant),
        publisher_(nullptr) {
    Init();
  }
  virtual ~Writer(){};
  bool Init() override {
    eprosima::fastrtps::PublisherAttributes wparam;
    wparam.topic.topicKind = eprosima::fastrtps::rtps::NO_KEY;
    wparam.topic.topicDataType = "CarrierMessage";
    wparam.topic.topicName = channel_name_.c_str();
    wparam.topic.historyQos.kind = eprosima::fastrtps::KEEP_LAST_HISTORY_QOS;
    wparam.topic.historyQos.depth = 30;
    wparam.topic.resourceLimitsQos.max_samples = 50;
    wparam.topic.resourceLimitsQos.allocated_samples = 20;
    wparam.times.heartbeatPeriod.seconds = 2;
    wparam.times.heartbeatPeriod.nanosec = 200 * 1000 * 1000;
    wparam.qos.m_reliability.kind =
        eprosima::fastrtps::RELIABLE_RELIABILITY_QOS;
    publisher_ = eprosima::fastrtps::Domain::createPublisher(
        participant_->RtpsParticipant(), wparam, &listener_);
    if (publisher_ == nullptr) {
      return false;
    }
    return true;
  };
  virtual bool Write(const MessageT& msg) {
    std::string buffer;
    CarrierMessage cm;
    msg.SerializeToString(&cm.data());
    return publisher_->write((void*)&cm);
  };
  virtual bool Write(const std::shared_ptr<MessageT>& msg_ptr) {
    std::string buffer;
    CarrierMessage cm;
    msg_ptr->SerializeToString(&cm.data());
    return publisher_->write((void*)&cm);
  };

 private:
  PublisherListener listener_;
  std::string channel_name_;
  std::shared_ptr<Participant> participant_;
  eprosima::fastrtps::Publisher* publisher_;
};

}  // namespace core
}  // namespace hermaeus
