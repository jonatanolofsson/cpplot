#include "cpplot.hpp"
int main(int argc, char* argv[]){
    using namespace cpplot;
    glut::init(argc, argv);
    int n=100;
    std::vector<double> x(n),y1(n),y2(n),y3(n),y4(n);

    // Create test data
    for(int i=0;i<n;++i){
    x[i]=10.0*i/(n-1);
    y1[i]=sin(x[i]);
    y2[i]=sin(3*x[i]);
    y3[i]=cos(x[i]);
    y4[i]=cos(3*x[i]);
    }

    // To create a layer
    layer("first",1);
    title("move the mouse cursor to left window edge.");

    // To create multiple lines in one graph
    //~ plot(x,y1);
    //~ plot(x,y2);
    plot(x,y3);
    plot(x,y4);

    // To create multiple layer and a graph in each layer
    layer("layer 1",0);
    plot(x,y1);

    layer("layer 2",0);
    plot(x,y2);

    // To create multiple graphs in a layer
    layer("multiple graphs in the layer",0);
    subplot(2,2,1);
    plot(x,y1);

    subplot(2,2,2);
    plot(x,y2);

    subplot(2,2,3);
    plot(x,y3);

    subplot(2,2,4);
    plot(x,y4);
    while(true) std::this_thread::yield();
    return 0;
}
