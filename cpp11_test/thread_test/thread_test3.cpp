// mutex线程锁，可以保证线程安全，但是不能保证原子性，因为mutex是线程锁，不是原子锁
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

//全局线程锁
mutex mtx;
int num;

int main() {
  auto func1 = []() {
    for (int i = 0; i < 10000; i++) {
      mtx.lock();
      num += 1;
      cout << "func1: " << num << endl;
      // this_thread::sleep_for(chrono::seconds(1));
      mtx.unlock();
    }
  };
  auto func2 = []() {
    for (int i = 0; i < 10000; i++) {
      mtx.lock();
      num += 1;
      cout << "func2: " << num << endl;
      // this_thread::sleep_for(chrono::seconds(1));
      mtx.unlock();
    }
  };
  thread t1(func1);
  thread t2(func2);

  //会看到两个线程抢锁
  t1.join();
  t2.join();

  cout << "final" << num << endl;
  return 0;
}
