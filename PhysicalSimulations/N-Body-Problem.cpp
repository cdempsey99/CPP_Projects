#include <iostream>
#include <cmath>
using namespace std;

//Calculates the distancce between body i and j
//n=4 bodies in total
double dist(double x[4][2], int i, int j){

    return sqrt(pow((x[i][0] - x[j][0]), 2.0)
                +(pow((x[i][1] - x[j][1]), 2.0)));
}

//Leapfrog update for positions x
void lf_x(double x[4][2], double v[4][2], double h) {

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 2; j++) {

            x[i][j] = x[i][j] + (h/2.0) * v[i][j];
        }
    }
}

//Leapfrog update for velocities v
void lf_v(double v[4][2], double a[4][2], double h) {

    for (int i = 0; i < 4; i++) {

        for (int j = 0; j < 2; j++) {

            v[i][j] = v[i][j] + h*a[i][j];
        }
    }
}

//Calculates the acceleration using Newton's Law (with G = 1)
void acceleration(double x[4][2],double a[4][2],double m[4]) {

        for (int i = 0; i < 4; i++){

            for (int j = 0; j < 2; j++){

                a[i][j] = 0;
            }
        }

        for (int i = 0; i < 4; i++) {

            for (int j = 0; j < 4; j++) {

                if (j != i) {

                    for (int k = 0; k < 2; k++) {

                        a[i][k] = a[i][k] - m[j] * (x[i][k] - x[j][k])/(pow(dist(x, i, j), 3.0));
                    }
                }
            }
        }
}


//X[i][j], V[i][j], and A[i][j] hold the positions, velocities and accelerations respectively
//of the ith body in the jth dimension
int main() {

    double t0 = 0;
    double t = t0;
    double h = 0.0001;

    double X[4][2] = {{-0.5, 0.1}, {-0.6, -0.2}, {0.5, 0.1}, {0.5, 0.4}};
    double V[4][2] = {{-0.85, 0.65}, {1.86, 0.75}, {-0.44, -1.5}, {1.15, -1.6}};
    double A[4][2] = {{0,0}, {0,0}, {0,0}, {0,0}};
    double M[4] = {2.5, 0.8, 0.9, 0.4};

    while (t < 4) {

        lf_x(X, V, h);
        acceleration(X, A, M);
        lf_v(V, A, h);
        lf_x(X, V, h);

        t += h;

        cout << "t = " << t << "\n";

        for (int i = 0; i < 4; i++) {
            for(int j =0; j < 2; j++) {
                cout << "Position of planet number " << i << " in the " << j << "th dim is " << X[i][j] << "\n";
            }
        }
    }
    return 0;
}


