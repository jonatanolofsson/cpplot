#include "cpplot.hpp"
int main(int argc,char* argv[]){
    using namespace cpplot;
    glut::init(argc, argv);
    std::vector<double> x(100),y(100);
    for(int i=0;i<100;++i){
    x[i]=0.1*i;
    y[i]=sin(x[i]);
    }
    plot(x,y);

    while(true) std::this_thread::yield();
}
