#include <iostream>
using namespace std;

//首先定义一个函数指针，形式为回调函数的具体返回类型以及参数组成
typedef int (*pFunc)(int, int);

/*回调函数的调用函数，通过该函数实现对回调函数的调用，
回调函数在该函数的调用方式是该函数的参数形式，并且对以
上定义的函数指针创建一个实例作为入参*/
int process(int a, int b, pFunc Callback) {
  cout << "callback start" << endl;
  Callback(a, b); //调用回调函数，将所需参数传入
  return 0;
}

/*回调函数的真正实现，返回类型和参数与定义的函数指针形式保持一致*/
int Add(int a, int b) {
  cout << "process callback function..." << endl;
  return a + b;
}

/*主函数*/
int main() {
  cout << "main function" << endl;
  process(1, 2, Add);
  return 0;
}
