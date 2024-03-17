#include "braun_robinson.h"

#include "maxmin.h"
#include <memory.h>
#include <cmath>

namespace gameTheoryAndOperationsResearch {
    gameTheoryAndOperationsResearch::_gameTheoryAndOperationsResearch_maxmin braun_robinson_maxmin;

    // Классичекий метод Брауна-Робинсона для матрицы игры
    void _gameTheoryAndOperationsResearch_braun_robinson::braun_robinson(double **pM, double *p, double *q, int n, int m, double& vmin, double& vmax, std::ofstream & fout)
    {
        // Выделение памяти для хранения частот по строкам и столбцам
        unsigned __int64 *pX = new unsigned __int64[n]; // Частоты по строкам
        unsigned __int64 *pY = new unsigned __int64[m]; // Частоты по столбцам

        // Инициализация переменных и массивов
        unsigned __int64 k1 = 1, k2 = 0; // Общее число выбора строк и столбцов
        double *pV1 = new double[n]; // Суммарный выигрыш 1-го игрока
        double *pV2 = new double[m]; // Суммарный выигрыш 2-го игрока

        for (int i = 0; i < n; i++)
            pV1[i] = pX[i] = 0;
        for (int i = 0; i < m; i++)
            pV2[i] = pY[i] = 0;

        // Находим минимум в матрице игры
        double mymin = braun_robinson_maxmin.min_matrix(pM, n, m);

        // Если минимум отрицательный (есть в матрице отриц элементы), делаем все элементы положительными, прибавлением одного и того же числа
        if (mymin < 0)
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    pM[i][j] -= (mymin - 1);

        // Определение первого хода первого игрока по максимину
        int iMax, iMin;
        braun_robinson_maxmin.max_min(pM, n, m, iMax); pX[iMax]++; // Первый ход первого игрока (по максимину)

        for (int i = 0; i < m; i++)
            pV2[i] += pM[iMax][i];

        do
        {
            // Выбор второго игрока
            double min = 9e99;
            for (int i = 0; i < m; i++)
                if (pV2[i] < min)
                {
                    min = pV2[i];
                    iMin = i;
                }

            pY[iMin]++; k2++;
            vmin = min / k1; // Верхняя цена игры
            for (int i = 0; i < n; i++)
                pV1[i] += pM[i][iMin];

            // Выбор первого игрока
            double max = 0;
            for (int i = 0; i < n; i++) if (pV1[i] > max)
            {
                max = pV1[i];
                iMax = i;
            }

            pX[iMax]++; k1++;
            vmax = max / k2; // Нижняя цена игры

            for (int i = 0; i < m; i++)
                pV2[i] += pM[iMax][i];

        } while (fabs(vmax - vmin) > 0.001); // Условие остановки

//        // Печатаем число ходов, сделанных каждым игроком
//        fout << "[" << std::endl;
//        fout << "Printing the number of moves made by each player:" << std::endl;
//        fout << "k1 = " << k1 << " k2 = " << k2 << std::endl;
//        fout << "]" << std::endl;

        // В случае отрицательных элементов обратный переход к исходной матрице
        if (mymin < 0) {
            vmax += (mymin - 1);
            vmin += (mymin - 1);
        }

        // Расчет оценок вероятностей
        for (int i = 0; i < n; i++)
            p[i] = (double)pX[i] / k1;
        for (int i = 0; i < m; i++)
            q[i] = (double)pY[i] / k2;

        delete[]pX;
        delete[]pY;
        delete[]pV1;
        delete[]pV2;
    }
}
