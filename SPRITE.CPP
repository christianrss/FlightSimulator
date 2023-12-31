#include <stdio.h>
#include <alloc.h>
#include <mem.h>
#include "SPRITE.H"
#include "SCREEN.H"

// Construtor Sprite
// Aloca memoria para estruturas sprite NUM_SPRITES
Sprite::Sprite(int num_sprites, int w, int h)
{
	image 		= new char far *[num_sprites];
	width 		= w;
	height 		= h;
	savebuffer 	= new char[width*height];
}

// Exibir sprite na tela com canto superior esquero nas
// coordenadas x,y. Pixels zero sao tratados como transparentes;
// isto e, nao sao exibidos.
void Sprite::put(int sprite_num, int x, int y,
	unsigned char far *screen)
{

	int poffset = y*320+x;  // Calcular offset das coordenadas do sprite
	int soffset = 0;		// Apontar offset do sprite para o seu inicio

	// Fazer loop nas linhas do sprite, transferindo pixels diferentes
	//  de zero para a tela
	for (int row=0; row<height; row++)
	{
		for (int column=0; column<width; column++)
		{
			// Copiar o pixel do fundo para o buffer que salva o fundo
			savebuffer[soffset] = screen[poffset];
			// Pegar o proximo pixel do buffer de imagens do sprite
			int pixel = image[sprite_num][soffset++];
			// Se nao for trasparante, coloque-o no buffer da tela
			if (pixel) screen[poffset] = pixel;
			poffset++;
		}
		poffset += (320-width);
	}
	// Gravar coordenadas atuais do sprite
	xsprite = x;
	ysprite = y;
}

// Apagar o sprite da tela copiando a imagem do fundo salva
// sobre ele
void Sprite::erase(unsigned char far *screen)
{
	// Calcula o offset do sprite na memoria de video
	int voffset = ysprite * 320 + xsprite;
	int soffset = 0;

	// Loop pelas linhas e colunas do buffer onde foi salvo o fundo
	// transferindo os pixels para a tela
	for (int column=0; column < width; column++)
	{
		for (int row = 0; row < height; row++)
			screen[voffset++] = savebuffer[soffset++];

		voffset+= (320-width); // Posicionar ponteiro para a proxima linha
	}
}

// "Pincar" uma imagem retangular de um sprite bitmap de 64K
// e armazena-la em SPRITE[SPRITE_NUM]
void Sprite::grab(unsigned char far *buffer, int sprite_num, int x1, int y1)
{

	 // Alocar memoria para o bitmap do sprite e para o
	 // buffer que salva o fundo
	 image[sprite_num] = new char[width*height];

	 // Verifica se o sprite ultrapassa o limite do buffer de bitmap;
	 // abortar se isso ocorrer
	 if ((x1+width>SCREEN_WIDTH) | (y1+height>SCREEN_WIDTH))
		return;

	 // Loop por todas as linhas e colunas do sprite,
	 // armazenando os pixels no buffer do sprite
	 for(int row=0; row < height; row++)
		for (int column = 0; column < width; column++)
			image[sprite_num][row*width+column] = buffer[(y1+row)*SCREEN_WIDTH+x1+column];
}