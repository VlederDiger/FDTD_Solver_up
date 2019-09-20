/*
 * IntensityOutputRoutine.cpp
 *
 *  Created on: 18 сен. 2019 г.
 *      Author: vladislav
 */

#include "IntensityOutputRoutineTE.h"
#include <fstream>
#include <cmath>
#include <thrust/for_each.h>
#include <thrust/iterator/counting_iterator.h>

void IntensityOutputRoutineTE::printFromCPU() {
	std::ofstream file;
	std::string currentFileName = fileName+"_"+std::to_string(currentTime) + ".txt";
	file.open(currentFileName, std::ofstream::trunc);
	if (!file.is_open()) {
		std::cout << 'File' << currentFileName << ' not opened' << std::endl;
		return;
	}
	for(int i = 0; i < intensity.size(); i++) {
		int xCoord = i/sizeY;
		int yCoord = i%sizeY;
		file << firstX+resolutionX*xCoord << " " << firstY+resolutionY*yCoord << " " << intensity[i]/period << std::endl;
	}
	file.close();
}

void IntensityOutputRoutineTE::printFromGPU() {
	std::ofstream file;
	std::string currentFileName = fileName+"_"+std::to_string(currentTime) + ".txt";
	intensityGPU.GPUtoCPU();
	file.open(currentFileName, std::ios::trunc | std::ios::binary);
	if (!file.is_open()) {
		std::cout << 'File' << currentFileName << ' not opened' << std::endl;
		return;
	}
	for(int i = 0; i < intensityGPU.getSize(); i++) {
		int xCoord = i/sizeY;
		int yCoord = i%sizeY;
		file << firstX+resolutionX*xCoord << " " << firstY+resolutionY*yCoord << " " <<intensityGPU[i]/period << "\n";
	}
	file.close();
}

void IntensityOutputRoutineTE::print() {
	if (copyEachIteration) {
		printFromCPU();
	} else {
		printFromGPU();
	}
}

void IntensityOutputRoutineTE::flushData() {
	stepsCollected = 0;
	if (copyEachIteration) {
		for(int i = 0; i < intensity.size(); i++) {
			intensity[i] = 0;
		}
		memset(&intensity[0], 0, intensity.size() * sizeof intensity[0]);
	} else {
		intensityGPU.fill(0);
	}
}

void IntensityOutputRoutineTE::collectData() {
	stepsCollected++;
	if (copyEachIteration) {
		collectDataCPU();
	} else {
		collectDataGPU();
	}
}

void IntensityOutputRoutineTE::collectDataCPU() {
	grid->Ez.GPUtoCPU();
	#define Hz(M, N) grid->Hz[(M) * (grid->sizeY) + (N)]
	for(int m = 0; m < sizeX; m++ ) {
		for(int n = 0; n < sizeY; n++ ){
			intensity(m, n) += Hz(firstX + m*resolutionX, firstY + n*resolutionX)*Hz(firstX + m*resolutionX, firstY + n*resolutionX);
		}
	}
}

void IntensityOutputRoutineTE::compute(int time) {
	if (time > startTime && time < endTime) {
		collectData();
		if ( stepsCollected == period ) {
			print();
			flushData();
		}
	}
	currentTime = time;
}
