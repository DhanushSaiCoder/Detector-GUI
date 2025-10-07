#include <iostream>
#include <memory>
#include <string>

using namespace std;

int main(){
    unique_ptr<int> ptr = make_unique<int>(101);

    unique_ptr<int> ptr2 = move(ptr);


    shared_ptr<int> sptr = make_shared<int>(33);
    cout << *sptr << endl;

    shared_ptr<int> sptr2 = sptr;
    cout << *sptr2 << endl;
}
