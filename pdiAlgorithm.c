#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <math.h>
#include "image.h"

unsigned char validColor(int c){
	if (c < 0) return 0;
	if (c > 255) return 255;
	pow(6,9);
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

void img_View(Image * origImg){

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

	//printf("%dx%d", imgGetHeight(rImg), imgGetWidth(rImg));

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

Image *img_Limiarizacao(Image *origImg, int T){
	int x,y;
	int PorB;
	unsigned char red, green, blue, gray;
	Image *rImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
	
	for (y = 0; y < imgGetHeight(origImg); y++){
		for (x = 0; x < imgGetWidth(origImg); x++){
			red = imgGetPixelRed(origImg, x, y);
			green = imgGetPixelGreen(origImg, x, y);
			blue = imgGetPixelBlue(origImg, x, y);
			
			gray = validColor(0.21*red + 0.71*green + 0.07*blue);
			
			if(gray > T){
				PorB = 255;
			}else{
				PorB = 0;
			}

			imgSetPixel(rImg, x, y, PorB, PorB, PorB);

		}
	}
	
	return rImg;
}

Image *img_Binarizacao(Image *origImg){
	return img_Limiarizacao(origImg, 127);
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



Image *img_PassaAltasRoberts(Image *origImg){
	int x,y,aux;
	unsigned char red, green, blue, gray;
	Image *rImg = img_ConvertGray(origImg);
	Image *newImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
	newImg = rImg;
	
	for (y = 0; y < imgGetHeight(rImg); y++){
		for (x = 0; x < imgGetWidth(rImg); x++){


			aux = sqrt((pow((imgGetPixelRed(rImg, x+1, y+1) - imgGetPixelRed(rImg, x, y)),2) + pow((imgGetPixelRed(rImg, x, y+1) - imgGetPixelRed(rImg, x+1, y)),2))); 

			aux = validColor(aux);

			imgSetPixel(newImg, x, y, aux, aux, aux);

		}
	}
	return newImg;
}

Image *img_PassaAltasSobel(Image *origImg){
	int x,y;
	
	int z1 = 0,z2 = 0,z3 = 0,z4 = 0,z5 = 0,z6 = 0,z7 = 0,z8 = 0,z9 = 0;
	int Gx = 0, Gy = 0, res = 0;
	
	unsigned char red, green, blue, gray;
	Image *rImg = img_ConvertGray(origImg);
	Image *newImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));

	for (y = 1; y < imgGetHeight(rImg); y++){
		for (x = 1; x < imgGetWidth(rImg); x++){
	
			z1 = imgGetPixelRed(rImg, x-1, y-1);
			z2 = imgGetPixelRed(rImg, x-1, y);
			z3 = imgGetPixelRed(rImg, x-1, y+1);

			z4 = imgGetPixelRed(rImg, x, y-1);
			z5 = imgGetPixelRed(rImg, x, y);
			z6 = imgGetPixelRed(rImg, x, y+1);

			z7 = imgGetPixelRed(rImg, x+1, y-1);
			z8 = imgGetPixelRed(rImg, x+1, y);
			z9 = imgGetPixelRed(rImg, x+1, y+1);

			//Gx = (z1+(2*z4)+z7-z3-(2*z6)-z9);
			//Gy = (z1+(2*z2)+z3-z7-(2*z8)-z9);

			Gx = (z7+(2*z8)+z9)-(z1+(2*z2)+z3);
			Gy = (z3+(2*z6)+z9)-(z1+(2*z4)+z7);
			
			Gx = validColor(Gx);
			Gy = validColor(Gy);
			
			res = (int)(sqrt((pow(Gx,2) + pow(Gy,2)))); 
			
			imgSetPixel(newImg, x, y, res, res, res);
	
		}
	}
	return newImg;
}

Image *img_PassaAltasPrewitt(Image *origImg){
	int x,y, aux;
	unsigned char red, green, blue, gray;
	Image *rImg = img_ConvertGray(origImg);
	Image *newImg = imgCreate(imgGetWidth(origImg), imgGetHeight(origImg));
	
	int z1 = 0,z2 = 0,z3 = 0,z4 = 0,z5 = 0,z6 = 0,z7 = 0,z8 = 0,z9 = 0;
	int Gx = 0, Gy = 0, res = 0;


	for (y = 1; y < imgGetHeight(rImg); y++){
		for (x = 1; x < imgGetWidth(rImg); x++){
	
			z1 = imgGetPixelRed(rImg, x-1, y-1);
			z2 = imgGetPixelRed(rImg, x-1, y);
			z3 = imgGetPixelRed(rImg, x-1, y+1);

			z4 = imgGetPixelRed(rImg, x, y-1);
			z5 = imgGetPixelRed(rImg, x, y);
			z6 = imgGetPixelRed(rImg, x, y+1);

			z7 = imgGetPixelRed(rImg, x+1, y-1);
			z8 = imgGetPixelRed(rImg, x+1, y);
			z9 = imgGetPixelRed(rImg, x+1, y+1);

			
			//Gx = (z7+z8+z9)-(z1+2*z2+z3);
			//Gy = (z3+z6+z9)-(z1+z4+z7);
			Gx = (z1+z2+z3-z7-z8-z9);
			Gy = (z3+z6+z9-z1-z4-z7);
			
			Gx = validColor(Gx);
			Gy = validColor(Gy);
						
			res = sqrt((pow(Gx,2))+(pow(Gy,2)));  
			
			imgSetPixel(newImg, x, y, res, res, res);
		}
	}
	return newImg;
}
