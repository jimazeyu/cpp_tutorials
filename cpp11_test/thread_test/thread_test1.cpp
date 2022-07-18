// thread基本用法
#include <chrono>
#include <thread>
#include <iostream>
using namespace std;

int main() {
  using seconds = chrono::duration<double, std::ratio<1>>;
  auto func1 = []() {
    for (int i = 0; i < 10; i++) {
      cout << "func1: " << i << endl;
      this_thread::sleep_for(seconds(1));
    }
  };
  auto func2 = []() {
    for (int i = 0; i < 2; i++) {
      cout << "func2: " << i << endl;
      this_thread::sleep_for(seconds(2));
    }
  };

  thread t1(func1);
  thread t2(func2);
  // join和detach的区别
  // join：等待线程结束，主线程结束后，线程也会结束
  // detach：线程结束后，不会等待线程结束，主线程结束后，线程也不会结束
  t1.join();
  cout << "main thread end" << endl; //会在最后才打印
  t2.join();
  //如果重复join，会报错
  if (t1.joinable()) {
    t1.join();
  }

  return 0;
}