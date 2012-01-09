#include "cpplot.hpp"
#include <utility>
int main(int argc, char* argv[]){
    using namespace cpplot;
    glut::init(argc, argv);
    std::vector<double> x(100),y(100);
    line_t ln = plot(x,y);
    for(int i=0;i<100;++i){
        ln << std::make_pair(0.1*i, std::sin(0.1*i));
        boost::this_thread::sleep(boost::posix_time::milliseconds(100));
    }
    //~ plot(x,y);

    while(true) boost::this_thread::yield();

    return 0;
}
