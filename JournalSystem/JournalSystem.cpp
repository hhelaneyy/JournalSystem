#include <iostream>
#include "tasks.h"

int main()
{
    setlocale(LC_ALL, "Russian");

    init_db();
    std::cout << "База данных успешно функционирует.";
    return 0;
}
