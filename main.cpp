#include <iostream>
#include <fstream>
#include <iomanip>

#include "main.define.h"

#include "maxmin.h"
#include "braun_robinson.h"
#include "print.h"

namespace gameTheoryAndOperationsResearch {

    void _gameTheoryAndOperationsResearch_readfile() {
        std::string line;std::ifstream in(gameTheoryAndOperationsResearch_filename);
        while (std::getline(in, line))
            std::cout << line << std::endl;
    }

    void _gameTheoryAndOperationsResearch_deletefile() {
        std::remove(gameTheoryAndOperationsResearch_filename);
    }
    gameTheoryAndOperationsResearch::_gameTheoryAndOperationsResearch_maxmin            class_maxmin_main;
    gameTheoryAndOperationsResearch::_gameTheoryAndOperationsResearch_print             class_print_main;
    gameTheoryAndOperationsResearch::_gameTheoryAndOperationsResearch_braun_robinson    class_braun_robinson;

    int _main(int argc, char* argv[])
    {
        // Удаляем файл
        _gameTheoryAndOperationsResearch_deletefile();

        // Аналитическое решение
        std::ofstream fout(gameTheoryAndOperationsResearch_filename);

        double x, y;

        // Решение уравнений для определения x и y
        x = ((c*e / (2 * b) - d) / (2 * a - c * c / (2 * b)));
        y = ((c*d / (2 * a) - e) / (2 * b - c * c / (2 * a)));



//        fout << "Kulikova Alyona - v4\n";
        fout << "Analitika: " << std::endl;
        fout << "x = " << x
             << " y = " << y << std::endl;

        fout << "H(" << x
             << ", " << y
             << ") = " << H(x, y)
             << std::endl;



        // Численный метод
        int N = 2;
        int N_END = 0;
        double minMax, maxMin;
        int i, j; // Индексы
        while (true)
        {
            double **Matr = new double*[N + 1];
            double *p = new double[N + 1];
            double *q = new double[N + 1];
            double h = 1. / N;
            x = 0;

            // Заполняем матрицу игры и выводим ее на экран
            fout << std::endl;
            fout << "[" << "#" << N_END << "(N=" << N << ")]" << std::endl;
            for (int i = 0; i <= N; i++, x+=h)
            {
                Matr[i] = new double[N + 1];
                y = 0;
                for (int j = 0; j <= N; j++, y += h)
                {
                    Matr[i][j] = H(x, y);
                    if(N <= 10)
                        fout << std::fixed << std::setprecision(3)
                             << std::setw(10) << Matr[i][j];
                }
                if(N <= 10)
                    fout << std::endl;
            }

            fout << std::endl;

            // Находим maxMin и minMax для матрицы игры
            maxMin = class_maxmin_main.max_min(Matr, N + 1, N + 1, i);
            minMax = class_maxmin_main.min_max(Matr, N + 1, N + 1, j);

            fout << "maxMin = " << maxMin << std::fixed << std::setprecision(5) << std::setw(6)
                 << " minMax =" << minMax << std::fixed << std::setprecision(5)
                 << std::endl;

            fout << std::endl;

            if (maxMin == minMax) {
                // Проверяем наличие седловой точки
                fout << "* There is a saddle point (maxMin == minMax)" << std::endl;
                fout << "H(" << h * i << ", "
                     << h * j << ") = "
                     << Matr[i][j]
                        << std::endl;

                // Вычисляем среднее взвешенное значение
                double x_sr = 0;
                x = 0;

                /**
                 *  исправлена ошибка, где при старте сразу же происходит умножение и из-за этого
                 *  х имеет большое значение
                 */

                if(N > 2)
                    for (int i = 0; i <= N; i++, x += h) {
                        x_sr += x * p[i];
                    }

                double y_sr = 0;
                y = 0;

                for (int i = 0; i <= N; i++, y += h)
                    y_sr += y * q[i];

                fout << "x = " << x_sr
                     << " y = " << y_sr
                     << " H = " << minMax
                     << std::endl;
            }
            else
            {
                fout << "* No saddle point (maxMin != minMax), solution by Brown-Robinson method:" << std::endl;

                // Применяем алгоритм Брауна-Робинсона для решения матричной игры
                class_braun_robinson.braun_robinson(Matr, p, q, N + 1, N + 1, minMax, maxMin, fout);
                if(N <= 10) class_print_main.print_vector(fout, (char *)"p", p, N + 1);
                if(N <= 10) class_print_main.print_vector(fout, (char *)"q", q, N + 1);

                // Вычисляем среднее взвешенное значение
                double x_sr = 0;
                x = 0;

                for (int i = 0; i <= N; i++, x += h)
                    x_sr += x * p[i];

                double y_sr = 0;
                y = 0;

                for (int i = 0; i <= N; i++, y += h)
                    y_sr += y * q[i];

                fout << "x = " << x_sr
                     << " y = " << y_sr
                     << " H = " << minMax
                     << std::endl;
            }

            if (N_END >= 30)
                break;
            N_END++; // :)

            delete[] p;
            delete[] q;

            for (int i = 0; i < N + 1; i++)
                delete[] Matr[i];

            delete[] Matr;

            ++N;
        }

        // Считываем файл
        _gameTheoryAndOperationsResearch_readfile();

        return 0;
    }
}

int main(int argc, char* argv[])
{
    gameTheoryAndOperationsResearch::_main(argc, argv);
    return 0;
}
