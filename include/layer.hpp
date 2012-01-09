/**
 * Copyright 2011, 2012 Jonatan Olofsson
 *
 * This file is part of cpplot.
 *
 * cpplot is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * cpplot is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with cpplot.  If not, see <http://www.gnu.org/licenses/>.
 */

/****************************************************************************
License: Gnu Public license (GPL) v3
* Author: Jonatan Olofsson (jonatan.olofsson@gmail.com)
* Version: 0.1
* Based on
Author: Yuichi Katori (yuichi.katori@gmail.com)
Project:MATPLOT++ (MATLAB-like plotting tool in C++).
Version:0.3.13
****************************************************************************/

#ifndef _CPPLOT_LAYER_HPP_
#define _CPPLOT_LAYER_HPP_

#include "cpplot_common.hpp"
#include <boost/timer.hpp>

namespace cpplot {
    class layer_t_t : public boost::enable_shared_from_this<layer_t_t>, public boost::noncopyable {
        private:
            axes_t ca, selected_axes;
            bool visible;
            float xButtonDown, yButtonDown;// last clicked mouse position

        public:
            boost::timer time_clicked;
            std::string layername;
            figure_t figure;

            axess_t axes;
            layer_t_t(const figure_t fig, const std::string name, const bool viz)
                :   visible(viz),
                    figure(fig),
                    layername(name)
                {}

            void draw();
            axes_t subplot(const int m, const int n, const int p);
            axes_t gca() { return ca ? ca : subplot(1,1,1); }
            figure_t gcf() { return figure; }

            void toggle_visibility();
            void set_visibility(bool v);
            bool is_visible() { return visible; }
            const bool mouse(const int button, const int state, const int x, const int y);
            const bool motion(const int x, const int y);
            //~ const bool passivemotion(const int x, const int y);

            // interface ///
            template<typename T>
            void set(const std::string v) { gca()->gco<T>()->set(v); }
            void set(const std::string v) { gca()->gco<Line>()->set(v); }
            template<typename T>
            void set(const float v) { gca()->gco<T>()->set(v); }
            void set(const float v) { gca()->gco<Line>()->set(v); }
            template<typename T>
            void set(const std::string p, const std::string v) { gca()->gco<T>()->set(p,v); }
            void set(const std::string p, const std::string v) { gca()->gco<Line>()->set(p,v); }
            template<typename T>
            void set(const std::string p, float v) { gca()->gco<T>()->set(p,v); }
            void set(const std::string p, float v) { gca()->gco<Line>()->set(p,v); }

            void axis(const double xMin, const double xMax, const double yMin, const double yMax) {
                gca()->axis(xMin, xMax, yMin, yMax);
            }
            void axis(const double xMin, const double xMax, const double yMin, const double yMax, const double zMin, const double zMax) {
                gca()->axis(xMin, xMax, yMin, yMax, zMin, zMax);
            }
            void axis(const std::string s) { gca()->axis(s); }
            void axis(const bool s) { gca()->axis(s); }
            void grid(const std::string s) { gca()->grid(s); }
            void grid(const bool s) { gca()->grid(s); }
            void ticklabel(const bool s) { gca()->ticklabel(s); }
            void title(const std::string s) { gca()->title(s); }
            void xlabel(const std::string s) { gca()->xlabel(s); }
            void ylabel(const std::string s) { gca()->ylabel(s); }
            void mouse_capture(const bool y) { gca()->mouse_capture(y); }

            void vertex(const double x, const double y) { gca()->gco<Line>()->vertex(x,y); }
            void vertex(const double x, const double y, const double z) { gca()->gco<Line>()->vertex(x,y,z); }

            line_t plot(const dvec& y) { return gca()->add<Line>()->plot(y); }
            line_t plot(const dvec& x,const dvec& y) { return gca()->add<Line>()->plot(x,y); }
            line_t plot(const dvec& x, const dvec& y, const dvec& z) { return gca()->add<Line>()->plot(x,y,z); }

            line_t semilogx(const dvec& x, const dvec& y) { return gca()->add<Line>()->semilogx(x,y); }
            line_t semilogy(const dvec& x, const dvec& y) { return gca()->add<Line>()->semilogy(x,y); }
            line_t loglog(const dvec& x, const dvec& y)   { return gca()->add<Line>()->loglog(x,y); }

            void vertex(const double x, const double y, const double ep, const double em)
                { gca()->gco<Line>()->vertex(x,y,ep,em); }
            void errorbar(const dvec& x, const dvec& y, const dvec& e)
                { gca()->gco<Line>()->errorbar(x,y,e); }
            void errorbar(const dvec& x, const dvec& y, const dvec& ep, const dvec& em)
                { gca()->gco<Line>()->errorbar(x,y,ep, em); }


