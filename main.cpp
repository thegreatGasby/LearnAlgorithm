#include "BruteForce.h"
#include"MatchString.h"
#include"TestMatchString.h"
using namespace std;

int main() {
    TestMatchString tester;
    MatchString method(make_unique<BruteForce>());
    cout << tester.test(method, 1000000);
    return 0;
}

