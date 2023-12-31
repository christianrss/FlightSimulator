#include <stdio.h>
#include <dos.h>
#include <io.h>
#include <fcntl.h>
#include <mem.h>

#ifndef __PCX__
	#include "PCX.H"
#endif

const long IMAGE_SIZE=64000;

int Pcx::load(char far *filename, pcx_struct *pcx)
{
	// Funcao para carregar dados PCX de um arquivo FILENAME
	// para a estrutura PCX.
	//abrir o arquivo; retornar valor nao-zero em caso de erro
	if ((infile=open(filename, O_BINARY))==NULL)
		return(-1);

	// Mover o ponteiro para o arquivo ate o inicio do cabecalho
	lseek(infile, 0L, SEEK_SET);
	// Ler o cabecalho do arquivo PCX:
	int readlen=read(infile, &(pcx->header), sizeof(pcx_header));


	// Descomprimir o bitmap e coloca-lo no buffer
	load_image(infile,pcx);
	// Descomprimir a paleta e armazenar em array:
	load_palette(infile, pcx);
	close(infile); // Fechar arquivo PCX
	return(0);

}

void Pcx::load_image(int pcxfile, pcx_struct *pcx)
{
	// Constantes simbolicas para modos de codificao, com
	// BYTEMODE representando o modo descomprimido do byte
	// e RUNMODE representando o modo codificado run-length

	const int BYTEMODE=0, RUNMODE=1;

	// Buffer para os dados lidos do disco:
	const int BUFLEN=5*1024;
	int mode = BYTEMODE; // Modo de codificacao corrente,
						 // ativado inicialmente para BYTEMODE
	int readlen;		 // numero de caracteres lidos do arquivo

	static unsigned char outbyte;   	// Proximo byte para o buffer
	static unsigned char bytecount; 	// Contador de carreiras
	static unsigned char buffer[BUFLEN];// buffer lido do disco

	// Alocar memoria para o buffer do bitmap
	pcx->image=new unsigned char[IMAGE_SIZE];

	int bufptr=0; // Apontar para o inicio do buffer
	readlen=0; 	  // Zero caracteres lidos ate agora

	// Criar ponteiro para o inicio da imagem:
	unsigned char *image_ptr=pcx->image;

	// Fazer um loop para o buffer do bitmap em toda sua extensao:
	for (long i=0; i<IMAGE_SIZE; i++)
	{
		if (mode==BYTEMODE)
		{
			// se estamos no modo de bytes
			// individuais ...
			if (bufptr>=readlen)   // se chegamos ao fim do buffer
			{
				bufptr=0; // apontar para o comeco
				// Ler mais bytes do arquivo para o buffer;
				// Se nao houver mais bytes, interrompa o loop
				if ((readlen=read(pcxfile, buffer, BUFLEN)) == 0)
					break;
			}
			outbyte=buffer[bufptr++]; // Proximo byte do bitmap
			if (outbyte>0xbf) // se indicacao de run-length...
			{
				// calcular o numero de bytes na carreira
				bytecount = (int)((int)outbyte & 0x3f);
				if (bufptr>=readlen) // verifica se passou do final do buffer
				{
					bufptr = 0; // aponta para o inicio
					// Ler mais bytes do arquivo para o buffer
					// se nao houver mais bytes sobrando, interroper o loop
					if ((readlen=read(pcxfile, buffer, BUFLEN))==0)
						break;
				}
				outbyte=buffer[bufptr++]; // proximo byte do bitmap
				// chavear para o modo run-length
				if (--bytecount > 0) mode = RUNMODE;
			}
			// Chavear para o modo individual
		}  else if (--bytecount == 0) mode = BYTEMODE;

		// acrescentar o proximo byte ao buffer do bitmap:
		*image_ptr++=outbyte;
	}

}

void Pcx::load_palette(int pcxfile, pcx_struct *pcx)
{
	// carregar registros de valores de cor do arquivo para o array da paleta

	// Posicionar no inicio da pleta, que esta sempre a 768 bytes
	// do final do arquivo
	lseek(pcxfile,-768L,SEEK_END);
	// Ler todos os 768 registros da paleta para o array
	read(pcxfile, pcx->palette,3*256);
	// Ajustar para o deslocamento de bit requerido:
	for (int i=0; i<256; i++)
		for (int j=0; j<3; j++)
			pcx->palette[i*3+j]=pcx->palette[i*3+j]>>2;
}