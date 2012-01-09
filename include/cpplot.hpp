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


#ifndef _LIB_CPPLOT_
#define _LIB_CPPLOT_

#include "cpplot_common.hpp"

namespace cpplot {
    extern figure_t cf;


    figure_t figure(const std::string name);
    figure_t figure();
    figure_t figure(const int i);



    inline figure_t gcf() { return cf ? cf : figure(0); }
    inline axes_t subplot(const int m, const int n, const int p) { return gcf()->gcl()->subplot(m,n,p); };
    //void legend(string s,int N);

    // interface ///
    inline layer_t layer(const std::string name, const bool viz) { return gcf()->layer(name); }
    inline axes_t gca() { return gcf()->gcl()->gca(); }

    inline std::vector<double> linspace(const double min, const double max, int n) { return math::linspace<std::vector<double> >(min, max, n); }

    template<typename T>
    inline void set(const std::string v) { gca()->gco<T>()->set(v); }
    inline void set(const std::string v) { gca()->gco<Line>()->set(v); }
    template<typename T>
    inline void set(const float v) { gca()->gco<T>()->set(v); }
    inline void set(const float v) { gca()->gco<Line>()->set(v); }
    template<typename T>
    inline void set(const std::string p, const std::string v) { gca()->gco<T>()->set(p,v); }
    inline void set(const std::string p, const std::string v) { gca()->gco<Line>()->set(p,v); }
    template<typename T>
    inline void set(const std::string p, float v) { gca()->gco<T>()->set(p,v); }
    inline void set(const std::string p, float v) { gca()->gco<Line>()->set(p,v); }

    inline void axis(const double xMin, const double xMax, const double yMin, const double yMax) {
        gca()->axis(xMin, xMax, yMin, yMax);
    }
    inline void axis(const double xMin, const double xMax, const double yMin, const double yMax, const double zMin, const double zMax) {
        gca()->axis(xMin, xMax, yMin, yMax, zMin, zMax);
    }
    inline void axis(const std::string s) { gca()->axis(s); }
    inline void axis(const bool s) { gca()->axis(s); }
    inline void grid(const std::string s) { gca()->grid(s); }
    inline void grid(const bool s) { gca()->grid(s); }
    inline void ticklabel(const bool s) { gca()->ticklabel(s); }
    inline void title(const std::string s) { gca()->title(s); }
    inline void xlabel(const std::string s) { gca()->xlabel(s); }
    inline void ylabel(const std::string s) { gca()->ylabel(s); }
    inline void mouse_capture(const bool y) { gca()->mouse_capture(y); }

    inline void vertex(const double x, const double y) { gca()->gco<Line>()->vertex(x,y); }
    inline void vertex(const double x, const double y, const double z) { gca()->gco<Line>()->vertex(x,y,z); }

    inline line_t plot(const dvec& y) { return gca()->add<Line>()->plot(y); }
    inline line_t plot(const dvec& x,const dvec& y) { return gca()->add<Line>()->plot(x,y); }
    inline line_t plot(const dvec& x, const dvec& y, const dvec& z) { return gca()->add<Line>()->plot(x,y,z); }

    inline line_t semilogx(const dvec& x, const dvec& y) { return gca()->add<Line>()->semilogx(x,y); }
    inline line_t semilogy(const dvec& x, const dvec& y) { return gca()->add<Line>()->semilogy(x,y); }
    inline line_t loglog(const dvec& x, const dvec& y)   { return gca()->add<Line>()->loglog(x,y); }

    inline void vertex(const double x, const double y, const double ep, const double em)
        { gca()->gco<Line>()->vertex(x,y,ep,em); }
    inline void errorbar(const dvec& x, const dvec& y, const dvec& e)
        { gca()->gco<Line>()->errorbar(x,y,e); }
    inline void errorbar(const dvec& x, const dvec& y, const dvec& ep, const dvec& em)
        { gca()->gco<Line>()->errorbar(x,y,ep, em); }


    // Surface, Contour ///
    inline dmat peaks(int n) { return math::peaks(n); }

    inline surface_t surface(const dmat& Z) { return gca()->add<Surface>()->surface(Z); }
    inline surface_t surface(const dmat& Z, const dmat& C) { return gca()->add<Surface>()->surface(Z, C); }
    inline surface_t surface(const dmat& Z, const tcmat& C) { return gca()->add<Surface>()->surface(Z, C); }
    inline surface_t surface(const dvec& x, const dvec& y, const dmat& Z) { return gca()->add<Surface>()->surface(x,y,Z); }
    inline surface_t surface(const dvec& x, const dvec& y, const dmat& Z, const dmat& C) { return gca()->add<Surface>()->surface(x,y,Z,C); }
    inline surface_t surface(const dvec& x, const dvec& y, const dmat& Z, const tcmat& C) { return gca()->add<Surface>()->surface(x,y,Z); }
    inline surface_t surface(const dmat& X, const dmat& Y, const dmat& Z) { return gca()->add<Surface>()->surface(X,Y,Z); }
    inline surface_t surface(const dmat& X, const dmat& Y, const dmat& Z, const dmat& C) { return gca()->add<Surface>()->surface(X,Y,Z,C); }
    inline surface_t surface(const dmat& X, const dmat& Y, const dmat& Z, const tcmat& C) { return gca()->add<Surface>()->surface(X,Y,Z,C); }

