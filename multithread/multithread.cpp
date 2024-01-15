#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

void print_int(int a) { std::cout << a << std::endl; };

class obj_print_int {
  void operator()(int a) { std::cout << a << std::endl; }
};

void test_create_thread() {
  int a = 1;
  // use lamda
  std::thread paral_print_int_1([](int v) { std::cout << v << std::endl; }, a);
}

/**
 * @brief All global and static variables that are initialised at compile time
 * can be accessed by threads. Since the threads should know the addresses for
 * them.
 * All parameters passed to a function when starting a thread are passed by
 * value, even if you defined in the function to pass by reference!
 * You need to explicitly wrap the arguments in std::ref() to pass by reference.
 *
 */
void method() {
  static int var = 0;
  thread_local int var_local = 0;
  for (int i = 0; i < 10; ++i) {
    var++;
    var_local++;
    // std::cout << "var: " << var << std::endl;
    std::cout << "var_local: " << var_local << std::endl;
  }
}

void test_share_data() {
  std::thread para_method_0(method);
  std::thread para_method_1(method);
}

void test_sleep_time() {
  // sleep for some time
  std::this_thread::sleep_for(std::chrono::seconds(5));
  std::chrono::system_clock::time_point time_point =
      std::chrono::system_clock::now() + std::chrono::seconds(10);

  std::this_thread::sleep_until(time_point);
}

// So there are several ways to prevent race conditions. An std::atomic is just
// one way.
void test_race_conditions() {
  int b = 10;
  std::mutex my_mutex;
  std::thread add_1(
      [&](int &a) {
        std::lock_guard<std::mutex> guard(my_mutex);
        a += 3;
        if (a == 13)
          std::cout << "add 1 success and get the exp result!!!\n";
        else
          std::cout << "some thing is wrong...\n";
      },
      std::ref(b));
  std::thread test_add(
      [&](int &a) {
        std::lock_guard<std::mutex> guard(my_mutex);
        a -= 3;
      },
      std::ref(b));
  add_1.join();
  test_add.join();
  std::cout << "var b=" << b << std::endl;
}

typedef void (*callback_func)(int *);
class TestDeviceStatus {
public:
  TestDeviceStatus() {
    std::unique_lock<std::mutex> guard(my_mutex);
    my_status = 0;
  }
  virtual ~TestDeviceStatus() {}

private:
  std::mutex my_mutex;
  int my_status = 0;
  callback_func my_func = NULL;

public:
  void registration(void func(int *), int *out_status) {
    std::cout << "1.注册设备状态检查..." << std::endl;
    my_func = func;
    auto getstatus = []() -> int { return -1; };
    std::thread check_device_status(
        [&](int *out_status) {
          std::cout << "2.开启子线程循环检查设备状态中..." << std::endl;
          while (true) {
            std::this_thread::sleep_for(std::chrono::seconds(3));
            std::unique_lock<std::mutex> guard(my_mutex);
            *out_status = getstatus();
            if (*out_status != 0)
              my_func(out_status);
          };
        },
        out_status);
    check_device_status.detach();
  }
};

void test_device_status() {
  TestDeviceStatus test_device;
  int status = 0;

  auto func = [](int *status) -> void {
    std::cout << "检测到设备异常 status=" << *status << std::endl;
  };

  test_device.registration(func, &status);
  std::cout << "do some thing else\n";
  std::this_thread::sleep_for(std::chrono::seconds(10));
}

#include <future>
#include <vector>

void test_future() {
  auto initiazer = [](std::promise<std::vector<int>> *promObj) {
    std::vector<int> data;
    std::cout << "Inside Thread" << std::endl;
    for (int i = 0; i < 100; i++)
      data.push_back(i);
    promObj->set_value(data);
  };

  std::promise<std::vector<int>> promiseObj;
  std::future<std::vector<int>> futureObj = promiseObj.get_future();

  std::cout << "start future inner thread..." << std::endl;
  std::thread th(initiazer, &promiseObj);

  auto data = futureObj.get();
  std::cout << data.size() << std::endl;
  for (auto &d : data) {
    std::cout << d << std ::endl;
  }
  th.join();
}

int main() {
  auto n = std::thread::hardware_concurrency();
  std::cout << "thread hardware_concurrency: " << n << std::endl;
  std::cout << "this thread id: " << std::this_thread::get_id() << std::endl;
  test_device_status();
  return 0;
}
