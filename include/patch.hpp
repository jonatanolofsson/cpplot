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

#ifndef _CPPLOT_PATCH_HPP_
#define _CPPLOT_PATCH_HPP_
namespace cpplot {
    class Patch;
    typedef boost::shared_ptr<Patch> patch_t;
    class Patch : public drawing_t_t, public boost::enable_shared_from_this<Patch> {
        public:
            enum types {_2D, _3D} type;
            std::vector< std::vector<int> > faces;
            dmat vertices;
            dmat FaceVertexCData;
            dmat XData,YData,ZData;

            tcvec CData;

            std::string EdgeColor,FaceColor;//{ ColorSpec}|none|flat|interp

            std::string LineStyle; // {-} | - - | : | -. | none
            float  LineWidth;

            Patch(const axes_t a)
                :   drawing_t_t(a),
                    type(_2D),
                    LineWidth(1),
                    FaceColor("r"),
                    EdgeColor("k"),
                    LineStyle("-")
                {}

            void draw();


            /// bar
            patch_t bar(const dvec& y, float width = 0.8);
            patch_t bar(const dvec& x, const dvec& y, const float width = 0.8);
            /// patch
            patch_t patch(const dmat& X, const dmat& Y);
            patch_t patch(const dmat& X, const dmat& Y, const dvec& C);
            patch_t patch(const dmat& X, const dmat& Y, const tcvec& C);
            patch_t patch(const dmat& X, const dmat& Y, const dmat& Z);
            patch_t patch(const dmat& X, const dmat& Y, const dmat& Z, const dvec& C);
            patch_t patch(const dmat& X, const dmat& Y, const dmat& Z, const tcvec& C);

            patch_t set(const std::string p, const std::string v);
            patch_t set(const std::string p, const float v);

            tcvec Index2TrueColor(const dvec& IC);

            void config();

        private:
            void draw2d();
            void draw3d();
            boost::mutex data_mutex;
    };
    //Note: XData[iv][if]
}
#endif
