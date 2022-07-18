// conditional_variable条件变量，可以用来实现线程间的同步
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <thread>

using namespace std;

atomic<int> num; //龙珠个数
mutex mtx;
condition_variable cv;
int main() {

  //找龙珠
  auto FindBall = [](int seconds) {
    //休眠seconds秒
    this_thread::sleep_for(chrono::seconds(seconds));
    //加锁，一定在休眠后，不然会轮流休眠
    lock_guard<mutex> lk(mtx);
    //找到龙珠
    num++;
    cout << "FindBall: " << num << endl;
    if (num >= 7)
      cv.notify_all();
  };

  //召唤神龙
  auto SummonDragon = [](int seconds) {
    unique_lock<mutex> lck(mtx);
    //记录开始寻找的时间
    auto start = chrono::system_clock::now();
    //如使用wait，则无限等待，直到找到龙珠，如使用wait_for，则等待seconds秒，如果seconds秒内没有找到龙珠，则认为是超时
    cv.wait_for(lck, chrono::seconds(seconds));
    //召唤神龙
    if (num >= 7) {
      //记录找到的时间
      auto end = chrono::system_clock::now();
      chrono::duration<double> diff = end - start;
      cout << "FindBall time: " << diff.count() << " seconds" << endl;
      cout << "SummonDragon!!!!!" << endl;
    } else {
      cout << "Failed!!!!!" << endl;
    }
  };

  //开始找龙珠
  thread finders[7];
  for (int i = 0; i < 7; i++) {
    finders[i] = thread(FindBall, i + 1);
  }

  //召唤神龙，10秒内找到龙珠则成功
  thread summoner = thread(SummonDragon, 10);

  //等待所有线程结束
  for (int i = 0; i < 7; i++) {
    finders[i].join();
  }
  summoner.join();

  return 0;
}
