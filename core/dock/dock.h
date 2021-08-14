#pragma once

#include <map>
#include <memory>
#include <mutex>
#include <string>

#include "core/dock/participant.h"
#include "core/dock/reader.h"
#include "core/dock/reader_base.h"
#include "core/dock/writer.h"
#include "core/dock/writer_base.h"

namespace hermaeus {
namespace core {

class Dock {
 public:
  Dock(const std::string& dock_name, const std::string& name_space)
      : dock_name_(dock_name), name_space_(name_space), participant_(nullptr) {
    Init();
  };
  virtual ~Dock(){};

  bool Init() {
    participant_ = std::make_shared<Participant>(dock_name_);
    return true;
  };

  template <typename MessageT>
  auto CreateWriter(const std::string& channel_name)
      -> std::shared_ptr<Writer<MessageT>> {
    std::shared_ptr<Writer<MessageT>> writer_ptr = nullptr;
    writer_ptr = std::make_shared<Writer<MessageT>>(participant_, channel_name);
    return writer_ptr;
  };

  template <typename MessageT>
  auto CreateReader(const std::string& channel_name,
                    std::function<void(const std::shared_ptr<MessageT>&)>
                        reader_func = nullptr)
      -> std::shared_ptr<Reader<MessageT>> {
    std::shared_ptr<Reader<MessageT>> reader_ptr = nullptr;
    reader_ptr = std::make_shared<Reader<MessageT>>(participant_, channel_name,
                                                    reader_func);
    return reader_ptr;
  };

 private:
  std::string dock_name_;
  std::string name_space_;
  std::shared_ptr<Participant> participant_;
};

}  // namespace core
}  // namespace hermaeus
