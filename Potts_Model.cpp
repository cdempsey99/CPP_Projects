#include <iostream>
#include <vector>
#include <cstdlib>
#include <cmath>
#include <fstream>
#include <algorithm>
#include <time.h>
using namespace std;

template <class T>
class Field
{
  private:
    int 			nx_;
    int 			ny_;
    std::vector<T>		data_;

    int index_(int x, int y) const { return x + nx_*y; }
  public:
    Field(int nx, int ny, int q) : nx_(nx), ny_(ny), data_(nx_*ny_)
    {
      int n=nx_*ny_;
      for (int t=0;t<n;t++) data_[t] = rand()%q;
    }

    T& operator() (int x, int y)       { return data_[index_(x,y)]; }
    T  operator() (int x, int y) const { return data_[index_(x,y)]; }

    int nx() const {return nx_;}
    int ny() const {return ny_;}
};

//A function to calculate the change in spin after a change in configuration:
int ds(Field<int> grid, int x, int y, int sigma, int n) {
    int xp = (x+1)%n;//Define the nearest neighbouring grid points
    int xm = (x+n-1)%n;
    int yp = (y+1)%n;
    int ym = (y+n-1)%n;

    int d_S=0;//Initialise the 'local' action to zero

    if (sigma != grid(xp, y)) {d_S++;} //Every neighbouring bond that is frustrated contributes 1 to the action
    if (sigma != grid(xm, y)) {d_S++;}
    if (sigma != grid(x, yp)) {d_S++;}
    if (sigma != grid(x, ym)) {d_S++;}

    return d_S;
}

//Appply the metropolis algorithm to each grid point once:
Field<int> update_metropolis(Field<int> grid, double beta, int n, int q) {
    for (int j=0; j<n; j++) {
        for (int i=0; i<n; i++) {
            int sigma_new = rand()%q;
            int s_0 = ds(grid, i, j, grid(i,j), n);
            int s_1 = ds(grid, i, j, sigma_new, n);

            if (s_1 - s_0 <= 0) {grid(i,j) = sigma_new;}
            if (s_1 - s_0 > 0) {
                double ran = ((double) rand()/(RAND_MAX));
                if(ran <= exp(-beta * (s_1 - s_0))) {
                        grid(i,j) = sigma_new;
                }
            }
        }
    }
    return grid;
}

//Function to calculate the magnetisation of the grid
double magnetisation(Field<int> grid, int n, int q) {
    vector<int> a(q); //The entries of this vector will contain the number of points at each state
    for (int l=0; l<q; l++) {
        for (int j=0; j<n; j++) {
            for (int i=0; i<n; i++){
                    if (grid(i,j) == l) {a[l]++;}
            }
        }
    }
    int counter=a[0];
    for (int l=0; l<q-1; l++) {  //to calculate the maximum of the vector elements of a[]:
        if (a[l+1] > counter) {counter = a[l+1];}
    }
    double f_s = double(counter/(pow(n,2.0)));//Max value of the fraction of sigma over the no. of grid points, f(sigma)
    double m = (q*f_s - 1)/(q-1); //Magnetisation
    return m;
}

//This fn prints the values of <M> for various values of Beta
void graph(Field<int> grid, int n, int q, int k) {
     for (double b=0.45; b<1.56; b += 0.005) {
            double b = 1.0;
            double m_cumulative = 0.0;
            double M = 0.0;
                for (int i=1; i<k+1; i++) {
                    grid = update_metropolis(grid, b, n, q); //Apply the metropolis algorithm to the whole grid
                    m_cumulative += magnetisation(grid, n, q);
                    }
            M = m_cumulative/double(k);//Calculate the running average of the magnetisation, M
            cout << b << " " << M << "\n";
     }
}

int main() {
    srand(time(NULL));
    int q = 4;
    int n = 20; //20x20 grid
    int k = 700; //number of iterations
    Field<int> grid(n,n,q);

//Produce the required graph:
    graph(grid, n, q, k);

	cout << ((double) rand()/(RAND_MAX)) << "\n";
    return 0;
}
