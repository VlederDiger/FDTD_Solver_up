/*
 * IntensityOutputRoutine.cpp
 *
 *  Created on: 18 сен. 2019 г.
 *      Author: vladislav
 */

#include "IntensityOutputRoutineTE.h"

#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>



void IntensityOutputRoutineTM::collectDataGPU() {
	thrust::counting_iterator<int> start(0);
	thrust::counting_iterator<int> end(intensityGPU.getSize());
	thrust::for_each(start , end , updaterIntensity);
}
