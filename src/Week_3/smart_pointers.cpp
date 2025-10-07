#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main(){
    unique_ptr<int> ptr = make_unique<int>(101);
    cout << *ptr << endl;
}
