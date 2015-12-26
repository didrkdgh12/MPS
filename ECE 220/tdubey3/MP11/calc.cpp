#include <cmath>
#include "calc.h"
using namespace std;

/**
 * This Program does elementary computations on various types of numbers.
 *
 * The program functions by extending a base Number class that represents a standard number
 *
 * The program then splits into 3 types of numbers, each using or overiding methods of the number class or the operators
 *
 * Real number represents all the numbers that are in the real domain
 *
 * Complex number represnts all the numbers that are in the complex domain, however, these numbers are made up of both a complex component and a real component, thus it uses the Real
 * Number class
 *
 * Rational Number represents all the numbers that can be reduced to a fraction, and represents the numbers as such, reducing all opeations to their simplest fraction.
 */


// RealNumber, ComplexNumber and RationalNumber inherit from base Number class.


//==============NUMBER===============//
Number::Number(){}

Number::~Number(){}

double Number::magnitude(){return 0.0;}

void Number::print(){}

Number Number::operator + (const Number& arg)
{
    Number result;
    return result;
}

Number Number::operator - (const Number& arg)
{
    Number result;
    return result;
}

Number Number::operator * (const Number& arg)
{
    Number result;
    return result;
}

Number Number::operator / (const Number& arg)
{
    Number result;
    return result;
}

void Number::set_value(double rval){}

void Number::set_value(double rval, double ival){}



//=============real=====================//
//constructors for real number
RealNumber::RealNumber()
{
    realComponent = 0.0;
}

RealNumber::RealNumber(double rval)
{
    realComponent = rval;
}

//return the magnitiude of the real number
double RealNumber::magnitude()
{
    return abs(realComponent);
}

//print real number out
void RealNumber::print(){
    cout << "RealNumber: " << realComponent << "\n" << endl;
}

//real + real
RealNumber RealNumber::operator + (const RealNumber& arg)
{
    RealNumber result;
    //Add the argument to the current value
    result.realComponent = realComponent + arg.realComponent;
    return result;
}

//real - real
RealNumber RealNumber::operator - (const RealNumber& arg)
{
    RealNumber result;
    //Subtract the argument to the current value
    result.realComponent = realComponent - arg.realComponent;
    return result;
}

//real * real
RealNumber RealNumber::operator * (const RealNumber& arg)
{
    RealNumber result;
    //Multiply the argument to the current value
    result.realComponent = realComponent * arg.realComponent;
    return result;
}

//real/real
RealNumber RealNumber::operator / (const RealNumber& arg)
{
    RealNumber result;
    //Divide the argument to the current value
    result.realComponent = realComponent / arg.realComponent;
    return result;
}

//set the value for real number
void RealNumber::set_value (double rval)
{
    realComponent = rval;
}



//=============complex================//

ComplexNumber::ComplexNumber()
{
    //You have both a imaginary component and real, so two variables are needed
    realComponent = 0.0;
    imagComponent = 0.0;
}

ComplexNumber::ComplexNumber(double rval, double ival)
{
    realComponent = rval;
    imagComponent = ival;
}

//return the magnitude of the complex number
double ComplexNumber::magnitude(){
    //Need to essentially use distance formula to find magnitude in imaginary plane and real plane
    double realCmp = realComponent * realComponent;
    double imgCmp = imagComponent * imagComponent;
    return sqrt(realCmp + imgCmp);
}
//print the complexnumber
void ComplexNumber::print(){
    cout << "ComplexNumber: " << realComponent << " + " << imagComponent << "i\n";
}

//imag + imag
ComplexNumber ComplexNumber::operator + (const ComplexNumber& arg)
{
    ComplexNumber result;
    //Just add the two components together
    result.realComponent = realComponent + arg.realComponent;
    result.imagComponent = imagComponent + arg.imagComponent;

    return result;
}

//imag - imag
ComplexNumber ComplexNumber::operator - (const ComplexNumber& arg)
{
    ComplexNumber result;
    //Just subtract the two components
    result.realComponent = realComponent - arg.realComponent;
    result.imagComponent = imagComponent - arg.imagComponent;

    return result;
}

//imag * imag
ComplexNumber ComplexNumber::operator * (const ComplexNumber& arg)
{
    ComplexNumber result;
    //Multiply by doing (ac-db) + (ab + cd)i where the numbers are a+bi and c+di
    result.realComponent = (realComponent * arg.realComponent) - (imagComponent * arg.imagComponent);
    result.imagComponent = (realComponent * arg.imagComponent) + (imagComponent * arg.realComponent);

    return result;
}

