#pragma once
inline int findMaxPixel(int img[][8], int height, int width) {
	int maxPix = img[0][0];
	for (int i = 0; i < HEIGHT; i++) {
		for (int j = 0; j < WIDTH; j++) {
			if (img[i][j] > maxPix)
				maxPix = img[i][j];
		}
	}
	return maxPix;
}
