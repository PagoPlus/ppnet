#include <PPNet.h>

#ifndef PIO_UNIT_TESTING
void setup() {
}
void loop () {
}
#else
#include <gtest/gtest.h>
void setup() {
  ::testing::InitGoogleTest();
  exit(RUN_ALL_TESTS());
}
void loop() {}

#ifndef ARDUINO
#include <thread>
int main() {
  setup();

  for (;;) {
    loop();
    std::this_thread::yield();
  }
}
#endif

#endif // PIO_UNIT_TESTING