//imag/imag
ComplexNumber ComplexNumber::operator / (const ComplexNumber& arg)
{
    ComplexNumber result;
    //Divide by doing (ac+bd/c^2+d^2)+(bc-ad/c^2+d^2)i where the numbers are a+bi and c+di
    result.realComponent = ((realComponent * arg.realComponent) + (imagComponent * arg.imagComponent)) / ((arg.realComponent * arg.realComponent) + (arg.imagComponent * arg.imagComponent));
    result.imagComponent = ((imagComponent * arg.realComponent) - (realComponent * arg.imagComponent)) / ((arg.realComponent * arg.realComponent) + (arg.imagComponent * arg.imagComponent));

    return result;
}

//set the complexnumber value
void ComplexNumber::set_value (double rval, double ival)
{
    realComponent = rval;
    imagComponent = ival;
}







//=============rational================//

RationalNumber::RationalNumber()
{
    numerator = 0;
    denominator = 1;
}

RationalNumber::RationalNumber(int numer, int denom)
{
    RationalNumber::set_value(numer, denom);
}

//return the magnitude of the rational number
double RationalNumber::magnitude(){
    return numerator/denominator;
}

//print the rational number
void RationalNumber::print(){
    cout << "RationalNumber: " << numerator << " / " << denominator <<"\n";
}

//rational + rational
RationalNumber RationalNumber::operator + (const RationalNumber& arg)
{
    RationalNumber ret;
    //Find the denominator
    ret.denominator = gcd(denominator, arg.denominator);
    //Multiply the numerator by the denominator and then  add them together
    ret.numerator = ((ret.denominator / denominator) * numerator) + ((ret.denominator / arg.denominator) * arg.numerator);

    //Get a new denominator and numerator
    double nN = ret.numerator / gcd(ret.numerator, ret.denominator);
    double nD = ret.denominator / gcd(ret.numerator, ret.denominator);

    //If the fraction can be reduced, then do it
    if(fmod(nD,nN) == 0) {
        nD = nD / nN;
        nN =1;
    }

    //Negative fix
    if(nD < 0){
        nN = nN * -1;
        nD = nD * -1;
    }

    ret.numerator = nN;
    ret.denominator = nD;

    return ret;
}

//rational - rational
RationalNumber RationalNumber::operator - (const RationalNumber& arg)
{
    RationalNumber ret;
    //Find the denominator
    ret.denominator = gcd(denominator, arg.denominator);
    //Multiply the numerator by the denominator and then  subtract them
    ret.numerator = ((ret.denominator / denominator) * numerator) - ((ret.denominator / arg.denominator) * arg.numerator);

    //Get a new denominator and numerator
    double nN = ret.numerator / gcd(ret.numerator, ret.denominator);
    double nD = ret.denominator / gcd(ret.numerator, ret.denominator);
    
    //If the fraction can be reduced, then do it
    if(fmod(nD,nN) == 0) {
        nD = nD / nN;
        nN =1;
    }

    //Negative Fix
    if(nD < 0){
        nN = nN * -1;
        nD = nD * -1;
    }

    ret.numerator = nN;
    ret.denominator = nD;

    return ret;
}

//rational * rational
RationalNumber RationalNumber::operator * (const RationalNumber& arg)
{
    RationalNumber ret;
    //Just multuply
    ret.denominator = denominator * arg.denominator;
    ret.numerator = numerator * arg.numerator;

    //Get a new denominator and numerator
    double nN = ret.numerator / gcd(ret.numerator, ret.denominator);
    double nD = ret.denominator / gcd(ret.numerator, ret.denominator);
    
    //If the fraction can be reduced, then do it
    if(fmod(nD,nN) == 0) {
        nD = nD / nN;
        nN =1;
    }

    //Negative Fix
    if(nD < 0){
        nN = nN * -1;
        nD = nD * -1;
    }

    ret.numerator = nN;
    ret.denominator = nD;

    return ret;
}

//rational/rational
RationalNumber RationalNumber::operator / (const RationalNumber& arg)
{
    RationalNumber ret;

    //Multiply by inverting
    ret.denominator = denominator * arg.numerator;
    ret.numerator = numerator * arg.denominator;

    //Get a new denominator and numerator
    double nN = ret.numerator / gcd(ret.numerator, ret.denominator);
    double nD = ret.denominator / gcd(ret.numerator, ret.denominator);
    
    //If the fraction can be reduced, then do it
    if(fmod(nD, nN) == 0) {
        nD = nD / nN;
        nN =1;
    }

    //Negative Fix
    if(nD < 0){
        nN = nN * -1;
        nD = nD * -1;
    }

    ret.numerator = nN;
    ret.denominator = nD;

    return ret;
}

//set the rational number value
void RationalNumber::set_value (int numer, int denom)
{
    numerator = numer;
    denominator = denom;
}


// helper functions
int RationalNumber::gcd(int a, int b)
{
    int temp;
    while(a != 0) {
        temp = a;
        a = b%a;
        b = temp;
    }

    return b;
}
