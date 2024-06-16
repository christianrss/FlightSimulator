#include <stdio.h>
#include <stdlib.h>
#include <conio.h>
#include <dos.h>
#include "SCREEN.H"
#include "PCX.H"

pcx_struct pcxbuf; // buffer para os dados do PCX
Pcx pcxloader;     // Objeto para carregamento de PCX

void main(int argc, char* argv[])
{
	if (argc!=2) { // Existem dois argumentos na linha de comando?
		puts("Numero de argumentos incorreto.\n"); // se nao
		exit(0); // Finaliza com erro
	}

	if (pcxloader.load(argv[1], &pcxbuf))
	{
		puts("Erro ao abrir o arquivo PCX.\n");
		exit(0);
	}
	// exibe o PCX
	cls((char *)MK_FP(0xa000,0)); 		  // Limpa a tela
	int oldmode=*(int *)MK_FP(0x40,0x49); // Ativa modo VGA
	setmode(0x13); 						  // para 320x200x256
	setpalettex(pcxbuf.palette);   // Ativa paleta PCX

	// Cria ponteiro para o monitor de video
	char far *screen=(char far*) MK_FP(0xa000,0);

	// percorre todos os 64.000 bytes, exibindo cada um
	for (long i=0; i<64000; i++) screen[i]=pcxbuf.image[i];

	// Manter a tela ate que uma tecla seja pressionada, entao
	// restaurar o modo de videoe sair para o DOs
	while (!kbhit()); 	  // Espera uma tecla ser pressionada
	setmode(oldmode); // Restaura antigo modo de video
}