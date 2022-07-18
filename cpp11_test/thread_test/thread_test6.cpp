//保证某个函数在多线程中只调用一次，使用once_flag来保证
#include <chrono>
#include <iostream>
#include <thread>
#include <mutex>
using namespace std;

std::once_flag onceflag;

void CallOnce() {
  std::call_once(onceflag, []() { cout << "call once" << endl; });
}

int main() {
  std::thread threads[5];
  for (int i = 0; i < 5; ++i) {
    threads[i] = std::thread(CallOnce);
  }
  for (auto &th : threads) {
    th.join();
  }
  return 0;
}
