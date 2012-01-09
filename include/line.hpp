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

#ifndef _CPPLOT_LINE_HPP_
#define _CPPLOT_LINE_HPP_

#include <valarray>

namespace cpplot {
    class Line;
    typedef boost::shared_ptr<Line> line_t;
    class Line : public drawing_t_t, public boost::enable_shared_from_this<Line> {
        public:
            bool Errorbar;

            void reset();
            void color(const float r, const float g, const float b);

            // Matlab oriented variables //
            dvec XData,YData,ZData;
            dvec YPData,YMData;

            std::string Color;
            std::string LineStyle;// {-} | - - | : | -. | none
            float  LineWidth;
            std::string Marker;// { none}
            float  MarkerSize;
            std::string MarkerEdgeColor;
            std::string MarkerFaceColor;

            int Clipping;
            //string EraseMode;
            int SelectionHighlight;
            bool visible;

            Line(const axes_t a)
                :   drawing_t_t(a),
                    Color("b"),
                    LineStyle("-"),
                    LineWidth(0.5),
                    Marker("none"),
                    MarkerSize(6),
                    MarkerEdgeColor("k"),
                    MarkerFaceColor("w"),
                    Errorbar(0),
                    XData(), YData(), ZData(),
                    YPData(), YMData()
                {}
            figure_t gcf();

            void draw();
            void config();
            // vertex
            void  vertex(const double x, const double y);
            line_t line(const dvec& x, const dvec& y);
            line_t line(const dvec& x, const dvec& y, const dvec& z);
            // plot, semilogx, semilogy, loglog
            line_t plot(const dvec& y);
            line_t plot(const dvec& x, const dvec& y);
            line_t plot(const dvec& x, const dvec& y, const dvec& z);
            line_t plot(std::valarray<double> x, std::valarray<double> y);
            line_t semilogx(const dvec& x, const dvec& y);
            line_t semilogy(const dvec& x, const dvec& y);
            line_t loglog(const dvec& x, const dvec& y);
            // errorbar
            void vertex(const double x, const double y, const double ep, const double em); //for errorbar
            line_t errorbar(const dvec& x, const dvec& y,dvec e);
            line_t errorbar(const dvec& x, const dvec& y,dvec ep, const dvec& em);
            // 3D line
            void vertex(const double x, const double y, const double z);
            line_t set(const float v);
            line_t set(const std::string v);
            line_t set(const std::string p, const std::string v);
            line_t set(const std::string p, const float v);

        private:
            std::pair<double, double> min_max(const dvec&, math::scale);
            boost::mutex data_mutex;
    };
}
#endif