    inline surface_t pcolor(const dmat& C) { return gca()->add<Surface>()->pcolor(C); }
    inline surface_t pcolor(const tcmat& C) { return gca()->add<Surface>()->pcolor(C); }
    inline surface_t pcolor(const dvec& x, const dvec& y, const dmat& C) { return gca()->add<Surface>()->pcolor(x,y,C); }
    inline surface_t pcolor(const dvec& x, const dvec& y, const tcmat& C) { return gca()->add<Surface>()->pcolor(x,y,C); }
    inline surface_t pcolor(const dmat& X, const dmat& Y, const dmat& C) { return gca()->add<Surface>()->pcolor(X,Y,C); }
    inline surface_t pcolor(const dmat& X, const dmat& Y, const tcmat& C) { return gca()->add<Surface>()->pcolor(X,Y,C); }

    inline surface_t contour(const dmat& Z) { return gca()->add<Surface>()->contour(Z); }
    inline surface_t contour(const dmat& Z,int n) { return gca()->add<Surface>()->contour(Z, n); }
    inline surface_t contour(const dmat& Z, const dvec& v) { return gca()->add<Surface>()->contour(Z,v); }
    inline surface_t contour(const dvec& x, const dvec& y, const dmat& Z) { return gca()->add<Surface>()->contour(x,y,Z); }
    inline surface_t contour(const dvec& x, const dvec& y, const dmat& Z, const int n) { return gca()->add<Surface>()->contour(x,y,Z,n); }
    inline surface_t contour(const dvec& x, const dvec& y, const dmat& Z, const dvec& v) { return gca()->add<Surface>()->contour(x,y,Z,v); }

    inline surface_t mesh(const dvec& x, const dvec& y, const dmat& Z) { return gca()->add<Surface>()->mesh(x,y,Z); }
    inline surface_t surf(const dvec& x, const dvec& y, const dmat& Z) { return gca()->add<Surface>()->surf(x,y,Z); }

    inline void shading(const std::string c) { gca()->gco<Surface>()->shading(c); }

    // Patch ///
    inline patch_t patch(const dmat& X, const dmat& Y) { return gca()->add<Patch>()->patch(X,Y); }
    inline patch_t patch(const dmat& X, const dmat& Y, const dvec& C) { return gca()->add<Patch>()->patch(X,Y,C); }
    inline patch_t patch(const dmat& X, const dmat& Y, const tcvec& C) { return gca()->add<Patch>()->patch(X,Y,C); }
    inline patch_t patch(const dmat& X, const dmat& Y, const dmat& Z) { return gca()->add<Patch>()->patch(X,Y,Z); }
    inline patch_t patch(const dmat& X, const dmat& Y, const dmat& Z, const dvec& C) { return gca()->add<Patch>()->patch(X,Y,Z,C); }
    inline patch_t patch(const dmat& X, const dmat& Y, const dmat& Z, const tcvec& C) { return gca()->add<Patch>()->patch(X,Y,Z,C); }

    inline patch_t bar(const dvec& y) { return gca()->add<Patch>()->bar(y); }
    inline patch_t bar(const dvec& y, const float width) { return gca()->add<Patch>()->bar(y, width); }
    inline patch_t bar(const dvec& x, const dvec& y) { return gca()->add<Patch>()->bar(x,y); }
    inline patch_t bar(const dvec& x, const dvec& y, const float width) { return gca()->add<Patch>()->bar(x,y,width); }

    // Text ///
    //TODO: more fonts
    inline text_t text(const double x, const double y, const std::string s) { return gca()->add<Text>()->text(x,y,s); }

    inline axes_t colorbar() { return gca()->colorbar(); }
    inline void gray() { gca()->gray(); };
    inline void jet() { gca()->jet(); }
    inline void hsv() { gca()->hsv(); }
    inline void hot() { gca()->hot(); }
    inline void cool() { gca()->hot(); }
    inline void spring() { gca()->spring(); }
    inline void summer() { gca()->summer(); }
    inline void autumn() { gca()->autumn(); }
    inline void winter() { gca()->winter(); }


    // print ///
    inline void print(const std::string name = "out.eps") { if(cf) cf->print(name); }

    inline void operator<<(line_t ln, const std::pair<double, double> p) { ln->vertex(p.first, p.second); }
    inline void operator<<(axes_t a, const std::pair<double, double> p) { a->gco<Line>()->vertex(p.first, p.second); }
    inline void operator<<(layer_t a, const std::pair<double, double> p) { a->gca()->gco<Line>()->vertex(p.first, p.second); }
    inline void operator<<(figure_t a, const std::pair<double, double> p) { a->gca()->gco<Line>()->vertex(p.first, p.second); }
}
#endif
