/*****************************************************************************
 *   Copyright (C) 2004-2009 The PaGMO development team,                     *
 *   Advanced Concepts Team (ACT), European Space Agency (ESA)               *
 *   http://apps.sourceforge.net/mediawiki/pagmo                             *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Developers  *
 *   http://apps.sourceforge.net/mediawiki/pagmo/index.php?title=Credits     *
 *   act@esa.int                                                             *
 *                                                                           *
 *   This program is free software; you can redistribute it and/or modify    *
 *   it under the terms of the GNU General Public License as published by    *
 *   the Free Software Foundation; either version 2 of the License, or       *
 *   (at your option) any later version.                                     *
 *                                                                           *
 *   This program is distributed in the hope that it will be useful,         *
 *   but WITHOUT ANY WARRANTY; without even the implied warranty of          *
 *   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the           *
 *   GNU General Public License for more details.                            *
 *                                                                           *
 *   You should have received a copy of the GNU General Public License       *
 *   along with this program; if not, write to the                           *
 *   Free Software Foundation, Inc.,                                         *
 *   59 Temple Place - Suite 330, Boston, MA  02111-1307, USA.               *
 *****************************************************************************/

#include <iostream>
#include "src/pagmo.h"

using namespace pagmo;

int main()
{

// This instantiates a differential evolution algorithm that will run for 500 generations. Refer to the documentation to
// see what othert parameters do
//pagmo::algorithm::de algo(1,0.8,0.92,2);
pagmo::algorithm::pso_generational algo(1,0.7298,2.05,2.05,0.05);

//This instantiates the spheres problem
pagmo::problem::spheres prob(5,10,1e-6,rand());

std::cout << "Initializing ...." << std::endl;

// This instantiates a population
pagmo::population pop_temp(prob,512);

prob.set_bounds(-10,10);

pagmo::population pop(prob);

pagmo::decision_vector v(123,0);
for (int i =0; i<512; ++i) {
	pop.push_back(pop_temp.get_individual(i).cur_x);
	pop.set_v(i,v);
}



island isl(algo,pop);


// //Evolution is here started on the single island instantiated
for (int i=0; i< 1000; ++i){
   std::cout << i << " " << isl.get_population().champion().f[0] << "\t" << isl.get_population().mean_velocity() << std::endl;
   isl.evolve();
   isl.join();

 }

 std::cout << "and the winner is ......" << "\n" << isl.get_population().champion().x << std::endl;

return 0;
}
