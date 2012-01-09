/****************************************************************************
Copyright (c) 2011 Jonatan Olofsson All Rites Reversed
License: Gnu Public license (GPL) v3
* Author: Jonatan Olofsson (jonatan.olofsson@gmail.com)
* Version: 0.1
* Based on
Author: Yuichi Katori (yuichi.katori@gmail.com)
Project:MATPLOT++ (MATLAB-like plotting tool in C++).
Version:0.3.13
****************************************************************************/

#include "cpplot.hpp"
#include <algorithm>
#include <cstdio>
#include <boost/thread.hpp>
#include <iostream>

namespace cpplot {
    figures_t figures;
    figure_t cf;
    typedef std::map<std::string, figure_t> figuremap;
    figuremap named_figures;

    figure_t figure(const std::string name) {
        figure_t f = named_figures[name];
        if(f == NULL) {
            named_figures[name] = f = figure(figures.size());
            f->window_name = name;
        }
        return f;
    }

    int max_figure_number = 0;
    figure_t figure() {
        return figure(max_figure_number + 1);
    }

    figure_t figure(const int i) {
        if(i > max_figure_number) max_figure_number = i;
        cf = figures[i];
        if(cf == NULL) {
            figure_t p(new figure_t_t());
            cf = p;
            glut::register_figure(p);
            figures.insert(figures_t::value_type(i,p));
            return cf;
        } else {
            return cf;
        }
    }


    //~ void run_free();
    //~ class cpplotrun {
        //~ public:
            //~ boost::thread cpplot_thread;
            //~ boost::barrier* init_barrier;
            //~ cpplotrun() {
                //~ init_barrier = new boost::barrier(2);
                //~ std::cout << "cpplot init.." << std::endl;
                //~ cpplot_thread = boost::thread(run_free);
                //~ init_barrier->wait();
                //~ std::cout << "cpplot initialized!" << std::endl;
            //~ }
            //~ ~cpplotrun() { std::cout << "Exiting, joining thread.." << std::endl; cpplot_thread.join(); }
    //~ } _cpplotinit_;
//~
    //~ void run_free() {
        //~ std::cout << "Running free!" << std::endl;
        //~ int argc = 0;
        //~ char* argv[0];
        //~ glut::init(argc, argv);
        //~ _cpplotinit_.init_barrier->wait();
        //~ std::cout << "Spinning..." << std::endl;
        //~ glut::spin();
    //~ }
}
