#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

[[nodiscard]] int generateCode() noexcept{
    srand(time(nullptr));

    int rand_num = 0;
    for(int i = 0;i < COUNT;i++) {
        rand_num  = rand() % 10;
    }

    return rand_num;
}
