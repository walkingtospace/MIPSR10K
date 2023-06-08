#include <iostream>
#include "activelist.h"

void test_setDonebit() {
    ActiveList activeList;
    activeList.m_setDonebit(1);
    if (activeList.getDonebit() == 1) {
        std::cout << "Test setDonebit passed" << std::endl;
    } else {
        std::cout << "Test setDonebit failed" << std::endl;
    }
}

int main() {
    test_setDonebit();
    return 0;
}