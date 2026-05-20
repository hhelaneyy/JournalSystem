# 📔 JournalSystem

> **Система учёта студентов** — консольное C++ приложение для управления записями об успеваемости и посещаемости студентов.

[![Language](https://img.shields.io/badge/language-C%2B%2B-blue.svg)](https://isocpp.org/)
[![Platform](https://img.shields.io/badge/platform-Windows%20x64%20%7C%20x86-lightgrey.svg)](#сборка)

---

## Описание

JournalSystem — десктопное приложение на C++, предназначенное для ведения электронного журнала учебного заведения. Система позволяет хранить, просматривать и управлять данными о студентах: их персональной информацией, оценками и посещаемостью.

---

## Технологический стек

| Компонент | Версия / Детали |
|---|---|
| Язык | C++ (98.3%), C (1.7%) |
| IDE / Build system | Visual Studio (`.slnx` / `.vcxproj`) |
| Целевые платформы | Windows x64, x86 |

---

## Структура репозитория

```
JournalSystem/
├── JournalSystem/          # Исходный код проекта (*.cpp, *.h, *.vcxproj)
├── JournalSystem.slnx      # Solution-файл Visual Studio (новый XML-формат)
├── .gitignore
├── .gitattributes
└── README.md
```

---

## Требования

- **OS:** Windows 10 / 11
- **IDE:** Visual Studio 2022 или новее (поддержка формата `.slnx`)
- **Компилятор:** MSVC (v143+) с поддержкой C++17 или выше

---

## Сборка

### Через Visual Studio

1. Клонируйте репозиторий:
   ```bash
   git clone https://github.com/hhelaneyy/JournalSystem.git
   cd JournalSystem
   ```

2. Откройте `JournalSystem.slnx` в Visual Studio 2022.

3. Выберите конфигурацию сборки — `Debug` или `Release` — и целевую платформу (`x64` или `x86`).

4. Нажмите **Build → Build Solution** (`Ctrl+Shift+B`).

5. Готовый исполняемый файл появится в папке `x64/Release/` (или соответствующей конфигурации).

### Через командную строку (MSBuild)

```bash
msbuild JournalSystem.slnx /p:Configuration=Release /p:Platform=x64
```

---

## Запуск

После сборки запустите исполняемый файл из директории сборки:

```bash
./x64/Release/JournalSystem.exe
```

---

## Возможности

- Добавление, просмотр и удаление записей о студентах
- Ведение журнала оценок и посещаемости
- Поиск и фильтрация данных по студентам
- Консольный интерфейс взаимодействия
