#include "minitrace.h"
#include <chrono>
#include <thread>
#include <vector>

#ifdef _WIN32
#include <windows.h>
#define usleep(x) Sleep(x / 1000)
#else
#include <unistd.h>
#endif

#ifdef CPU_TRACE 
    #define CPU_TRACE_START()    \
        mtr_init("cpu_trace.json");  \
        mtr_register_sigint_handler();
#else 
   #define CPU_TRACE_START();
#endif

#ifdef CPU_TRACE
   #define CPU_TRACE_SCOPE(func_name)   \
           MTR_SCOPE("core", func_name);
#else 
   #define CPU_TRACE_SCOPE(func_name);
#endif 

#ifdef CPU_TRACE 
   #define CPU_TRACE_END()    \
       mtr_flush();           \
       mtr_shutdown();
#else 
   #define CPU_TRACE_END();
#endif


void c() {
  MTR_SCOPE("c++", "3. c");
  std::this_thread::sleep_for(std::chrono::microseconds(100));
}

void b() {
  MTR_SCOPE("c++", "2. b");
  std::this_thread::sleep_for(std::chrono::microseconds(100));
}

void a() {
  MTR_SCOPE("c++", "1. a");
  std::this_thread::sleep_for(std::chrono::seconds(2));
  c();
}

int main() {
  int i;
  CPU_TRACE_START();

  b();

  std::vector<std::thread> threads;
  for (int i = 0; i < 5; ++i) {
    threads.push_back(std::thread(a));
  }
  for (auto &thread : threads) {
    thread.join();
  }


  CPU_TRACE_END();
  return 0;
}
