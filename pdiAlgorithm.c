#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include "image.h"

unsigned char validColor(int c){
	if (c < 0) return 0;
	if (c > 255) return 255;

	return ((unsigned char) c);
}

int cor4(int x){
	if(x < 64) return 64;
	if(x >= 64 && x < 128) return 128;
	if(x >= 128 && x < 192) return 192;
	if(x >= 192) return 255;
}

int cor2(int cor){
	if(cor<128){
		return 0;
	}else{
		return 255;
	}
}

void printHistogramToConsole(Image * origImg){
	int x, y, k;
	unsigned char red, green, blue, gray;
	long hist[255];
	
	for(k = 0; k < 255; k++){
		hist[k] = 0;
	}	
	
	for (y = 0; y < imgGetHeight(origImg); y++){
		for (x = 0; x < imgGetWidth(origImg); x++){
			red = imgGetPixelRed(origImg, x, y);
			green = imgGetPixelGreen(origImg, x, y);
			blue = imgGetPixelBlue(origImg, x, y);

			gray = validColor(0.21*red + 0.71*green + 0.07*blue);
						
			hist[gray] += 1;
		}
	}
	
	for(k = 0; k < 255; k++){
		printf("%d = %d \n", k, hist[k]);
	}	
}

Image *img_ConvertGray(Image *origImg){
	int x, y;
	unsigned char red, green, blue, gray;
	Image *rImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
	
	printf("%dx%d", imgGetHeight(rImg), imgGetWidth(rImg));

	if (rImg == NULL)
			return NULL;

	for (y = 0; y < imgGetHeight(origImg); y++){
		for (x = 0; x < imgGetWidth(origImg); x++){
			red = imgGetPixelRed(origImg, x, y);
			green = imgGetPixelGreen(origImg, x, y);
			blue = imgGetPixelBlue(origImg, x, y);

			gray = validColor(0.21*red + 0.71*green + 0.07*blue);

			imgSetPixel(rImg, x, y, gray, gray, gray);
		}
	}

	return rImg;
}

Image *img_Quantizacao(Image *origImg, int cores){
	int x,y;
	unsigned char red, green, blue, gray;
	Image *rImg = img_ConvertGray(origImg);

	for (y = 0; y < imgGetHeight(rImg); y++){
		for (x = 0; x < imgGetWidth(rImg); x++){
			gray = imgGetPixelRed(rImg, x, y);
			
			if(cores == 2){
				imgSetPixel(rImg, x, y, cor2(gray), cor2(gray), cor2(gray));
			}else if(cores == 4){
				imgSetPixel(rImg, x, y, cor4(gray), cor4(gray), cor4(gray));
			}
		}
	}
	return rImg;
}

Image *img_Blur(Image *origImg, int sizeMask){
	int x,y,xx,yy;
	int aux = 0;
	int blurPix;
	unsigned char red, green, blue, gray;
	Image *rImg = img_ConvertGray(origImg);
	
	for (y = sizeMask; y < imgGetHeight(rImg)-sizeMask; y++){
		for (x = sizeMask; x < imgGetWidth(rImg)-sizeMask; x++){
			
			for (yy = y-(sizeMask/2); yy < (sizeMask/2)+y+1; yy++){
				for (xx = x-(sizeMask/2); xx < (sizeMask/2)+x+1; xx++){
					gray		= imgGetPixelRed(rImg, xx, yy);
					aux += gray;	
				}
			}
			blurPix = aux/(sizeMask*sizeMask);
			imgSetPixel(rImg, x, y, blurPix, blurPix, blurPix);
			aux = 0;
		}
	}
	
	return rImg;
}

Image *img_BlurMediana(Image *origImg, int sizeMask){
	int x,y,xx,yy, mx,my;
	int blurPix;
	int getMadiana[sizeMask*sizeMask];
	
	unsigned char red, green, blue, gray;
	
	Image *rImg = img_ConvertGray(origImg);

	for (y = sizeMask; y < imgGetHeight(rImg)-sizeMask; y++){
		for (x = sizeMask; x < imgGetWidth(rImg)-sizeMask; x++){
			int posMediana = 0;
			for (yy = y-(sizeMask/2); yy < (sizeMask/2)+y+1; yy++){
				for (xx = x-(sizeMask/2); xx < (sizeMask/2)+x+1; xx++){
					gray		= imgGetPixelRed(rImg, xx, yy);
										
					getMadiana[posMediana] = gray;
					posMediana++;
				}
			}
			
			for(mx = 0; mx < (sizeMask*sizeMask); mx++){
				for(my = 0; my < (sizeMask*sizeMask); my++){
					if(getMadiana[mx] < getMadiana[my]){
						int auxM = 0;
						auxM = getMadiana[mx];
						getMadiana[mx] = getMadiana[my];
						getMadiana[my] = auxM;
					}
				}
			}
						
			blurPix = getMadiana[(sizeMask*sizeMask)/2];
			imgSetPixel(rImg, x, y, blurPix, blurPix, blurPix);
		}
	}
	
	return rImg;
}


Image *img_Negativo(Image *origImg){
	int x,y;
	unsigned char red, green, blue, gray;
	Image *rImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
	
	for (y = 0; y < imgGetHeight(origImg); y++){
		for (x = 0; x < imgGetWidth(origImg); x++){
			red = imgGetPixelRed(origImg, x, y);
			green = imgGetPixelGreen(origImg, x, y);
			blue = imgGetPixelBlue(origImg, x, y);
			
			gray = validColor(0.21*red + 0.71*green + 0.07*blue);
			
			imgSetPixel(rImg, x, y, 255-gray, 255-gray, 255-gray);
		}
	}
	
	return rImg;
}

Image *img_SaltAndPepper(Image *origImg, int qtd){
	int x,y;
	Image *rImg = img_ConvertGray(origImg);
	
	time_t t;
	srand((unsigned) time(&t));
	
	
	for (y = 0; y < imgGetHeight(rImg); y++){
		for (x = 0; x < imgGetWidth(rImg); x++){
			if((rand() % qtd) < 1){
				if((rand() % 2) == 0){
					imgSetPixel(rImg, x, y, 255, 255, 255);
				}else{
					imgSetPixel(rImg, x, y, 0, 0, 0);
				}
			}
		}
	}
	
	return rImg;
}

Image *img_Gaussiano(Image *origImg, int qtd){
	int x,y, c;
	Image *rImg = img_ConvertGray(origImg);
	
	time_t t;
	srand((unsigned) time(&t));
	
	
	for (y = 0; y < imgGetHeight(rImg); y++){
		for (x = 0; x < imgGetWidth(rImg); x++){
			if((rand() % qtd) < 1){
				c = rand() % 255;
				imgSetPixel(rImg, x, y, c, c, c);
			}
		}
	}
	
	return rImg;
}

