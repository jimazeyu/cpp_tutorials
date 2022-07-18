//使用线程锁来防止没有unlock，RAII思想
#include <chrono>
#include <iostream>
#include <mutex>
#include <thread>
using namespace std;

// lock_guard是unique_lock轻量版，不能手动释放
// unique_lock可以手动释放，一般配合条件变量（conditional variable）使用
mutex mtx;
int num;

int main() {
  auto func1 = []() {
    for (int i = 0; i < 10000; i++) {
      lock_guard<mutex> lck(mtx);
      num += 1;
      cout << "func1: " << num << endl;
      // this_thread::sleep_for(chrono::seconds(1));
    }
  };
  auto func2 = []() {
    for (int i = 0; i < 10000; i++) {
      lock_guard<mutex> lck(mtx);
      num += 1;
      cout << "func2: " << num << endl;
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
