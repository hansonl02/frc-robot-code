#include "third_party/aos/common/libc/aos_strsignal.h"

#include <signal.h>

#include "third_party/aos/common/check.h"
const char *aos_strsignal(int signal) {
  static thread_local char buffer[512];

  if (signal >= SIGRTMIN && signal <= SIGRTMAX) {
    CHECK(snprintf(buffer, sizeof(buffer), "Real-time signal %d",
                   signal - SIGRTMIN) > 0);
    return buffer;
  }

  if (signal > 0 && signal < NSIG && sys_siglist[signal] != nullptr) {
    return sys_siglist[signal];
  }

  CHECK(snprintf(buffer, sizeof(buffer), "Unknown signal %d", signal) > 0);
  return buffer;
}
