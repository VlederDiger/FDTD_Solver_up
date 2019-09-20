/*
 * UpdaterHz1D.h
 *
 *  Created on: 20 сен. 2019 г.
 *      Author: vladislav
 */

#ifndef UpdaterIntensityTE_H_
#define UpdaterIntensityTE_H_

#include <thrust/device_vector.h>
#include <thrust/functional.h>

typedef thrust::device_ptr<float> d_ptr;

class UpdaterIntensityTE {
public:
	__host__ __device__
	UpdaterIntensityTE(d_ptr _intensity, d_ptr _Hz, int _firstX, int _firstY, int _sizeY,
									int _gridSizeY, int _stepX, int _stepY) :
														intensity(_intensity), Hz(_Hz),
														firstX(_firstX), firstY(_firstY),
														sizeY(_sizeY), gridSizeY(_gridSizeY),
														stepX(_stepX), stepY(_stepY)
														{};
	__host__ __device__
	UpdaterIntensityTE() {};

	__host__ __device__
	void setParams(d_ptr _intensity, d_ptr _Hz, int _firstX, int _firstY, int _sizeY,
									int _gridSizeY, int _stepX, int _stepY) {
		Hz = _Hz;
		intensity = _intensity;
		firstX = _firstX;
		firstY = _firstY;
		sizeY = _sizeY;
		gridSizeY = _gridSizeY;
		stepX = _stepX;
		stepY = _stepY;
	}
	__device__
	void operator() (const int indx);

	d_ptr Hz, intensity;
	int firstX, firstY, sizeY, gridSizeY, stepX, stepY;
};

#endif /* UPDATERHZ1D_H_ */
