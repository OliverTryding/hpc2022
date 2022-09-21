#include <iostream>

#include "fraction_toolbox.hpp"

void print_fraction(fraction frac)
{
    std::cout << frac.num << '/' << frac.denom << std::endl;
}

void print_fraction_array(fraction frac_array[], int n)
{
    std::cout << "[ " << frac_array[0].num << '/' << frac_array[0].denom << std::endl;
    for (int i = 1; i < n-1; i++)
    {
        std::cout << "  ";
        print_fraction(frac_array[i]);
    }
    std::cout << "  " << frac_array[n-1].num << '/' << frac_array[n-1].denom << " ]" << std::endl;
}

fraction square_fraction(fraction frac)
{
    //TODO: implement function 2
        fraction square;
        square.num = frac.num * frac.num;
        square.denom = frac.denom * frac.denom;
        return square;
}

//TODO: implement function 3
void square_fraction_inplace(fraction & frac) 
{
        frac.num = frac.num * frac.num;
        frac.denom = frac.denom * frac.denom;
}


double fraction2double(fraction frac)
{
    //TODO: implement function 4
        double double_num = (double) frac.num;
        double double_denom = (double) frac.denom;
        return double_num / double_denom;
}

int gcd(int a, int b) 
{
    //TODO: implement function 5
        if(b == 0) { 
                return a;
        }
        else { 
                return gcd(b,a % b);
        }
}

//TODO: implement function 6
int gcd(fraction frac) 
{ 
    int a = frac.num;
    int b = frac.denom;
    while(b != 0) { 
            int t = b;
            b = a % b;
            a = t;
    }
    return a;
}


void reduce_fraction_inplace(fraction & frac)
{
    //TODO: implement function 7
    int greatest_common_divisor = gcd(frac.num,frac.denom);

    frac.num = frac.num / greatest_common_divisor;
    frac.denom = frac.denom / greatest_common_divisor;

    //TODO: add short comment to explain which of the gcd() functions your code is calling
    //This function uses the iterative version of gcd from line 56. 
    //This is because this version is loaded after the one on line 45 and therefore overloads gcd from line 45.
}

fraction add_fractions(fraction frac1, fraction frac2) 
{
    //TODO: implement function 8
    fraction frac;
    frac.num = frac1.num * frac2.denom + frac2.num * frac1.denom;
    frac.denom = frac1.denom * frac2.denom;
    reduce_fraction_inplace(frac);

    return frac;
}

double sum_fraction_array_approx(fraction frac_array[], int n) 
{
    //TODO: implement function 9
    double sum = 0;
    for (int i = 0; i < n; i++) {
            sum += fraction2double(frac_array[i]);
    }
    return sum;
    //TODO: add short comment to explain why this function is approximate
    //The function is an approximation because some fraction can not be made 
    //into exact floating point numbers.
}

//TODO: implement function 10
fraction sum_fraction_array(fraction frac_array[], int n) 
{
    fraction sum = frac_array[0];
    for (int i = 1; i < n; i++) {
            sum = add_fractions(sum,frac_array[i]);
    }
    return sum;
}



void fill_fraction_array(fraction frac_array[], int n)
{
    fraction temp_frac;
    temp_frac.num = 1;
    for (int i = 1; i <= n; i++)
    {
        temp_frac.denom = i * (i+1);
        frac_array[i-1] = temp_frac;
    }
}

