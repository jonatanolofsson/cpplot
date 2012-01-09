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

#ifndef _CPPLOT_AXES_HPP_
#define _CPPLOT_AXES_HPP_

#include "cpplot_common.hpp"

namespace cpplot {
    class axes_t_t : public boost::enable_shared_from_this<axes_t_t>, public boost::noncopyable {
        public:
            std::vector<std::vector<float> > cmap;
        private:
            boost::mutex children_mutex;
            layer_t layer;
            axes_t color_bar_axes;
            int window_h();
            int window_w();
            void draw2d();
            void draw3d();
            void draw_colorbar();
            float ctx(const double x);
            float cty(const double y);
            float ct3x(const double x);
            float ct3y(const double y);
            float ct3z(const double z);

        public:
            axes_t_t(layer_t);
            ~axes_t_t(){children.clear();}
            layer_t gcl() { return layer; }
            float cta,phi;  // controlled by mouse
            float cta0,phi0;// default value or specified by command line
            // Mouse
            double XMouse,YMouse;
            bool Mouse;
            int xButtonDown, yButtonDown;// last clicked mouse position
            float ctaButtonDown, phiButtonDown;
            bool(*mouse_callback)(int button, int state, int x, int);

            double xmin,xmax,ymin,ymax,zmin,zmax;

            void reset();
            void config();
            axes_t set(const std::string p, const std::string v);

            axes_t colorbar();


            void ptext(const float x, const float y, const std::string s);
            void ptext3(const float x, const float y, const float z, const std::string s);
            void ptext3c(const float x, const float y, const float z, const std::string s);

            bool mouse(const int button, const int state, const int x, const int y);
            bool motion(const int x, const int y);

            dvec make_tick(const double min, const double max);

            enum types {_2D, _3D, color_bar} type;

            // Matlab variables //
            // styles
            bool Box;//0:Off, 1:On
            std::string GridLineStyle;
            float LineWidth;
            std::string TickDir;// { in} | out
            //string TickDirMode;
            //TickLength
            bool visible;//0:Off, 1:On
            bool XGrid,YGrid,ZGrid;// {0:Off}, 1:On

            // General Information
            drawings_t children;
            drawing_t co;
            bool selected;
            float position[4];//left bottom width height
            float viewport3d[4];//left bottom width height

            //Scale
            std::string XAxisLocation;
            std::string YAxisLocation;

            //string XDir,YDir,ZDir;

            double XLim[2],YLim[2],ZLim[2];//plot range
            enum modes { automatic, manual } XLimMode,YLimMode,ZLimMode;//0:Auto 1:Manual
            math::scale XScale,YScale,ZScale;// linear_scale | log

            dvec XTick,YTick,ZTick;
            bool TickLabel;// 0:Off, {1:On}
            //View
            float camera_position[3];
            float camera_target[3];
            float camera_up_vector[3];

            // Label
            std::string Title;
            std::string XLabel,YLabel,ZLabel;

            double CLim[2];

            void draw();


            /// interface
            void axis(const double xMin, const double xMax, const double yMin, const double yMax);
            void axis(const double xMin, const double xMax, const double yMin, const double yMax, const double zMin, const double zMax);
            void axis(const std::string s);
            void axis(const bool s = true);
            void grid(const std::string s);
            void grid(bool s = true);
            void ticklabel(const bool s = true);
            void title(const std::string s);
            void xlabel(const std::string s);
            void ylabel(const std::string s);
            void mouse_capture(const bool y = true);

            template<typename T>
            boost::shared_ptr<T> add() {
                boost::shared_ptr<T> p(new T(shared_from_this()));
                co = boost::dynamic_pointer_cast<drawing_t_t, T>(p);
                assert(co);
                boost::mutex::scoped_lock l(children_mutex);
                children.push_back(co);
                return p;
            }

            template<typename T>
            boost::shared_ptr<T> gco() {
                if(!co) return add<T>();
                boost::shared_ptr<T> ptr = boost::dynamic_pointer_cast<T, drawing_t_t>(co);
                return ptr ? ptr : add<T>();
            }

            // Colors ///
            void color(const float r, const float g, const float b);
            std::vector<float> colormap(const std::string c, const float t);
            void colormap(const std::string c);
            void colormap(const std::vector<std::vector<float> >& c);


            void gray() { colormap("Gray"); };
            void jet() { colormap("Jet"); }
            void hsv() { colormap("HSV"); }
            void hot() { colormap("Hot"); }
            void cool() { colormap("Cool"); }
            void spring() { colormap("Spring"); }
            void summer() { colormap("Summer"); }
            void autumn() { colormap("Autumn"); }
            void winter() { colormap("Winter"); }

            std::vector<float> map2color(const double x);

            void vertex(const double x, const double y) { gco<Line>()->vertex(x,y); }
            void vertex(const double x, const double y, const double z) { gco<Line>()->vertex(x,y,z); }

            line_t plot(const dvec& y) { return add<Line>()->plot(y); }
            line_t plot(const dvec& x,const dvec& y) { return add<Line>()->plot(x,y); }
            line_t plot(const dvec& x, const dvec& y, const dvec& z) { return add<Line>()->plot(x,y,z); }

