#include "print.h"

namespace gameTheoryAndOperationsResearch {
    void _gameTheoryAndOperationsResearch_print::print_vector(std::ostream& out, char * str, double *p, int n)
    {
        out.precision(3);
        out << str << ": ";
        for (int i = 0; i < n; i++)
            out << p[i] << std::fixed << std::setprecision(5) << " ";
        out << std::endl;
    }
}
