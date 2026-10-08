#include <iostream>
#include "PassForge.hpp"
#include "KeySec.hpp"
int main()
{
    KeySec ks;
    std::string some{"HACKERS ARE BEST!"};
    ks.setGlobPass("some");
    std::cout << ks.showOnce() << '\n';

    Sleep(60000);
}