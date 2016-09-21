#ifndef PDIALGORITHM_H_
#define PDIALGORITHM_H_

Image * img_ConvertGray(Image * origImg);
Image * img_Blur(Image * origImg, int sizeMask);
Image * img_BlurMediana(Image * origImg, int sizeMask);
Image * img_Quantizacao(Image * origImg, int cores);
Image * img_Negativo(Image * origImg);

Image * img_SaltAndPepper(Image * origImg, int qtd);
Image * img_Gaussiano(Image * origImg, int qtd);


unsigned int * img_GetHistogram (Image * img);
void printHistogramToConsole(Image * img);

#endif
