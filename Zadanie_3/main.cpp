/*- Задание 3. Класс с мьютексами -*/

#include <iostream>
#include <mutex>
#include <iomanip>
using namespace std;

class Data
{
private:
  int value_a;
  int value_b;
  int value_c;
  mutable mutex mtx;

public:
  Data(int value_a, int value_b, int value_c)
  {
    this->value_a = value_a;
    this->value_b = value_b;
    this->value_c = value_c;
  }

  void swapData_a(Data &other)
  {
    if (this == &other)
    {
      return;
    };
    scoped_lock lock(this->mtx, other.mtx);
    swap(this->value_a, other.value_a);
    return;
  }

  void swapData_b(Data &other)
  {
    if (this == &other)
    {
      return;
    }

    lock(this->mtx, other.mtx);
    lock_guard<mutex> lockThis(this->mtx, adopt_lock);
    lock_guard<mutex> lockOther(other.mtx, adopt_lock);
    swap(this->value_b, other.value_b);

    return;
  }

  void swapData_c(Data &other)
  {
    if (this == &other)
    {
      return;
    }

    unique_lock<mutex> lockThis(this->mtx, defer_lock);
    unique_lock<mutex> lockOther(other.mtx, defer_lock);
    lock(lockThis, lockOther);
    swap(this->value_c, other.value_c);

    return;
  }

  int showValue_a()
  {
    return this->value_a;
  };

  int showValue_b()
  {
    return this->value_b;
  }

  int showValue_c()
  {
    return this->value_c;
  }
};

int main()
{
  Data d1(1, 2, 3);
  Data d2(10, 20, 30);

  cout << endl;
  cout << setw(15) << "d1.value_a = " << setw(5) << d1.showValue_a()
       << setw(15) << "d1.value_b = " << setw(5) << d1.showValue_b()
       << setw(15) << "d1.value_c = " << setw(5) << d1.showValue_c()
       << endl;
  cout << setw(15) << "d2.value_a = " << setw(5) << d2.showValue_a()
       << setw(15) << "d2.value_b = " << setw(5) << d2.showValue_b()
       << setw(15) << "d2.value_c = " << setw(5) << d2.showValue_c()
       << endl;
  cout << endl;

  d1.swapData_a(d2);
  d1.swapData_b(d2);
  d1.swapData_c(d2);

  cout << setw(15) << "d1.value_a = " << setw(5) << d1.showValue_a()
       << setw(15) << "d1.value_b = " << setw(5) << d1.showValue_b()
       << setw(15) << "d1.value_c = " << setw(5) << d1.showValue_c()
       << endl;
  cout << setw(15) << "d2.value_a = " << setw(5) << d2.showValue_a()
       << setw(15) << "d2.value_b = " << setw(5) << d2.showValue_b()
       << setw(15) << "d2.value_c = " << setw(5) << d2.showValue_c()
       << endl;
  cout << endl;

  return 0;
}