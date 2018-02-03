#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define TAILLE 75
#define AVATAR '@'
#define DIRECTION 'S'
#define BLANC ' '
#define NOIR '*'

typedef struct tableau_struct{
  int taille;
  char tableau[TAILLE][TAILLE];
}zone;
typedef struct fourmi_struct{
  int posX;
  int posY;
  int posTempX;
  int posTempY;
  char avatar;
  char direction; // N,S,E,O
}fourmi;
int getIteration(){
  int iterations;
  printf("Veuillez saisir le nombre d'itérations > ");
  scanf("%d", &iterations);
  return iterations;
}
zone initGrille(){
  zone grille;
  int i, j;
  for(i=0; i<TAILLE; i++){
    for(j=0; j<TAILLE; j++){
      grille.tableau[i][j] = BLANC;
    }
  }
  return grille;
}
int afficherGrille(zone grille, fourmi maFourmi){
  int i, j;
  for(i=0; i<TAILLE; i++){
    for(j=0; j<TAILLE; j++){
      if(maFourmi.posX == i && maFourmi.posY == j){
        printf("%c", maFourmi.avatar);
      }else{
        printf("%c", grille.tableau[i][j]);
      }
    }
    printf("\n");
  }
  return 0;
}
fourmi bougerFourmi(zone grille, fourmi maFourmi){
  // On bouge la pos de fourmi en fonction de initGrille
  // Puis on renvoie juste fourmi
  maFourmi.posTempX = maFourmi.posX;
  maFourmi.posTempY = maFourmi.posY;
  if(grille.tableau[maFourmi.posX][maFourmi.posY] == BLANC){ // BLANC
    if(maFourmi.direction == 'N'){
      maFourmi.posX = maFourmi.posX + 1;
      maFourmi.direction = 'E';
    }
    else if(maFourmi.direction == 'S'){
      maFourmi.posX = maFourmi.posX - 1;
      maFourmi.direction = 'O';
    }
    else if(maFourmi.direction == 'E'){
      maFourmi.posY = maFourmi.posY + 1;
      maFourmi.direction = 'S';
    }
    else if(maFourmi.direction == 'O'){
      maFourmi.posY = maFourmi.posY - 1;
      maFourmi.direction = 'N';
    }
  }
  else if(grille.tableau[maFourmi.posX][maFourmi.posY] == NOIR){ // BLANC
    if(maFourmi.direction == 'N'){
      maFourmi.posX = maFourmi.posX - 1;
      maFourmi.direction = 'O';
    }
    else if(maFourmi.direction == 'S'){
      maFourmi.posX = maFourmi.posX + 1;
      maFourmi.direction = 'E';
    }
    else if(maFourmi.direction == 'E'){
      maFourmi.posY = maFourmi.posY - 1;
      maFourmi.direction = 'N';
    }
    else if(maFourmi.direction == 'O'){
      maFourmi.posY = maFourmi.posY + 1;
      maFourmi.direction = 'S';
    }
  }
  //printf("Position après : posX : %d et posY : %d\n", maFourmi.posX, maFourmi.posY);
  return maFourmi;
}
zone majGrille(zone grille, fourmi maFourmi){
  // On mettra a jour la grille en fonction de la fourmi
  //printf("%c\n", grille.tableau[maFourmi.posTempX][maFourmi.posTempY]);
  if(grille.tableau[maFourmi.posTempX][maFourmi.posTempY] == BLANC){
    grille.tableau[maFourmi.posTempX][maFourmi.posTempY] = NOIR;
  }
  else{
    grille.tableau[maFourmi.posTempX][maFourmi.posTempY] = BLANC;
  }
  //printf("%c\n", grille.tableau[maFourmi.posTempX][maFourmi.posTempY]);
  return grille;
}
int main(){
  int iterations;
  int i;
  int usleep_var;
  zone grille;
  fourmi maFourmi;
  maFourmi.posX = TAILLE/2;
  maFourmi.posY = TAILLE/2;
  maFourmi.avatar = AVATAR;
  maFourmi.direction = DIRECTION;

  iterations = getIteration();
  grille = initGrille();
  afficherGrille(grille, maFourmi);
  for(i=0; i<iterations ; i++){
    printf("\e[1;1H\e[2J");
    usleep(30000);
    maFourmi = bougerFourmi(grille, maFourmi);
    grille = majGrille(grille, maFourmi);
    afficherGrille(grille, maFourmi);
    printf("Itérations : %d\n", i);
  }
}