            line_t semilogx(const dvec& x, const dvec& y) { return add<Line>()->semilogx(x,y); }
            line_t semilogy(const dvec& x, const dvec& y) { return add<Line>()->semilogy(x,y); }
            line_t loglog(const dvec& x, const dvec& y)   { return add<Line>()->loglog(x,y); }

            void vertex(const double x, const double y, const double ep, const double em)
                { gco<Line>()->vertex(x,y,ep,em); }
            void errorbar(const dvec& x, const dvec& y, const dvec& e)
                { gco<Line>()->errorbar(x,y,e); }
            void errorbar(const dvec& x, const dvec& y, const dvec& ep, const dvec& em)
                { gco<Line>()->errorbar(x,y,ep,em); }


            // Surface, Contour ///
            surface_t surface(const dmat& Z) { return add<Surface>()->surface(Z); }
            surface_t surface(const dmat& Z, const dmat& C) { return add<Surface>()->surface(Z, C); }
            surface_t surface(const dmat& Z, const tcmat& C) { return add<Surface>()->surface(Z, C); }
            surface_t surface(const dvec& x, const dvec& y, const dmat& Z) { return add<Surface>()->surface(x,y,Z); }
            surface_t surface(const dvec& x, const dvec& y, const dmat& Z, const dmat& C) { return add<Surface>()->surface(x,y,Z,C); }
            surface_t surface(const dvec& x, const dvec& y, const dmat& Z, const tcmat& C) { return add<Surface>()->surface(x,y,Z); }
            surface_t surface(const dmat& X, const dmat& Y, const dmat& Z) { return add<Surface>()->surface(X,Y,Z); }
            surface_t surface(const dmat& X, const dmat& Y, const dmat& Z, const dmat& C) { return add<Surface>()->surface(X,Y,Z,C); }
            surface_t surface(const dmat& X, const dmat& Y, const dmat& Z, const tcmat& C) { return add<Surface>()->surface(X,Y,Z,C); }

            surface_t pcolor(const dmat& C) { return add<Surface>()->pcolor(C); }
            surface_t pcolor(const tcmat& C) { return add<Surface>()->pcolor(C); }
            surface_t pcolor(const dvec& x, const dvec& y, const dmat& C) { return add<Surface>()->pcolor(x,y,C); }
            surface_t pcolor(const dvec& x, const dvec& y, const tcmat& C) { return add<Surface>()->pcolor(x,y,C); }
            surface_t pcolor(const dmat& X, const dmat& Y, const dmat& C) { return add<Surface>()->pcolor(X,Y,C); }
            surface_t pcolor(const dmat& X, const dmat& Y, const tcmat& C) { return add<Surface>()->pcolor(X,Y,C); }

            surface_t contour(const dmat& Z) { return add<Surface>()->contour(Z); }
            surface_t contour(const dmat& Z,int n) { return add<Surface>()->contour(Z, n); }
            surface_t contour(const dmat& Z, const dvec& v) { return add<Surface>()->contour(Z,v); }
            surface_t contour(const dvec& x, const dvec& y, const dmat& Z) { return add<Surface>()->contour(x,y,Z); }
            surface_t contour(const dvec& x, const dvec& y, const dmat& Z, const int n) { return add<Surface>()->contour(x,y,Z,n); }
            surface_t contour(const dvec& x, const dvec& y, const dmat& Z, const dvec& v) { return add<Surface>()->contour(x,y,Z,v); }

            surface_t mesh(const dvec& x, const dvec& y, const dmat& Z) { return add<Surface>()->mesh(x,y,Z); }
            surface_t surf(const dvec& x, const dvec& y, const dmat& Z) { return add<Surface>()->surf(x,y,Z); }

            void shading(const std::string c) { gco<Surface>()->shading(c); }

            // Patch ///
            patch_t patch(const dmat& X, const dmat& Y) { return add<Patch>()->patch(X,Y); }
            patch_t patch(const dmat& X, const dmat& Y, const dvec& C) { return add<Patch>()->patch(X,Y,C); }
            patch_t patch(const dmat& X, const dmat& Y, const tcvec& C) { return add<Patch>()->patch(X,Y,C); }
            patch_t patch(const dmat& X, const dmat& Y, const dmat& Z) { return add<Patch>()->patch(X,Y,Z); }
            patch_t patch(const dmat& X, const dmat& Y, const dmat& Z, const dvec& C) { return add<Patch>()->patch(X,Y,Z,C); }
            patch_t patch(const dmat& X, const dmat& Y, const dmat& Z, const tcvec& C) { return add<Patch>()->patch(X,Y,Z,C); }

            patch_t bar(const dvec& y) { return add<Patch>()->bar(y); }
            patch_t bar(const dvec& y, const float width) { return add<Patch>()->bar(y, width); }
            patch_t bar(const dvec& x, const dvec& y) { return add<Patch>()->bar(x,y); }
            patch_t bar(const dvec& x, const dvec& y, const float width) { return add<Patch>()->bar(x,y,width); }

            // Text ///
            //TODO: more fonts
            text_t text(const double x, const double y, const std::string s) { return add<Text>()->text(x,y,s); }
    };
}
#endif
