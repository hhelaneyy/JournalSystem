#include <iostream>
#include "tasks.h"

int main() {
    setlocale(LC_ALL, "Russian");
    init_db();
    int choice;

    while (true) {
        system("cls");
        std::cout << "=============ЭЛЕКТРОННЫЙ ЖУРНАЛ=============" << std::endl;
        std::cout << "1. Создать группу" << std::endl;
        std::cout << "0. Выйти из программы" << std::endl;
        std::cout << "============================================" << std::endl;
        std::cout << "Ваш выбор: ";

        if (!(std::cin >> choice)) {
            std::cin.clear();
            std::cin.ignore(1000, '\n');
            continue;
        }

        switch (choice) {
        case 1:
            system("cls");
            add_group();
            break;
        case 0:
            std::cout << "Выход из программы..." << std::endl;
            return 0;
        default:
            std::cout << "Введите корректное число!" << std::endl;
        }

        std::cout << "\nНажмите Enter, чтобы продолжить...";
        std::cin.ignore(1000, '\n');
        std::cin.get();
    }
    return 0;
}