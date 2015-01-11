#include "cpplot.hpp"
#include <chrono>

bool is_run = true;

void keyboard(unsigned char key, int, int) {
    if(key == 'r'){ is_run = !is_run; }
}

int main(int argc, char* argv[]){
    using namespace cpplot;
    glut::init(argc, argv);
    figure("Animation")->keyboard_callback = keyboard;
    line_t p1 = subplot(2,1,1)->add<Line>();
    title("press r to run and stop");
    surface_t p2 = subplot(2,1,2)->add<Surface>();
    axis(-2,2,-2,2,0,1);
    double t=0;// time
    // Create test data
    int n=40;
    dvec x(n),y(n),z(n);
    x=linspace(-2,2,n);
    y=linspace(-2,2,n);

    dmat Z(n,dvec(n));
    double r2;

    while(true) {
        for(int i=0;i<n;++i){//y
            for(int j=0;j<n;++j){//x
                r2=x[j]*x[j]+y[i]*y[i];
                Z[i][j]=std::exp(-r2)*std::sin(2*r2+t)+0.5;
            }
        }
        for(int i=0;i<n;++i){
            z[i]=std::sin(3*x[i]+t);
        }
        //plot
        p1->plot(x,z);

        //mesh
        p2->mesh(x,y,Z);

        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if(is_run) t+= 0.1;
    }
    return 0;
}
