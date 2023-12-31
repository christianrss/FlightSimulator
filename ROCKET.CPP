#include <stdio.h>
#include <dos.h>
#include <conio.h>
#include <alloc.h>
#include <mem.h>
#include "SPRITE.H"
#include "PCX.H"
#include "SCREEN.H"
#include <time.h>
#include "ROCKETMODEL.H"
#include <math.h>
void putbuffer(unsigned char far *, int, int);

const int NUM_SPRITES=8; 	// Numero de imagens do sprite
const int SPRITE_WIDTH=24; 	// Largura do sprite em pixels
const int SPRITE_HEIGHT=24; // Altura do sprite em pixels
const int DELAY=40000;		// Fator de retardo para determinar
							// velocidade da animacao

double PREVIOUS_TIME = clock();

pcx_struct pcx,bg; 				// Estrutura para manter pcx
unsigned char far *screenbuf;	// Array de 64000 bytes para manter
								// imagens da tela
int rocket90[]={0,1};   // Sequencia das imagens para animacao
int rocket60[]={4,5};
int rocket30[]={2,3};
int rocket0[] ={6,7};

Pcx rocket, rocketbg;			// Objetos Pcx para carregar bitmaps
Sprite rocketsprite(NUM_SPRITES, SPRITE_WIDTH, SPRITE_HEIGHT); // Objeto Sprite

void main()
{
	int oldmode; // Armazenar o modo de video anterior;

	// Carregar arquivo PCX do fundo, aborta se nao encontra-lo
	if (rocket.load("rocket.pcx", &pcx))
		puts("Cannot load PCX file.\n");
	else {
		// iniciar a animacao
		cls((char *)MK_FP(0xa000,0)); 		// Limpar a tela
		oldmode=*(int *)MK_FP(0x40,0x49);	// Salva modo anterior
		setmode(0x13);						// Ativar modo de video 13h
		setpalettex(pcx.palette);			// Ativar paleta VGA com paleta PCX
		rocketbg.load("walkmanbg.pcx", &bg);		// Carregar sprite PCX
		screenbuf= new unsigned char[64000];// Criar buffer de video offscreen
		memmove(screenbuf, bg.image, 64000);// Mover imagem de fundo para o buffer

		putbuffer(screenbuf,0,SCREEN_HEIGHT); // Mover buffer offscreen para vidram

		// Carregar bitmap do sprite do bitmap PCX
		for(int i = 0; i < 7; i++)
			rocketsprite.grab(pcx.image,i,i*SPRITE_WIDTH,0);

		int rocketX = (320/2)-24/4;
		int rocketZ = (200-24);

		RocketSimModel rocketSimModel = RocketModel::SetSimModel();
		// Loop repetidamente pelos quadros da animacao, movendo
		// a imagem do lado esquerdo do monitor de video para o direito
		while(rocketSimModel.rocket.s < rocketSimModel.rocket.burnTime)
		{
			RocketModel::rocketRungeKutta4(
				&rocketSimModel.rocket,
				rocketSimModel.dt
			);

			rocketSimModel.time = rocketSimModel.rocket.s;
			rocketSimModel.x = rocketSimModel.rocket.q[1];
			rocketSimModel.z = rocketSimModel.rocket.q[5];
			rocketSimModel.mass = rocketSimModel.rocket.q[7];
			rocketSimModel.v = sqrt(
				rocketSimModel.rocket.q[0] *
				rocketSimModel.rocket.q[0] +
				rocketSimModel.rocket.q[2] *
				rocketSimModel.rocket.q[2] +
				rocketSimModel.rocket.q[4] *
				rocketSimModel.rocket.q[4]
			);

			double theta = rocketSimModel.rocket.q[9] * 180.0 / rocketSimModel.pi;

			double CURRENT_TIME = clock();
			double DELTA_TIME = CURRENT_TIME - PREVIOUS_TIME;
			if (DELTA_TIME > 0.0)
			{
				PREVIOUS_TIME = CURRENT_TIME;
			}

			//Desenhar o Foguete na tela
			rocketX = -(int)((rocketSimModel.x * 0.1) );
			//	if (rocketZ < 200)
			rocketZ = (int)(SCREEN_HEIGHT - SPRITE_HEIGHT) + (int) ( (rocketSimModel.z * 0.01));

			if (rocketX < 320 && rocketZ < 200) {
				for (int i = 0; i < 2; i++)
				{
					if (theta < 12.0)
						rocketsprite.put(rocket0[i],rocketX,rocketZ,screenbuf);
					else if (theta < 40.0)
						rocketsprite.put(rocket30[i],rocketX,rocketZ,screenbuf);
					else if (theta < 70.0)
						rocketsprite.put(rocket60[i],rocketX,rocketZ,screenbuf);
					else
						rocketsprite.put(rocket90[i],rocketX,rocketZ,screenbuf);
					// Mover o segmento do buffer do video para a memoria do video
					putbuffer(screenbuf,0,200);
					rocketsprite.erase(screenbuf);
					while((clock() - CURRENT_TIME) * 1000 / CLOCKS_PER_SEC < 100)
					{
						asm{ hlt };
					}
				}
			   //	rocketsprite.erase(screenbuf);
			}
			while ((clock() - CURRENT_TIME) * 1000 / CLOCKS_PER_SEC < 200)
			{
				asm{ hlt };
			}

			//rocketsprite.erase(screenbuf);
			//putbuffer(screenbuf,rocketZ,SPRITE_HEIGHT);
			if (kbhit()) break;
		}
		for (;;) if (kbhit()) break;
		setmode(oldmode);

	}
}

void putbuffer(unsigned char far *screenbuf, int y1,int height)
{
	// Mover buffer offscreen para a vidram
	char far *screen=
		(char far *) MK_FP(0xa000,0); // Apontar para memoria de video
	// Chamar funcao da biblioteca, MEMMOVE(), para mover dados
	// para a memoria de video
	memmove(
		screen+y1*SCREEN_WIDTH,
		screenbuf+y1*SCREEN_WIDTH,
		height*SCREEN_WIDTH
	);
}