/*struct sprite_struct {
	char far *image; // Ponteiro para o array contendo
					 // os bitmaps do sprite
	char far *savebuffer; // Ponteiro para o array a fim de salvar
						  // o fundo do sprite
	int width, height; // Altura e largura do sprite em pixels
	int x,y; 		   // Coordenadas x,y do sprite no momento
};*/

class Sprite
{
	private:
		char far **image;		// Ponteiro para bitmaps do sprite
		int width, height;  	// Largura e altura do bitmap do sprite
		int xsprite,ysprite;	// Coordenadas x,y do sprite neste momento
		char far *savebuffer;   // Ponteiro para o array a fim de
								// salvar o fundo do sprite
	public:
		// Constructor para a classe sprite:
		Sprite(int num_sprites, int width, int height);
		// Funcao grabber do sprite:
		void grab(unsigned char far *buffer, int sprite_num,
			int x1, int y1);
		// Funcao para exibir o sprite:
		void put (int sprite_num, int x, int y,
			unsigned char far *screen);
		// Funcao para apagar a imagem do sprite
		void erase(unsigned char far *screen);
};