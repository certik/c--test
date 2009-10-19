#include <stdio.h>
#include <vector>
#include <typeinfo>

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

double sum1(std::vector<double> &v)
{
    double sum = 0;
    for (int j=0; j < v.size(); j++)
        sum += v[j];
    return sum;
}

double sum2(std::vector<double> &v)
{
    double sum = 0;
    for (std::vector<double>::const_iterator it=v.begin();
            it != v.end(); ++it)
        sum += *it;
    return sum;
}

double sum3(std::vector<double> &v)
{
    double sum = 0;
    for (auto it=v.begin(); it != v.end(); ++it)
        sum += *it;
    return sum;
}

double sum4(std::vector<double> &v)
{
    double sum = 0;
    std::vector<double>::const_iterator it=v.begin();
    std::vector<double>::const_iterator &it2 = it;
    for (; it2 != v.end(); ++it2) {
        // it2.base() is of a type "const double *"
        const double *p = it2.base();
        const double x = *p;
        sum += x;
    }
    return sum;
}

int main()
{
    std::vector<double> &v = init_vector(11);
    auto i = 5;
    printf("i=%d\n", i);
    printf("sum1: %f\n", sum1(v));
    printf("sum2: %f\n", sum2(v));
    printf("sum3: %f\n", sum3(v));
    printf("sum4: %f\n", sum4(v));
    return 0;
}
