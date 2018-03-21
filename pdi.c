/*
 ============================================================================
 Name        : pdi.c
 Author      : Maxsuel Marreiro
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

//READ IMG
Image *original = imgReadPPM("/Users/Public/lena256color.ppm");
Image *lenaImg = original;
//imgWritePPM(lenaImg, "./images/lena256color.ppm");

Image *img;
int aux = 0;
int op = 100;

while(op != 0){
	system("cls");

	printf("+----+----+----+----+----+----+\n");

	printf("100 : Set original img\n");
	printf("101 : Set previous img\n");
	printf("102 : View current img\n");

	printf("+----+----+----+----+----+----+\n");

	printf(" 1 : Equalizacao (TODO)\n");
	printf(" 2 : Negativo\n");
	printf(" 3 : Binarizacao\n");
	printf(" 4 : Limiarizacao\n");
	printf(" 5 : Histograma\n");

	printf(" + Filtros passa-baixas\n");
	printf(" |--- 9  : Media\n");
	printf(" |--- 10 : Mediana\n");

	printf(" + Filtros passa-altas\n");
	printf(" |--- 71 : Roberts\n");
	printf(" |--- 72 : Sobel\n");
	printf(" |--- 73 : Prewitt\n");

	printf(" 8 : Realce (TODO)\n");

	printf("12 : QUANTIZACAO\n");

	printf(" + Ruidos\n");
	printf(" |--- 13 : SALT AND PEPPER\n");
	printf(" |--- 14 : GAUSSIANO\n");

	printf("+----+----+----+----+----+----+\n");

	printf(" 0 : EXIT\n");

	scanf("%d", &op);

	switch(op){
	
		// Equalização
		case 1:
		
		break;
		// Negativo
		case 2:
			img = img_Negativo(lenaImg);
			imgWritePPM(img, "/Users/Public/lenaNegativo.ppm");
			printf(" >> Negativo\n");
			system("/Users/Public/lenaNegativo.ppm");
		break;
		// Binarização
		case 3:
			img = img_Binarizacao(lenaImg);
			imgWritePPM(img, "/Users/Public/lenaBinarizacao.ppm");
			printf(" >> Binarização\n");
			system("/Users/Public/lenaBinarizacao.ppm");
		break;
		// Limiarização
		case 4:
			printf("Limiar: ");
			scanf("%d", &aux);
			
			img = img_Limiarizacao(lenaImg, aux);
			imgWritePPM(img, "/Users/Public/lenaLimiarizacao.ppm");
			printf(" >> Limiarizacao\n");
			system("/Users/Public/lenaLimiarizacao.ppm");
		break;
		// Histograma
		case 5:
			printHistogramToConsole(lenaImg);
		break;
		// Passa baixa
		case 6:
		
		break;
		// Passa alta
		case 71:
			img = img_PassaAltasRoberts(lenaImg);
			imgWritePPM(img, "/Users/Public/lenaPassaAltasRoberts.ppm");
			printf(" >> Passa-altas: Roberts\n");
			system("/Users/Public/lenaPassaAltasRoberts.ppm");
		break;
		case 72:
			img = img_PassaAltasSobel(lenaImg);
			imgWritePPM(img, "/Users/Public/lenaPassaAltasSobel1.ppm");
			printf(" >> Passa-altas: Sobel\n");
			system("/Users/Public/lenaPassaAltasSobel1.ppm");
		break;
		case 73:
			img = img_PassaAltasPrewitt(lenaImg);
			imgWritePPM(img, "/Users/Public/lenaPassaAltasPrewitt.ppm");
			printf(" >> Passa-altas: Prewitt\n");
			system("/Users/Public/lenaPassaAltasPrewitt.ppm");
		break;
		// Realce
		case 8:
		
		break;
		// Media
		case 9:
			printf("Tamanho da mascara: ");
			scanf("%d", &aux);
			
			img = img_BlurMediana(lenaImg, aux);
			imgWritePPM(img, "/Users/Public/lenaBlurMediana.ppm");
			printf(" >> \n");
			system("/Users/Public/lenaBlurMediana.ppm");
		break;
		// Mediana
		case 10:
			printf("Tamanho da mascara: ");
			scanf("%d", &aux);
			
			img = img_Blur(lenaImg, aux);
			imgWritePPM(img, "/Users/Public/lena256Blur1.ppm");
			printf(" >> \n");
			system("/Users/Public/lena256Blur1.ppm");
		break;
		// 
		case 11:
		
		break;
		// QUANTIZAÇÃO
		case 12:
			printf("Quantidade de tons (2 ou 4): ");
			scanf("%d", &aux);	
			
			img = img_Quantizacao(lenaImg, aux);
			imgWritePPM(img, "/Users/Public/lena256Quantizacao.ppm");
			printf(" >> \n");
			system("/Users/Public/lena256Quantizacao.ppm");
		break;
		// SALT AND PEPPER
		case 13:
			img = img_SaltAndPepper(lenaImg, 10);
			imgWritePPM(img, "/Users/Public/lenaSaltAndPepper.ppm");
			printf(" >> \n");
			system("/Users/Public/lenaSaltAndPepper.ppm");
		break;
		// GAUSSIANO
		case 14:
			img = img_Gaussiano(lenaImg, 10);
			imgWritePPM(img, "/Users/Public/lenaGaussiano.ppm");
			printf(" >> \n");
			system("/Users/Public/lenaGaussiano.ppm");
		break;		
		// 
		case 15:
		
		break;
		// 
		case 100:
			printf (">> utilizando imagem original..\n");
			lenaImg = original;
		break;
		case 101:
			printf (">> utilizando imagem anterior..\n");
			lenaImg = img;
		break;
		case 102:
			printf (">> img atual...\n");
			imgWritePPM(lenaImg, "/Users/Public/lenaCurrent.ppm");
			system("/Users/Public/lenaCurrent.ppm");
		break;
		default :
       		printf (">> Saiu!\n");
		
	}
}
	imgDestroy(lenaImg);
	//imgDestroy(img);
	return EXIT_SUCCESS;
}
