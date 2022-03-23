#include <stdio.h>
#include <windows.h>
#include <stdlib.h>
#include <conio.h>
#include <time.h>

//Déclaration des variables globales

#define N 20 // definition des rows (hauteur des bordures)
#define M 40 // definition des columns(largeur des bordures)

int i,j;
int champ[N][M];//champs sous forme de tableau(matrice)
int x, y, Gy;
int tete, queue;
int pommes, a, b;//a et b pour les positions(coordonnées) aléatoires des pommes;
int jeu;
int var;//qui prend la valeur sasie par l'utilisateur sur le clavier
int dir,score,vitesse;

//signature des fonctions du jeu

void initialisation_serpent();
void afficher();
void ResetScreenPosition();
void generer_pomme();
int getch_noblock();
void mouvement();
void effacer_queue();
void GameOver();

//programme principal

void main()
{
    initialisation_serpent();

    while(jeu == 0)// jeu en cours (si jeu == 1, jeu = terminé)
    {
        afficher();
        ResetScreenPosition();
        generer_pomme();
        mouvement();
        effacer_queue();
        Sleep(vitesse);/*a chaque fois que le serpent mange une pomme 
                        la vitesse descend de 5, on l'assignant a la fonction
                        sleeep, le temps de sleep diminue donc la vitesse augmente*/
    }
}

void initialisation_serpent()
{
    for(i=0;i<N;i++){
        for(j=0;j<M;j++){
            champ[i][j]=0;//pour dire que le champ est vide
        }
    }

    x = N/2; y = M/2;//initialiser les coordonnées x et y au centre (x a 10, et y a 20)
    Gy = y; //Gy=20
    tete = 5;
    queue = 1;
    jeu = 0; // jeu en cours (si jeu = 1, jeu = terminé)
    pommes = 0; //initialiser les pommes a 0 (pas de pommes)
    dir='d';//initialiser la direction a d (direction droite)
    score=0;
    vitesse = 99;

    for(i=0;i<tete;i++)//le reste du corps entre 1(queue) et 5(tete)
    {
        Gy++;//21;22...
        champ[x][Gy-tete] = i+1;//1=champ[10][16(21-5)]; 2=[10][17(22-5)]; 3=...; 4=...
    }
}

void afficher(){
    // impression des caracteres pour former le contour de la fenetre (cote superieur)
    for(i=0;i<=M+1;i++){
        if(i==0)// coin haut gauche
        {
            printf("%c",201);
        }else if(i==M+1)// coin haut droit
        {
            printf("%c",187);
        }else// entre les deux coins du haut
        {
            printf("%c",205);
        }
    }
    printf("   Score: %d ",score);
    printf("\n");//passer a la deuxième ligne
    // impression des caracteres pour les cotés et l'interieur de la fenetre
    for(i=0;i<N;i++)//coté gauche de la fenetre
    {
        printf("%c",186);//caractere coté gauche de la fenetre

        for(j=0;j<M;j++)//coté gauche
        {
            if(champ[i][j]==0) printf(" ");//espace vide si rien dans le champs
            if(champ[i][j]>0 && champ[i][j]!=tete) printf("%c",176);// caractere du corps, si champs = au corps du serpent de 1 à 4 (!= de tete)
            if(champ[i][j]==tete) printf("%c",178);//caractere de la tete (si champs = à 5(la tete))
            if(champ[i][j]==-1) printf("%c",15);//caractere de la pomme(si champs = à -1(la pomme))
            if(j==M-1) printf("%c\n",186);//caractere coté droit de la fenetre
        }
    }
    // impression des caracteres pour former le contour de la fenetre (cote inferieur)
    for(i=0;i<=M+1;i++){
        if(i==0)// coin bas gauche
        {
            printf("%c",200);
        }else if(i==M+1)//coin bas droit 
        {
            printf("%c",188);
        }else//entre les deux coins du haut
        {
            printf("%c",205);
        }
    }
}
void ResetScreenPosition()/*pour remettre le curseur à chaque fin de 
                        boucle d'affichage au debut de la page pour ne
                        pas creer de nouvelle fenetre a chaque fois et
                        avoir une infinitée de fenetres qui défile */
{
    HANDLE hOut;// variable de type HANDLE
    COORD Position;
    hOut = GetStdHandle(STD_OUTPUT_HANDLE); //on assigne la fonction a la var hout
    //placer les coordonées au debut de l'ecran
    Position.X = 0;
    Position.Y = 0;
    SetConsoleCursorPosition(hOut,Position);// appel de la fonction avec les deux parametre déclarés
}


void generer_pomme(){
    srand(time(0));/* Initialiser le générateur aleatoire en se basant sur l'heure de
                    la machine et qui produit des nombres differents a chaque instant*/
    a = 1+ rand() % 18;// generer un nombre entre 0 et 18
    b = 1 + rand() % 38;// generer un nombre entre 0 et 38

    if(pommes == 0 && champ[a][b]==0)/*verifier si il ya déja une pomme ou pas(=0)
                                       et verifier si le champ est vide (=0) pour 
                                       ne pas creer une pomme sur le serpent */
    {
        champ[a][b]= -1; // on assigne la valeur -1 aux coord (a,b)
        pommes = 1;// actualiser la valeur de pommes a 1 au lieu de 0(pas de pommmes)
        if(vitesse>10 && score!=0) vitesse = vitesse - 5; //pour augmenter la vitesse
    }
}

