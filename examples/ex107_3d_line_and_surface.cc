#include "cpplot.hpp"
int main(int argc, char* argv[]){
    using namespace cpplot;
    glut::init(argc, argv);

    // Prepare test data
    int n=50;
    std::vector<double> x,y,z;
    x=linspace(-2,2,n);
    y=linspace(-2,2,n);
    std::vector< std::vector< double > > Z(n, std::vector<double>(n)),C(n,std::vector<double>(n));
    for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
        Z[i][j]=sin(3*x[j])+sin(3*y[i])+0.5;
    }
    }

    // To set current color map, use following commands
    //hsv();
    spring();

    // To generate 3D surface plot
    surface(x,y,Z);

    // Another test data
    n=300;
    x.resize(n);
    y.resize(n);
    z.resize(n);
    double t;
    for(int i=0;i<n;++i){
    t=0.1*i;
    x[i]=sin(t);
    y[i]=cos(t);
    z[i]=0.1*t;
    }

    // To plot 3D line
    plot(x,y,z);

    // To color this line
    set("r");set(3);

    // To add colorbar
    colorbar();
    while(true) std::this_thread::yield();
    return 0;
}
