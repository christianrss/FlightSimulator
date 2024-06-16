struct pcx_header {
	char	manufacturer;	  	  // Sempre 0
	char 	version;              // Sempre em 5 para arquivos em 256 cores
	char 	encoding;			  // Sempre em 1
	char 	bits_per_pixel;	      // Deve ser 8 para arquivos em 256 cores
	int 	xmin,ymin;			  // Coordenadas do canto superior esquerdo
	int 	xmax,ymax;			  // Largura e altura da imagem
	int 	hres;				  // Resolucao horizontal da imagem
	int 	vres;				  // Resolucao vertical da imagem
	char	palette16[48];		  // Paleta EGA; nao utilizada
									// para arquivos 256 cores
	char 	reserved;
	char 	color_planes;		  // Plano de cores
	int		bytes_per_line;		  // Numero de bytes em 1 linha
									// de pixels
	int		palette_type;		  // Deve ser 2 para paleta colorida
	char 	filler[58];			  // lixo
};

struct pcx_struct {
	pcx_header header;				// Esturtura para conter o cabecalho PCX
	unsigned char far *image;   	// Ponteiro para um buffer que contem
									//	o bitmap de 64000 bytes
	unsigned char far *cimage;		// Aponta para um buffer contendo
									//	uma versao comprimida do
									//	bitmap PCX
	unsigned char palette[3*256];  	// Array contendo os 768
									// bytes da paleta
	int clength;					// Tamanho do bitmap comprimido

};

class Pcx
 //Classe para carregar arquivos tipo PCX em 256 cores VGA
{
	private:
		int infile;
		// funcao que carrega o bitmap:
		void load_image(int pcxfile, pcx_struct *pcx);
		// Funcao que carrega a paleta:
		void load_palette(int pcxfile, pcx_struct *pcx);
	public:
		// Funcao que carrega dados PCX:
		int load(char far *filename, pcx_struct *pcx);
		// Funcao que comprime o bitmap PCX
		int compress(pcx_struct *pcx);
};