int getch_noblock()//recuperation des valeurs saisie sur le clavier
{
    if(_kbhit())//si le clavier est touché 
        return _getch(); //retourn la valeur du charactère touché sur le clavier
    else
        return -1;// retourner la valeur de -1 qui est (rien)
}

void mouvement(){
    var = getch_noblock();//appel de la fonction 
    var = tolower(var);/*fonction pour convertir les maj et min en miniscule pour ne pas
                         avoir a se prendre la tete sur : si la touche maj est activé ou pas*/
    if(((var=='d'||var=='a')||(var=='w'||var=='s'))
       &&(abs(dir-var)>5)) dir = var;
       //valeur absolue de dir - var > 5 (sa taille etant de 5 pour ne pas revenir sur lui meme)
    
    if(dir =='d')//si on appuie sur d (direction droite)
    {
        y++;//y augmente de 1 a chaque fois
        if(y==M-1) y = 0;//pour le retour a au debut de la ligne
        if(champ[x][y]!=0 && champ[x][y]!=-1) GameOver();//ça veut dire que le serpent s'est touché le corps
        if(champ[x][y]==-1)//si la tete du serpent se trouve sur la valeur de la pomme(-1)
        {
            pommes = 0;//valeur 0, pas de pommes, il y'aura donc appel d'une pomme
            score+=5;
            queue -= 1;//la qeue augmente de 1, en diminuant sa valeur de 1
        }

        tete++;//la tete se deplace une fois
        champ[x][y] = tete;
    }

    if(dir =='a')//direction gauche
    {
        y--;//y diminue de 1 a chaque fois
        if(y==0) y = M-1;//pour le retour a la fin de la ligne
        if(champ[x][y]!=0 && champ[x][y]!=-1) GameOver();//ça veut dire que le serpent s'est touché le corps
        if(champ[x][y]==-1)//si la tete du serpent se trouve sur la valeur de la pomme(-1)
        {
            pommes = 0;//valeur 0, pas de pommes, il y'aura donc appel d'une pomme
            score+=5;
            queue -= 1;//la qeue augmente de 1, en diminuant sa valeur de 1
        }
        tete++;//la tete se deplace une fois
        champ[x][y] = tete;
    }

    if(dir =='w')//direction nord (haut)
    {
        x--;//x diminue de 1 a chaque fois
        if(x==-1) x = N-1;//pour le retour a la fin de la ligne
        if(champ[x][y]!=0 && champ[x][y]!=-1) GameOver();//ça veut dire que le serpent s'est touché le corps
        if(champ[x][y]==-1)//si la tete du serpent se trouve sur la valeur de la pomme(-1)
        {
            pommes = 0;//valeur 0, pas de pommes, il y'aura donc appel d'une pomme
            score+=5;
            queue -= 1;//la qeue augmente de 1, en diminuant sa valeur de 1
        }
        tete++;//la tete se deplace une fois
        champ[x][y] = tete;
    }

    if(dir =='s')//direction sud (bas)
    {
        x++;//x augmente de 1 a chaque fois
        if(x==N-1) x = 0;//pour le retour au debut de la ligne
        if(champ[x][y]!=0 && champ[x][y]!=-1) GameOver();//ça veut dire que le serpent s'est touché le corps
        if(champ[x][y]==-1)//si la tete du serpent se trouve sur la valeur de la pomme(-1)
        {
            pommes = 0;//valeur 0, pas de pommes, il y'aura donc appel d'une pomme
            score+=5;
            queue -= 1;//la qeue augmente de 1, en diminuant sa valeur de 1
        }
        tete++;//la tete se deplace une fois
        champ[x][y] = tete;
    }
}

void effacer_queue()//pour que la que accompagne le serpent dans son déplacement
{
    for(i=0;i<N;i++)
    {
        for(j=0;j<M;j++)
        {
            if(champ[i][j]==queue)//si le champ correspond a la queue
            {
                champ[i][j] = 0;//vider l'espace dans le champs
            }
        }
    }
    queue++;//la queue se deplacera a la case suivante
}

void GameOver(){
    printf("\a");// pour faire un son, un bip
    Sleep(1500);//marquer une pause de 1500 ms
    system("Cls");//pour vider l'ecran / clear screen

    system("Cls");
    printf("\n\n         Game OVER !!!!!!\n");
    printf("             Score : %d \n\n",score);
    printf("             appuyez sur entree pour jouer a nouveau ou Echap pour sortir ... \n");


    while(1)
    {
        var = getch_noblock();//appel fonction recuperation valeurs saisies
        if(var == 13)//correspont a la touche entree
        {
            jeu = 0;//jeu devient en cours
            initialisation_serpent();//redemarer le jeu
            break;
        }
        else if(var == 27)//correspont a la touche Echap
        {
            jeu = 1;//jeu devient terminé
            break;
        }
    }
    system("Cls");//vider l'ecran
}

