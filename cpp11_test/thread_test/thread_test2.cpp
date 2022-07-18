//编写ThreadGuard类，用于管理线程，防止线程没有join或detach
#include <chrono>
#include <iostream>
#include <thread>

using namespace std;

class ThreadGuard {
public:
  enum class ThreadType { JOIN, DETACH };
  // thread使用右值引用，可以直接传递thread对象，不需要传递thread&
  ThreadGuard(thread &&t, ThreadType type) : t_(move(t)), type_(type) {}
  ~ThreadGuard() {
    if (t_.joinable()) {
      if (type_ == ThreadType::JOIN) {
        t_.join();
      } else {
        t_.detach();
      }
    }
  }
  //手动调用
  void start() {
    if (t_.joinable()) {
      if (type_ == ThreadType::JOIN) {
        t_.join();
      } else {
        t_.detach();
      }
    }
  }

private:
  thread t_;
  ThreadType type_;
};

int main() {
  auto func1 = []() {
    for (int i = 0; i < 5; i++) {
      cout << "func1: " << i << endl;
      this_thread::sleep_for(chrono::seconds(1));
    }
  };
  auto func2 = []() {
    for (int i = 0; i < 2; i++) {
      cout << "func2: " << i << endl;
      this_thread::sleep_for(chrono::seconds(2));
    }
  };
  thread rubbish_t1(func1);
  //下面使用move将rubbish_t转移给t0，rubbish_t失效
  ThreadGuard t1(move(rubbish_t1), ThreadGuard::ThreadType::JOIN);
  ThreadGuard t2(thread(func2), ThreadGuard::ThreadType::JOIN);

  t1.start();
  t2.start();

  return 0;
}