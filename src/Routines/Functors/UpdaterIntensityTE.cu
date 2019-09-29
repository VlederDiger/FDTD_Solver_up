/*
 * UpdaterHz1D.cpp
 *
 *  Created on: 20 сен. 2019 г.
 *      Author: vladislav
 */

#include "UpdaterIntensityTE.h"

__device__
void UpdaterIntensityTE::operator() (const int indx) {
	#define Ex(M, N) Ex[(M) * (gridSizeY) + (N)]
	#define Ey(M, N) Ey[(M) * (gridSizeY) + (N)] // gridSizeY-1?
	const int n = indx % sizeY;
	const int m = indx / sizeY;
	intensity[indx] = intensity[indx] + sqrt(Ex(firstX + m*stepX, firstY + n*stepX)*Ex(firstX + m*stepX, firstY + n*stepX)+Ey(firstX + m*stepX, firstY + n*stepX)*Ey(firstX + m*stepX, firstY + n*stepX));
}
