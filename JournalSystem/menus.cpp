#include "menus.h"
#include "tasks.h"
#include <iostream>

void menu1() {
    int choice;

    while (true) {
        system("cls");
        std::cout << "============УПРАВЛЕНИЕ ГРУППАМИ=============" << std::endl;
        std::cout << "1. Добавить группу" << std::endl;
        std::cout << "2. Удалить группу" << std::endl;
        std::cout << "3. Список групп" << std::endl;
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
        case 2:
            system("cls");
            del_group();
            break;
        case 3:
            system("cls");
            get_groups();
            break;
        case 0:
            system("cls");
            return;
        default:
            std::cout << "Введите корректное число!" << std::endl;
        }

        std::cout << "\nНажмите Enter, чтобы продолжить...";
        std::cin.ignore(1000, '\n');
        std::cin.get();
    }
}

void menu2() {
    int choice;

    while (true) {
        system("cls");
        std::cout << "============УПРАВЛЕНИЕ СТУДЕНТАМИ===========" << std::endl;
        std::cout << "1. Добавить студента" << std::endl;
        std::cout << "2. Удалить студента" << std::endl;
        std::cout << "3. Список студентов" << std::endl;
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
            add_student();
            break;
        case 2:
            system("cls");
            del_student();
            break;
        case 3:
            system("cls");
            get_students();
            break;
        case 0:
            system("cls");
            return;
        default:
            std::cout << "Введите корректное число!" << std::endl;
        }

        std::cout << "\nНажмите Enter, чтобы продолжить...";
        std::cin.ignore(1000, '\n');
        std::cin.get();
    }
}

void menu3() {
    int choice;

    while (true) {
        system("cls");
        std::cout << "===========УПРАВЛЕНИЕ ПРЕДМЕТАМИ============" << std::endl;
        std::cout << "1. Добавить предмет" << std::endl;
        std::cout << "2. Удалить предмет" << std::endl;
        std::cout << "3. Список предметов" << std::endl;
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
            add_subject();
            break;
        case 2:
            system("cls");
            del_subject();
            break;
        case 3:
            system("cls");
            // добавить сюда get_subjects потом (вот бы не забыть)
            break;
        case 0:
            system("cls");
            return;
        default:
            std::cout << "Введите корректное число!" << std::endl;
        }

        std::cout << "\nНажмите Enter, чтобы продолжить...";
        std::cin.ignore(1000, '\n');
        std::cin.get();
    }
}

// потом разморозить!!
// 
//void menu4() {
//    int choice;
//
//    while (true) {
//        system("cls");
//        std::cout << "=============УПРАВЛЕНИЕ ОЦЕНКАМИ============" << std::endl;
//        std::cout << "1. Добавить оценки" << std::endl;
//        std::cout << "2. Отредактировать оценки" << std::endl;
//        std::cout << "0. Выйти из программы" << std::endl;
//        std::cout << "============================================" << std::endl;
//        std::cout << "Ваш выбор: ";
//
//        if (!(std::cin >> choice)) {
//            std::cin.clear();
//            std::cin.ignore(1000, '\n');
//            continue;
//        }
//
//        switch (choice) {
//        case 1:
//            system("cls");
//            add_student();
//            break;
//        case 2:
//            system("cls");
//            del_student();
//            break;
//        case 0:
//            system("cls");
//            return;
//        default:
//            std::cout << "Введите корректное число!" << std::endl;
//        }
//
//        std::cout << "\nНажмите Enter, чтобы продолжить...";
//        std::cin.ignore(1000, '\n');
//        std::cin.get();
//    }
//}