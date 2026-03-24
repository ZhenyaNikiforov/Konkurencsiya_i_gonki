#include <iostream>
#include <atomic>
#include <thread>
#include <chrono>
using namespace std;

int maximumContainer = 10;
atomic<int> countContainer(0);

void incrementContainer()
{
  for (int i = 0; i < maximumContainer; ++i)
  {
    this_thread::sleep_for(chrono::seconds(1));
    countContainer++;
    cout << "Prischel; v nakopitele: " << countContainer << endl;
  }
  cout << "Vse prishli!" << endl;
  return;
}

void decrementContainer()
{
  for (int i = 0; i < maximumContainer; ++i)
  {
    this_thread::sleep_for(chrono::seconds(2));
    countContainer--;
    cout << "Propustil; v nakopitele: " << countContainer << endl;
  }
  cout << "Vsekh propustil! v nakopitele: " << countContainer;
  return;
}

int main()
{
  thread firstJet(incrementContainer);
  thread secondJet(decrementContainer);
  firstJet.join();
  secondJet.join();
  return 0;
}