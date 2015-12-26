#include <stdio.h>
#include <stdlib.h>
#include <math.h>

/*
 * netid: tdubey3
 * partners: hqu5, stang17
 *
 * This program finds the roots of a polynomial function in two steps. The first
 * step involves using Budans theorem to find the number of roots in a function.
 * The second step uses Halley's method to actually find the value of the roots
 * by using the derivatives and double derivatives of the function. The program
 * then prints out the found roots, or lack thereof.
 *
 */

double abs_double(double y)
{
    //Change this to return the absolute value of y i.e |y|
    return (double)abs(y);
}

double fx_val(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the polynomial at the value x
    return a*pow(x,4)+b*pow(x,3)+c*pow(x,2)+d*x+e;
}

double fx_dval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the derivative of the polynomial at the value x
    return 4*a*pow(x,3)+3*b*pow(x,2)+2*c*pow(x,1)+d;
}

double fx_ddval(double a, double b, double c, double d, double e, double x)
{
    //Change this to return the value of the double derivative of the polynomial at the value x
    return 12*a*pow(x,2)+6*b*pow(x,1)+2*c;
}


double newrfind_halley(double a, double b, double c, double d, double e, double x)
{
    double previous = -1000, current = x, next = 0.0, i = 0;
    while(abs_double(current-previous) > 0.00001 && i <= 10000){
                next = current - ((2*fx_val(a,b,c,d,e,current)*fx_dval(a,b,c,d,e,current))/((2*pow(fx_dval(a,b,c,d,e,current),2))-(fx_val(a,b,c,d,e,current)*fx_ddval(a,b,c,d,e,current))));
                //next = (current - (2*fx_val(a,b,c,d,e,current)*fx_dval(a,b,c,d,e,current)/(2*pow(fx_dval(a,b,c,d,e,current),2)-fx_val(a,b,c,d,e,current)*fx_ddval(a,b,c,d,e,current))));
                printf("%lf\n", next);
                previous = current;
                current = next;
                i = i+1;
    }
    if( i >= 10000) {
        printf("No roots found.\n"); //If it diverges, print this
    }
    return current;
}
int rootbound(double a, double b, double c, double d, double e, double r, double l)
{
    double y1, y2, y3, y4, y5, x1, x2, x3, x4, x5;
    int vl, vr;
    y1 = a;
    y2 = (4*a*l)+b;
    y3 = (6*a*pow(l,2))+(3*b*l)+c;
    y4 = (4*a*pow(l,3))+(3*b*pow(l,2))+(2*c*l)+d;
    y5 = (a*pow(l,4))+(b*pow(l,3))+(c*pow(l,3))+(d*l)+e;

    vl = ((y1*y2)<0)+((y2*y3)<0)+((y3*y4)<0)+((y4*y5)<0); //find number of sign changes

    x1 = a;
    x2 = (4*a*r)+b;
    x3 = (6*a*pow(r,2))+(3*b*r)+c;
    x4 = (4*a*pow(r,3))+(3*b*pow(r,2))+(2*c*r)+d;
    x5 = (a*pow(r,4))+(b*pow(r,3))+(c*pow(r,3))+(d*r)+e;

    vr = ((x1*x2)<0)+((x2*x3)<0)+((x3*x4)<0)+((x4*x5)<0);

    return vl-vr;
}

int main(int argc, char **argv){
	double a, b, c, d, e, l, r;
	FILE *in;

	if (argv[1] == NULL) {
		printf("You need an input file.\n");
		return -1;
	}
	in = fopen(argv[1], "r");
	if (in == NULL)
		return -1;
	fscanf(in, "%lf", &a);
	fscanf(in, "%lf", &b);
	fscanf(in, "%lf", &c);
	fscanf(in, "%lf", &d);
	fscanf(in, "%lf", &e);
	fscanf(in, "%lf", &l);
	fscanf(in, "%lf", &r);

    //The values are read into the variable a, b, c, d, e, l and r.
    //You have to find the bound on the number of roots using rootbound function.
    //If it is > 0 try to find the roots using newrfind function.
    //You may use the fval, fdval and fddval funtions accordingly in implementing the halleys's method.

    if(rootbound(a,b,c,d,e,r,l) == 0){
        printf("The polynomial has no roots in the given interval\n");
    } else {
        double i;
          for(i =l; i<= r; i+=.5) { // run halley's for as many times as there is r-i/.5
            double rootFound = newrfind_halley(a,b,c,d,e,i);
            printf("Root found: %lf\n", rootFound);
        }
    }

    fclose(in);

    return 0;
}
