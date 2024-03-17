#ifndef MAIN_DEFINE
#define MAIN_DEFINE

// -15 20/3 40 -12 -24

#define a (double)(-15)
#define b (double)(20. / 3)
#define c (double)40
#define d (double)(-12)
#define e (double)(-24)

#define gameTheoryAndOperationsResearch_filename "gameTheoryAndOperationsResearch_l3.txt"

#define H(x, y)\
    ((double)(a * x*x + b * y*y + c * x*y + d * x + e * y))

#endif // MAIN_DEFINE
