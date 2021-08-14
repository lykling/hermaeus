#pragma once

#include <fastrtps/Domain.h>
#include <fastrtps/attributes/SubscriberAttributes.h>
#include <fastrtps/participant/Participant.h>
#include <fastrtps/subscriber/SampleInfo.h>
#include <fastrtps/subscriber/Subscriber.h>
#include <fastrtps/subscriber/SubscriberListener.h>

#include <functional>
#include <memory>

#include "core/dock/carrier_message.h"
#include "core/dock/participant.h"
#include "core/dock/reader_base.h"

namespace hermaeus {
namespace core {

template <typename MessageT>
class SubscriberListener : public eprosima::fastrtps::SubscriberListener {
 public:
  SubscriberListener(
      std::function<void(const std::shared_ptr<MessageT>&)> callback)
      : matched_(0), samples_(0), callback_(callback){};
  ~SubscriberListener(){};

  void onSubscriptionMatched(eprosima::fastrtps::Subscriber* sub,
                             eprosima::fastrtps::rtps::MatchingInfo& info) {
    (void)sub;
    if (info.status == eprosima::fastrtps::rtps::MATCHED_MATCHING) {
      matched_++;
    } else {
      matched_--;
    }
  }
  void onNewDataMessage(eprosima::fastrtps::Subscriber* sub) {
    if (sub->takeNextData(reinterpret_cast<void*>(&msg_), &info_)) {
      if (info_.sampleKind == eprosima::fastrtps::rtps::ALIVE) {
        this->samples_++;
      }
      const std::string buffer(msg_.data());
      auto msg = std::make_shared<MessageT>();
      msg->ParseFromString(buffer);
      callback_(msg);
    }
  }

 private:
  CarrierMessage msg_;
  eprosima::fastrtps::SampleInfo_t info_;
  int matched_;
  uint32_t samples_;
  std::function<void(const std::shared_ptr<MessageT>&)> callback_;
};

template <typename M0>
using CallbackFunc = std::function<void(const std::shared_ptr<M0>&)>;

template <typename MessageT>
class Reader : public ReaderBase {
 public:
  Reader(const std::shared_ptr<Participant>& participant,
         const std::string& channel_name,
         const std::function<void(const std::shared_ptr<MessageT>&)> callback)
      : listener_(callback),
        channel_name_(channel_name),
        participant_(participant),
        callback_(callback),
        subscriber_(nullptr) {
    Init();
  }
  virtual ~Reader(){};
  bool Init() override {
    eprosima::fastrtps::SubscriberAttributes rparam;
    rparam.topic.topicKind = eprosima::fastrtps::rtps::NO_KEY;
    rparam.topic.topicDataType = "CarrierMessage";
    rparam.topic.topicName = channel_name_;
    rparam.topic.historyQos.kind = eprosima::fastrtps::KEEP_LAST_HISTORY_QOS;
    rparam.topic.historyQos.depth = 30;
    rparam.topic.resourceLimitsQos.max_samples = 50;
    rparam.topic.resourceLimitsQos.allocated_samples = 20;
    rparam.qos.m_reliability.kind =
        eprosima::fastrtps::RELIABLE_RELIABILITY_QOS;
    rparam.qos.m_durability.kind =
        eprosima::fastrtps::TRANSIENT_LOCAL_DURABILITY_QOS;
    subscriber_ = eprosima::fastrtps::Domain::createSubscriber(
        participant_->RtpsParticipant(), rparam, &listener_);
    if (subscriber_ == nullptr) {
      return false;
    }
    return true;
  };

 private:
  SubscriberListener<MessageT> listener_;
  std::string channel_name_;
  std::shared_ptr<Participant> participant_;
  std::function<void(const std::shared_ptr<MessageT>&)> callback_;
  eprosima::fastrtps::Subscriber* subscriber_;
};
}  // namespace core
}  // namespace hermaeus
