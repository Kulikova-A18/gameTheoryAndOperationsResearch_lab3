#include "maxmin.h"

namespace gameTheoryAndOperationsResearch {
    // Функция находит максимальный минимум в матрице и возвращает его значение
    // Параметры:
    // _matrix - двумерный массив значений
    // n - количество строк в матрице
    // m - количество столбцов в матрице
    // iMax - индекс строки, содержащей максимальный минимум
    // Возвращает максимальный минимум в матрице

    double _gameTheoryAndOperationsResearch_maxmin::max_min(double **_matrix, int n, int m, int& iMax)
    {
        double min;
        double max = -9e99; // Инициализация максимального значения

        for (int i = 0; i < n; i++) // Итерация по строкам матрицы
        {
            min = _matrix[i][0]; // Инициализация минимума для текущей строки

            for (int j = 1; j < m; j++) // Итерация по столбцам матрицы
                if (min > _matrix[i][j]) // Если текущий элемент меньше минимума
                    min = _matrix[i][j]; // Обновляем значение минимума

            if (max < min) // Если текущий минимум больше записанного максимума
            {
                max = min; // Обновляем значение максимума
                iMax = i; // Запоминаем индекс строки
            }
        }
        return max; // Возвращаем найденный максимальный минимум
    }

    // Функция нахождения минимального из максимальных значений в строках матрицы
    // Принимает двумерный массив _matrix, количество строк n, количество столбцов m и ссылку на iMin
    // Возвращает минимальное из максимальных значений и индекс строки, в которой оно находится
    double _gameTheoryAndOperationsResearch_maxmin::min_max(double **_matrix, int n, int m, int& iMin)
    {
        double min = 9e99; // Начальное значение минимума - очень большое число
        double max; // Переменная для хранения максимального значения в столбце
        for (int j = 0; j < m; j++)
        {
            max = _matrix[0][j]; // Изначально первый элемент в столбце становится максимальным

            // Находим максимальный элемент в столбце
            for (int i = 1; i < n; i++) // Перебираем все столбцы
                if (max < _matrix[i][j])
                    max = _matrix[i][j];

            // Если найденный максимум меньше текущего минимума
            if (max < min)
            {
                min = max; // Запоминаем новый минимум
                iMin = j; // Сохраняем индекс столбца с минимальным максимальным значением
            }
        }
        return min; // Возвращаем минимальное из максимальных значений
    }

    // Функция для поиска минимального значения в матрице
    double _gameTheoryAndOperationsResearch_maxmin::min_matrix(double **pM, int n, int m)
    {
        // Инициализация переменной для хранения минимального значения
        double mymin = pM[0][0];

        // Циклы для перебора всех элементов матрицы
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                // Проверка текущего элемента на то, меньше ли он текущего минимального значения
                if (pM[i][j] < mymin)
                    // Если элемент меньше текущего минимума, обновляем минимальное значение
                    mymin = pM[i][j];

        // Возвращаем найденное минимальное значение
        return mymin;
    }
}