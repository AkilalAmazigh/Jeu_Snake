#include <stdio.h>
#include <stdlib.h>
#include <windows.h>
#include <conio.h>
#include <time.h>

//Déclaration des variables globales

#define N 20
#define M 40

int i,j,champs[N][M],x,y,Gy,tete,queue,jeu,pomme,a,b,var,dir,score,vitesse;

//signature des fonctions du jeu

void snakeInitialization();
void print();
void ResetScreenPosition();
void Random();
int getch_noblock();
void movement();
void TailRemove();
void GameOver();


// Programme principal
void main()
{
    snakeInitialization();

    while(jeu == 0)
    {
        print();
        ResetScreenPosition();
        Random();
        movement();
        TailRemove();
        Sleep(vitesse);
    }
}