#include <iostream>
#include <vector>
#include <Windows.h>
using std::cout;
using namespace std;

class Field
{
  private:
    int 			qx_;	// This is nx+1, the number of grid
                            // points in the x direction when
                            // the range is sliced into nx parts
    int 			qy_;
    std::vector<double>		data_;

    int index_(int x, int y) const { return x + qx_*y; }
  public:
    Field(int nx, int ny) : qx_(nx+1), qy_(ny+1), data_(qx_*qy_)
    {
      int N=qx_*qy_;
      for (int t=0;t<N;t++) data_[t] = 0.0;
    }

    double  operator() (int x, int y) const { return data_[index_(x,y)]; }
    double& operator() (int x, int y)       { return data_[index_(x,y)]; }
};

//Checks if the fn phi is being evaluated at either the line B or on the square A,
//returns true for these cases and false otherwise
bool Check(Field phi, int i, int j, int n){
    if( (i>=int(0.2*n) && i<=int(0.4*n) && j==int(0.1*n)) ||(i>=int(0.2*n) && i<=int(0.4*n) && j==int(0.3*n)) ||
       (i==int(0.2*n) && j>=int(0.1*n) && j<=int(0.3*n)) ||(i==int(0.4*n) && j>=int(0.1*n) && j<=int(0.3*n)) ||
       (i == int(0.8*n) && j>=int(0.3*n) && j<=int(0.7*n)) || (i>=int(0.5*n) && i<=int(0.8*n) && j==int(0.7*n)) ){
        return true;
        }
    else {
        return false;
        }
}

//Approximates the partial derivative of phi in the y dirn at a grid point (i,j)
double Dphi_Dy(Field phi, int i, int j, int n) {
    return (phi(i, j+1) - phi(i, j-1))*double(n)*0.5;
}

int main() {
//Initialise values and create and instance of the field
    int n = 100;
    int k = 1000; //Number of iterations of the Laplace solver
    Field phi(n,n);
    double w = 1.9;// SOR parameter, optimised value
    double t1, t2;//Involved in plotting the convergence of phi vs iteration number

    for (int s = 0; s < k; s++) {
            double t1 = phi(0.2*n, 0.7*n);

        for (int j = 1; j < n-1; j++) {

            for (int i = 1; i < n-1; i++) {

                if (Check(phi, i, j, n) == true) {
                    if (i >= 0.45*n) {phi(i,j) = -1.0;}
                    if (i <= 0.45*n) {phi(i,j) = 2.0;}
                }
                if (Check(phi, i, j ,n) == false) {
                    phi(i,j) = (1-w)* phi(i,j) + w*0.25*(phi(i-1,j) + phi(i+1,j) + phi(i,j-1) + phi(i,j+1));
                }
            }
        }
        //This was used for the convergence of phi plot
        /*double t2 = phi(0.2*n, 0.7*n);
    cout << s << " " << abs(t2 - t1) << "\n";*/
}

//Showing the field values at the end to make a heatmap
/*for (int v = 0; v < n; v++) {
    for (int u = 0; u < n; u++){cout << phi(u,v) << " ";}
    cout << "\n";
*/

//Find th derivative at (0.2n, 0.7n):
cout << Dphi_Dy(phi, 0.2*n, 0.7*n, n) << "\n";

//cout << phi(int(0.2*n), int(0.7*n)) << "\n";
  return 0;
}
