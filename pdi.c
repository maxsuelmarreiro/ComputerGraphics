/*
 ============================================================================
 Name        : pdi.c
 Author      : 
 Version     :
 Copyright   : 
 Description : C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "image.h"
#include "pdiAlgorithm.h"

int main(void) {
	
	//puts("!!!Hello World!!!"); /* prints !!!Hello World!!! */
	
	//LER IMG
	Image *lenaImg = imgReadPPM("/Users/Public/lena256Gray.ppm");
	//imgWritePPM(lenaImg, "./images/lena256color.ppm");
	
	//printHistogramToConsole(lenaImg);
	
	//GRAY
	Image *img = img_ConvertGray(lenaImg);
	imgWritePPM(img, "/Users/Public/lena256Gray.ppm");
	system("/Users/Public/lena256Gray.ppm");

	//QUANTIZAÇÃO
	//Image *img = img_Quantizacao(lenaImg, 2);
	//imgWritePPM(img, "/Users/Public/lena256Quantizacao.ppm");
	//system("/Users/Public/lena256Quantizacao.ppm");

	//BLUR - MEDIA
	//Image *img = img_Blur(lenaImg, 11);
	//imgWritePPM(img, "/Users/Public/lena256Blur1.ppm");
	//system("/Users/Public/lena256Blur1.ppm");
	
	//BLUR - MEDIANA
	//Image *img = img_BlurMediana(lenaImg, 7);
	//imgWritePPM(img, "/Users/Public/lenaBlurMediana.ppm");
	//system("/Users/Public/lenaBlurMediana.ppm");

	//NEGATIVO
	//Image *img = img_Negativo(lenaImg);
	//imgWritePPM(img, "/Users/Public/lenaNegativo.ppm");
	//system("/Users/Public/lenaNegativo.ppm");

	//SALT AND PEPPER
	//Image *img = img_SaltAndPepper(lenaImg, 10);
	//imgWritePPM(img, "/Users/Public/lenaSaltAndPepper.ppm");
	//system("/Users/Public/lenaSaltAndPepper.ppm");

	//GAUSSIANO
	//Image *img = img_Gaussiano(lenaImg, 10);
	//imgWritePPM(img, "/Users/Public/lenaGaussiano.ppm");
	//system("/Users/Public/lenaGaussiano.ppm");


	//printHistogramToConsole(img);
	
	imgDestroy(lenaImg);
	//imgDestroy(img);
	return EXIT_SUCCESS;
}
