#include <stdio.h>
#include <time.h>
#include <vector>
#include <typeinfo>

#define N 100

std::vector<double> & init_vector(int n)
{
    std::vector<double> &v = *(new std::vector<double>(n));
    for (int i=1; i<n; i++)
        if (i % 2 == 0)
            v[i] = 1./i;
        else
            v[i] = -1./i;
    v[0] = 1.;
    return v;
}

double sum0(double *v, int n)
{
    double sum = 0;
    for (int k=0; k < N; k++) {
        for (int j=0; j < n; j++)
            sum += v[j];
    }
    return sum;
}

double sum1(std::vector<double> &v)
{
    double sum = 0;
    for (int k=0; k < N; k++) {
        for (int j=0; j < v.size(); j++)
            sum += v[j];
    }
    return sum;
}

double sum2(std::vector<double> &v)
{
    double sum = 0;
    for (int k=0; k < N; k++) {
        for (std::vector<double>::const_iterator it=v.begin();
                it != v.end(); ++it)
            sum += *it;
    }
    return sum;
}

double sum3(std::vector<double> &v)
{
    double sum = 0;
    for (int k=0; k < N; k++) {
        for (auto it=v.begin(); it != v.end(); ++it)
            sum += *it;
    }
    return sum;
}

#define for_each(element, list) \
    for (auto element=*((list).begin()), _it=(list).begin(); \
            _it != (list).end(); element=*(++_it))

double sum4(std::vector<double> &v)
{
    double sum = 0;
    for (int k=0; k < N; k++) {
        for_each(x, v)
            sum += x;
    }
    return sum;
}

int main()
{
    int n = 1e7;
    printf("initializing v...\n");
    std::vector<double> &v = init_vector(n);
    double *a = &(v[0]);
    clock_t t;
    printf("done.\n");
    t = clock();
    printf("sum0: %f\n", sum0(a, n));
    printf("time: %d\n", clock() - t);
    t = clock();
    printf("sum1: %f\n", sum1(v));
    printf("time: %d\n", clock() - t);
    t = clock();
    printf("sum2: %f\n", sum2(v));
    printf("time: %d\n", clock() - t);
    t = clock();
    printf("sum3: %f\n", sum3(v));
    printf("time: %d\n", clock() - t);
    t = clock();
    printf("sum4: %f\n", sum4(v));
    printf("time: %d\n", clock() - t);
    return 0;
}