            // Surface, Contour ///
            surface_t surface(const dmat& Z) { return gca()->add<Surface>()->surface(Z); }
            surface_t surface(const dmat& Z, const dmat& C) { return gca()->add<Surface>()->surface(Z, C); }
            surface_t surface(const dmat& Z, const tcmat& C) { return gca()->add<Surface>()->surface(Z, C); }
            surface_t surface(const dvec& x, const dvec& y, const dmat& Z) { return gca()->add<Surface>()->surface(x,y,Z); }
            surface_t surface(const dvec& x, const dvec& y, const dmat& Z, const dmat& C) { return gca()->add<Surface>()->surface(x,y,Z,C); }
            surface_t surface(const dvec& x, const dvec& y, const dmat& Z, const tcmat& C) { return gca()->add<Surface>()->surface(x,y,Z); }
            surface_t surface(const dmat& X, const dmat& Y, const dmat& Z) { return gca()->add<Surface>()->surface(X,Y,Z); }
            surface_t surface(const dmat& X, const dmat& Y, const dmat& Z, const dmat& C) { return gca()->add<Surface>()->surface(X,Y,Z,C); }
            surface_t surface(const dmat& X, const dmat& Y, const dmat& Z, const tcmat& C) { return gca()->add<Surface>()->surface(X,Y,Z,C); }

            surface_t pcolor(const dmat& C) { return gca()->add<Surface>()->pcolor(C); }
            surface_t pcolor(const tcmat& C) { return gca()->add<Surface>()->pcolor(C); }
            surface_t pcolor(const dvec& x, const dvec& y, const dmat& C) { return gca()->add<Surface>()->pcolor(x,y,C); }
            surface_t pcolor(const dvec& x, const dvec& y, const tcmat& C) { return gca()->add<Surface>()->pcolor(x,y,C); }
            surface_t pcolor(const dmat& X, const dmat& Y, const dmat& C) { return gca()->add<Surface>()->pcolor(X,Y,C); }
            surface_t pcolor(const dmat& X, const dmat& Y, const tcmat& C) { return gca()->add<Surface>()->pcolor(X,Y,C); }

            surface_t contour(const dmat& Z) { return gca()->add<Surface>()->contour(Z); }
            surface_t contour(const dmat& Z,int n) { return gca()->add<Surface>()->contour(Z, n); }
            surface_t contour(const dmat& Z, const dvec& v) { return gca()->add<Surface>()->contour(Z,v); }
            surface_t contour(const dvec& x, const dvec& y, const dmat& Z) { return gca()->add<Surface>()->contour(x,y,Z); }
            surface_t contour(const dvec& x, const dvec& y, const dmat& Z, const int n) { return gca()->add<Surface>()->contour(x,y,Z,n); }
            surface_t contour(const dvec& x, const dvec& y, const dmat& Z, const dvec& v) { return gca()->add<Surface>()->contour(x,y,Z,v); }

            surface_t mesh(const dvec& x, const dvec& y, const dmat& Z) { return gca()->add<Surface>()->mesh(x,y,Z); }
            surface_t surf(const dvec& x, const dvec& y, const dmat& Z) { return gca()->add<Surface>()->surf(x,y,Z); }

            void shading(const std::string c) { gca()->gco<Surface>()->shading(c); }

            // Patch ///
            patch_t patch(const dmat& X, const dmat& Y) { return gca()->add<Patch>()->patch(X,Y); }
            patch_t patch(const dmat& X, const dmat& Y, const dvec& C) { return gca()->add<Patch>()->patch(X,Y,C); }
            patch_t patch(const dmat& X, const dmat& Y, const tcvec& C) { return gca()->add<Patch>()->patch(X,Y,C); }
            patch_t patch(const dmat& X, const dmat& Y, const dmat& Z) { return gca()->add<Patch>()->patch(X,Y,Z); }
            patch_t patch(const dmat& X, const dmat& Y, const dmat& Z, const dvec& C) { return gca()->add<Patch>()->patch(X,Y,Z,C); }
            patch_t patch(const dmat& X, const dmat& Y, const dmat& Z, const tcvec& C) { return gca()->add<Patch>()->patch(X,Y,Z,C); }

            patch_t bar(const dvec& y) { return gca()->add<Patch>()->bar(y); }
            patch_t bar(const dvec& y, const float width) { return gca()->add<Patch>()->bar(y, width); }
            patch_t bar(const dvec& x, const dvec& y) { return gca()->add<Patch>()->bar(x,y); }
            patch_t bar(const dvec& x, const dvec& y, const float width) { return gca()->add<Patch>()->bar(x,y,width); }

            // Text ///
            //TODO: more fonts
            text_t text(const double x, const double y, const std::string s) { return gca()->add<Text>()->text(x,y,s); }

            axes_t colorbar() { return gca()->colorbar(); }
            void gray() { gca()->gray(); };
            void jet() { gca()->jet(); }
            void hsv() { gca()->hsv(); }
            void hot() { gca()->hot(); }
            void cool() { gca()->hot(); }
            void spring() { gca()->spring(); }
            void summer() { gca()->summer(); }
            void autumn() { gca()->autumn(); }
            void winter() { gca()->winter(); }
    };
}
#endif
