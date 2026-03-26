/*- Подпрограмма, посвящённая прогресс-барам.
(Задание-2) -*/

#include <iostream>
#include <vector>
#include <string>
#include <thread>
#include <chrono>
#include <mutex>
#include <cstdlib>
#include <iomanip>
#include <windows.h>
using namespace std;

int threadsQuantity = 10;
int threadLength = 50;

vector<string> threadList(threadsQuantity, string(threadLength, '-'));
vector<int> threadsID(threadsQuantity, 0);
vector<double> threadsTime(threadsQuantity, 0);

mutex mtx;

void fillBar(int threadNumber)
{
  int myId = static_cast<int>(GetCurrentThreadId());
  auto startTime = chrono::high_resolution_clock::now();

  for (int symbolCount = 0; symbolCount < threadLength; ++symbolCount)
  {
    this_thread::sleep_for(chrono::seconds(1));
    lock_guard<mutex> lock(mtx);
    threadList[threadNumber][symbolCount] = '*';
    threadsID[threadNumber] = myId;

    bool lastSymbol = false;

    if (symbolCount + 1 == threadLength)
    {
      lastSymbol = true;
      auto endTime = chrono::high_resolution_clock::now();
      chrono::duration<double> resultTime = endTime - startTime;
      threadsTime[threadNumber] = resultTime.count();
    }

#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif

    cout << setw(5) << "NUM"
         << setw(10) << "ID"
         << setw(threadLength + 2) << "PROGRESS_BAR";
    if (lastSymbol)
      cout << setw(15) << "TIME";
    cout << endl;

    for (int threadsCount = 0; threadsCount < threadsQuantity; ++threadsCount)
    {
      cout << setw(5) << threadsCount + 1
           << setw(10) << threadsID[threadsCount]
           << setw(threadLength + 2) << threadList[threadsCount];
      if (lastSymbol)
        cout << setw(15) << threadsTime[threadsCount];
      cout << endl;
    }
  }
  return;
}

int main()
{
  vector<thread> threads;

  for (int threadsCount = 0; threadsCount < threadsQuantity; ++threadsCount)
  {
    threads.emplace_back(fillBar, threadsCount);
  };

  for (auto &t : threads)
  {
    if (t.joinable())
    {
      t.join();
    };
  };

  return 0;
}