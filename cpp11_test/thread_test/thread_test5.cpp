//原子类型atomic，一般存数字，不需要mutex保护
#include <atomic>
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

atomic<int> num;
// int num;结果不对

int main() {
  auto func1 = []() {
    for (int i = 0; i < 100000; i++) {
      num += 1;
      // this_thread::sleep_for(chrono::seconds(1));
    }
  };
  auto func2 = []() {
    for (int i = 0; i < 100000; i++) {
      num += 1;
      // this_thread::sleep_for(chrono::seconds(1));
    }
  };
  thread t1(func1);
  thread t2(func2);

  //会看到两个线程抢锁
  t1.join();
  t2.join();

  cout << "final: " << num << endl;
  return 0;
}
