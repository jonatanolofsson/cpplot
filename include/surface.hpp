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

#ifndef _CPPLOT_SURFACE_HPP_
#define _CPPLOT_SURFACE_HPP_
namespace cpplot {
    class Surface;
    typedef boost::shared_ptr<Surface> surface_t;
    class Surface : public drawing_t_t, public boost::enable_shared_from_this<Surface> {
        public:
            std::string ColorMap;

            dmat XData,YData,ZData,CDataIndex;
            dvec V,UserData;
            tcmat CData;

            std::string FaceColor;//ColorSpec    | none | { flat}
            std::string EdgeColor;//ColorSpec{ k} | none | flat

            std::string LineStyle;// {-} | - - | : | -. | none
            float LineWidth;
            std::string Marker;// { none}
            float MarkerSize;
            std::string MarkerEdgeColor;
            std::string MarkerFaceColor;

            int NContour;

            enum types { _2D, _3D, contourplot } type;

            Surface(const axes_t a)
                :   drawing_t_t(a),
                    ColorMap("Gray"),
                    FaceColor("flat"),
                    EdgeColor("b"),
                    LineStyle("-"),
                    LineWidth(0.5),
                    NContour(10),
                    V(), UserData()
                {}

            void draw();


            /// Color ///
            surface_t shading(const std::string c);
            surface_t surface(const dmat& Z);
            surface_t surface(const dmat& Z, const dmat& C);
            surface_t surface(const dmat& Z, const tcmat& C);
            surface_t surface(const dvec& x, const dvec& y, const dmat& Z);
            surface_t surface(const dvec& x, const dvec& y, const dmat& Z, const dmat& C);
            surface_t surface(const dvec& x, const dvec& y, const dmat& Z, const tcmat& C);
            surface_t surface(const dmat& X, const dmat& Y, const dmat& Z);
            surface_t surface(const dmat& X, const dmat& Y, const dmat& Z, const dmat& C);
            surface_t surface(const dmat& X, const dmat& Y, const dmat& Z, const tcmat& C);
            /// surf
            surface_t surf(const dvec& x, const dvec& y, const dmat& Z);
            /// create pcolor
            surface_t pcolor(dmat C);
            surface_t pcolor(const tcmat& C);
            surface_t pcolor(const dvec& x, const dvec& y, const dmat& C);
            surface_t pcolor(const dvec& x, const dvec& y, const tcmat& C);
            surface_t pcolor(const dmat& X, const dmat& Y, const dmat& C);
            surface_t pcolor(const dmat& X, const dmat& Y, const tcmat& C);
            /// mesh
            surface_t mesh(const dvec& x, const dvec& y, dmat Z);
            /// contour
            surface_t contour(const dmat& Z);
            surface_t contour(const dmat& Z, const int n);
            surface_t contour(const dmat& Z, const dvec& v);
            surface_t contour(const dvec& x, const dvec& y, const dmat& Z);
            surface_t contour(const dvec& x, const dvec& y, const dmat& Z, const int n);
            surface_t contour(const dvec& x, const dvec& y, const dmat& Z, const dvec& v);

            surface_t set(const std::string p, const std::string v);
            surface_t set(const std::string p, const float v);

            void contourc(const dvec& x, const dvec& y, const dmat& Z, const dvec& v, dmat& C);

            void config();

        private:
            void draw2d();
            void draw3d();
            void draw_contour();
            boost::mutex data_mutex;

            // contour
            struct ContourPoint{
                double x,y;
                int xj,yi;
                int xy;
                int done;
            };

    };
    //Note:
    // [m,n] = size(Z), length(x) = n length(y) = m, (x(j),y(i),Z(i,j))
}
#endif
