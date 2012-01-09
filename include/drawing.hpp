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

#ifndef _CPPLOT_DRAWING_HPP_
#define _CPPLOT_DRAWING_HPP_

#include "drawing.hpp"
#include <boost/utility.hpp>
#include "cpplot_common.hpp"

namespace cpplot {
    class drawing_t_t;
    typedef boost::shared_ptr<drawing_t_t> drawing_t;
    typedef std::list<drawing_t> drawings_t;

    class drawing_t_t : public boost::noncopyable {
        protected:
            axes_t ca;

        public:
            // axes coordination
            float ctx(const double x);
            float cty(const double y);
            float ct3x(const double x);
            float ct3y(const double y);
            float ct3z(const double z);

            virtual void draw() = 0;
            virtual void config() = 0;

            drawing_t_t(const axes_t a)
                :   ca(a)
                {}
    };
}
#endif
