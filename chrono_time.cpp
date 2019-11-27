#include <chrono>
using namespace std;
using namespace chrono;

auto start = system_clock::now();
// do something...
auto end   = system_clock::now();
auto duration = duration_cast<microseconds>(end - start);
cout <<  "»¨·ÑÁË" 
     << double(duration.count()) * microseconds::period::num / microseconds::period::den 
     << "Ãë" << endl;
     