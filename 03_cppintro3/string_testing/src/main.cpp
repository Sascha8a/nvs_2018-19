
#include <iostream>
#include <thread>

using namespace std;

int main() {
    string str{"abcd"};
    cout << "Start: " << str << endl;
    str.append("fgh");
    cout << "append 'fgh': " << str << endl;
    str.insert(5, "e");
    cout << "insert 'e': " << str << endl;
    str.replace(4, 2, "ef");
    cout << "replace 'fe' with 'ef': " << str << endl;
    str = str.substr(0, 3);
    cout << "substr 0 - 3: " << str << endl;
}
