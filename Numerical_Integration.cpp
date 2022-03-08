#include <iostream>
#include <cmath>
using namespace std;

//Define the two first order ODEs from our original 2nd order ODE:
double f1(double v) {
    return v;
}

double f2(double x, double t) {
    return -pow(x,3.0)*exp(-(pow(x,2.0))/2.0 - t/20.0);
}

//Runs the RK4 scheme, for x and v = dx/dt, given step size h and end points a and b,
// and initial values v_0, x_0 and t_0 and returns the value of x at the end of the time interval:
double RK_x(double v_0, double x_0, double t_0, double h, double a, double b) {

    double k1, k2, k3, k4, l1, l2, l3, l4;
    double n = (b-a)/(double(h));

    double v = v_0;
    double x = x_0;
    double t = t_0;

    for (int i = 0; i < n; i++) {

        k1 = h*f1(v);
        l1 = h*f2(x,t);

        k2 = h*f1(v + l1/2.0);
        l2 = h*f2(x + k1/2.0, t + h/2.0);

        k3 = h*f1(v + l2/2.0);
        l3 = h*f2(x + k2/2.0, t + h/2.0);

        k4 = h*f1(v + l3/2.0);
        l4 = h*f2(x + k3/2.0, t + h/2.0);

        x += (k1 + (2 * k2) + (2 * k3) + k4)/6.0;
        v += (l1 + (2 * l2) + (2 * l3) + l4)/6.0;
        t += h;
    }
    return x;
}

//This function finds x(10) using the Runge Kutta and subtracts the true value of x(10) = 1,
//hence this is the function whose roots need to be found, by the bisection method:
double F(double v_0, double x_0, double t_0, double h, double a, double b, double x_f) {
    return RK_x(v_0, x_0, t_0, h, a, b) - x_f;
}

//This function plots the F function (the x(10) found by the Runge Kutta algorithm minus 1) for a range of
//v(0) values (from s1 to s2))
void guess(double s1, double s2, double x_0,double t_0, double h, double a, double  b, double x_f) {

    double s = s1;
    double H = 0.01;

    while (s < s2) {

        cout << s << " " << F(s, x_0, t_0, h, a, b, x_f) << "\n";
        s += H;
    }
}

int main() {

    //Initialise the step size, integration range for the Runge Kutta, and the intial values of x and t:
    double h = 0.01;
    double a = 0.0;
    double b = 10.0;
    double x_f = 1.0;
    double t_0 = 0.0;
    double x_0 = 0.0;

    //Plot a range of v(0) = c values at the beginning to get a sense of where the zeros are:
    guess(-2.0, 2.0, x_0, t_0, h, a, b, x_f);

    //We choose these as a small interval around the approximate roots of the function plotted by guess()
    double c_l = 1.8;
    double c_h = 2.0;

    double tol = 1.0e-8;

    //Insert these guesses into the bisection method code:
    if (F(c_l, x_0, t_0, h, a, b, x_f) * F(c_h, x_0, t_0, h, a, b, x_f) > 0) {
        cout << "The given guesses for c_l and c_h do not enclose a root\n";
    }
    else

        while (abs(c_h - c_l) > tol) {

            double c_m  = 0.5 * (c_h + c_l);

            if (F(c_m, x_0, t_0, h, a, b, x_f) == 0.0)
                break;

            else if (F(c_m, x_0, t_0, h, a, b, x_f) * F(c_l, x_0, t_0, h, a, b, x_f) < 0)
                c_h = c_m;
            else
                c_l = c_m;

        cout << (c_l + c_h)/2.0 << "\n";
        }
    return 0;
}
