// RAINBOW.CPP
// Um programa que exibe a paleta VGA default
#include	<stdio.h>
#include	<conio.h>
#include	<dos.h>
#include	"SCREEN.H"

void main()
{
	// Limpar o monitor VGA:
	cls((char*)MK_FP(0xa000,0));
	// Salvar o modo de video anterior:
	int oldmode=*(int *)MK_FP(0x40,0x49);
	// Ativar o modo de video 320x200x256;
	setmode(0x13);
	// Criar um ponteiro para memoria de video
	char far *screen=(char far *)MK_FP(0xa000,0);
	// Fazer um loop por todos os 200 pixels de uma coluna:
	for (int i=0; i<200; i++)
		for (int j=0; j<256; j++)
			// Colocando um pixel de cada cor em cada coluna:
			screen[i*320+j]=j;
	// Esperar ate que uma tecla seja pressionada
	while(!kbhit());
	// Entao, retornar ao modo antigo e voltar ao DOS:
	setmode(oldmode);

}