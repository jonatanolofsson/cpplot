#include "cpplot.hpp"
int main(int argc, char* argv[]){
    using namespace cpplot;
    glut::init(argc, argv);
    // Prepare test data
    int n=100;
    std::vector<double> x,y,z;
    x=linspace(-2,2,n);
    y=linspace(-2,2,n);
    std::vector< std::vector< double > > Z(n,std::vector<double>(n)),C(n,std::vector<double>(n));
    for(int i=0;i<n;++i){
    for(int j=0;j<n;++j){
        Z[i][j]=sin(3*x[j])+sin(3*y[i])+0.5;
    }
    }
    // To add contour plot
    //contour(Z);

    // To set current color map, use following commands
    //hsv();
    jet();

    // To generate pseudo color plot:
    pcolor(Z);

    // To delete edge lines:
    set("EdgeColor","none");

    // To add color bar
    colorbar();
    while(true) std::this_thread::yield();
    return 0;
}
