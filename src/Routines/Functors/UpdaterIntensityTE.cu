/*
 * UpdaterHz1D.cpp
 *
 *  Created on: 20 сен. 2019 г.
 *      Author: vladislav
 */

#include "UpdaterIntensityTE.h"

__device__
void UpdaterIntensityTE::operator() (const int indx) {
	#define Hz(M, N) Hz[(M) * (gridSizeY) + (N)]
	const int n = indx % sizeY;
	const int m = indx / sizeY;
	intensity[indx] = intensity[indx] + Hz(firstX + m*stepX, firstY + n*stepX)*Hz(firstX + m*stepX, firstY + n*stepX);
}
