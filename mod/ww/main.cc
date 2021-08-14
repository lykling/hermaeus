#include <chrono>
#include <cstdlib>
#include <memory>
#include <string>
#include <thread>

#include "core/dock/dock.h"
#include "mod/hello/proto/hello.pb.h"

int main(int argc, char** argv) {
  (void)argc;
  (void)argv;
  hermaeus::core::Dock dock("ww", "hermaeus");
  std::string topic = "/hermaeus/hello";
  auto writer = dock.CreateWriter<hermaeus::mod::hello::Hello>(topic);
  for (int i = 0; true; ++i) {
    hermaeus::mod::hello::Hello msg;
    msg.set_index(i);
    msg.set_name("hello");
    auto ret = writer->Write(msg);
    std::cout << "publish message[" << msg.index() << "]: " << msg.name()
              << " with ret: " << ret << std::endl;
    std::this_thread::sleep_for(std::chrono::seconds(1));
  }
  return EXIT_SUCCESS;
}
