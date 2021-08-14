#include <chrono>
#include <cstdlib>
#include <functional>
#include <thread>

#include "core/dock/dock.h"
#include "mod/hello/proto/hello.pb.h"

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  hermaeus::core::Dock dock("rr", "hermaeus");
  std::string topic = "/hermaeus/hello";
  auto reader = dock.CreateReader<hermaeus::mod::hello::Hello>(
      topic, [](const std::shared_ptr<hermaeus::mod::hello::Hello>& msg) {
        std::cout << "subscribe message[" << msg->index() << "]:" << msg->name()
                  << std::endl;
      });
  for (; true;) {
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return EXIT_SUCCESS;
}
