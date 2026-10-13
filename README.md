# Проєкт 2, варіант 16: adjacent_difference (максимальна різниця між сусідами)

Компілятор: g++ 15.2.0 (MSYS2 UCRT64), C++20, TBB (для паралельних політик).

## Формат вхідних файлів

Файли `sequence_1000.txt`, `sequence_100000.txt`, `sequence_10000000.txt`:

- рядок 1: N — кількість елементів;
- рядки 2…N+1: N цілих чисел, по одному в рядку.

Приклад (N = 3):

```
3
-12
705
0
```

Файли генерує `generate.exe` один раз: `std::mt19937` + `std::uniform_int_distribution`,
значення в діапазоні [−1000, 1000]. Обидві збірки (-O0 і -O3) читають ті самі файли.

## Збірка (Release)

```
cmake -S . -B build-O0 -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DOPT_LEVEL=-O0
cmake --build build-O0
cmake -S . -B build-O3 -G "MinGW Makefiles" -DCMAKE_BUILD_TYPE=Release -DOPT_LEVEL=-O3
cmake --build build-O3
```

## Запуск (з кореня проєкту)

```
.\build-O3\generate.exe
.\build-O0\benchmark.exe | Out-File -Encoding utf8 output_O0.txt
.\build-O3\benchmark.exe | Out-File -Encoding utf8 output_O3.txt
```
