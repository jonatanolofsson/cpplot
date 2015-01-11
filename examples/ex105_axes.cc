#include "cpplot.hpp"
#include <thread>
#include <iostream>

int main(int argc, char* argv[]) {
    using namespace cpplot;
    glut::init(argc, argv);

    // create test data
    int n=100;
    float d=0.4;
    std::vector<double> x(n),y1(n),y2(n),y3(n),y4(n);
    for(int i=0;i<n;++i){
        x[i]=0.1*i;
        y1[i]=std::sin(x[i])+d*0;
        y2[i]=std::sin(x[i])+d*1;
        y3[i]=std::sin(x[i])+d*2;
        y4[i]=std::sin(x[i])+d*3;
    }

    subplot(2,3,1);
    plot(x,y1);
    // To add a title, labels
    title("Auto");
    xlabel("x label ");
    ylabel("y label ");

    // To change plot range
    subplot(2,3,2);
    axis(-5,15,-2,0.5);
    plot(x,y1);

    // To add grids
    subplot(2,3,3);
    plot(x,y1);
    grid(1);
    //or grid("off");

    // To delete axes
    subplot(2,3,4);
    plot(x,y1);
    axis(0);

    // To delete ticklabel
    subplot(2,3,5);
    plot(x,y1);
    ticklabel(0);

    // To put tick outside
    subplot(2,3,6);set("TickDir","out");
    plot(x,y1);

    while(true) std::this_thread::yield();
}
