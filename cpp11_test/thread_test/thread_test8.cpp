//使用async来实现异步
//关于future之类的还没搞清楚，以后再补充
#include <chrono>
#include <functional>
#include <future>
#include <iostream>
#include <thread>

using namespace std;

int func(int in) {
  this_thread::sleep_for(chrono::seconds(1));
  return in + 1;
}

int main() {
  auto res = std::async(func, 5);
  cout << res.get() << endl; // 阻塞直到函数返回
  return 0;
}