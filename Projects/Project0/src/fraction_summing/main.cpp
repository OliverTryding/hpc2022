#include <iostream>
#include <stdio.h>
#include <stdlib.h>

#include "fraction_toolbox.hpp"

using namespace std;

// read command line arguments
static void readcmdline(fraction & frac, int argc, char* argv[])
{
    if (argc!=3)
    {
        printf("Usage: n d\n");
        printf("  n        numerator of fraction\n");
        printf("  d        denominator of fraction\n");
        exit(1);
    }

    // read n
    frac.num = atoi(argv[1]);

    // read d
    frac.denom = atoi(argv[2]);
}

static void test23467(int argc, char* argv[])
{
    //TODO: implement function
    fraction frac;

    readcmdline(frac, argc, argv);

    printf("The original fraction: ");
    print_fraction(frac);

    printf("Square of the fraction using function 2: ");
    print_fraction(square_fraction(frac));

    printf("Square of the fraction using function 3: ");
    square_fraction_inplace(frac);
    print_fraction(frac);

    printf("Fraction to double using function 4: %lf\n", fraction2double(frac));

    printf("GCD using function 6: %d\n", gcd(frac));

    printf("Reduction of the fraction using function 7: ");
    reduce_fraction_inplace(frac);
    print_fraction(frac);
}

static void test5()
{
    //TODO: implement function
    int a;
    int b;
    printf("Give an integer: ");
    std::cin >> a;
    printf("Give another integer: ");
    std::cin >> b;

    printf("GCD using function 5: %d",gcd(a,b));
}

static void test_array_functions(int n)
{
    //TODO: implement function
    fraction* frac_array = (fraction *) malloc(n);

    fill_fraction_array(frac_array,n);

    printf("Sum of the fractions using function 10: ");
    print_fraction(sum_fraction_array(frac_array,n));

    printf("Sum of the fractions using function 9: %lf\n",sum_fraction_array_approx(frac_array,n));

    //TODO: find n for which sum function breaks. Explain what is happening.
}

static void test_toolbox(int argc, char* argv[])
{
    cout << "\n===============  test23467  =============== " << endl;
    test23467(argc, argv);

    cout << "\n=================  test5  ================= " << endl;
    test5();

    cout << "\n==========  test_array_functions  ========= " << endl;
    int n = 1000;
    test_array_functions(n);
}

int main(int argc, char* argv[])
{
    test_toolbox(argc,argv);
}