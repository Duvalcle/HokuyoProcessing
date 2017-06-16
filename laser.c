// Programme de lancement acquisition des points
// Created on 24/03/2017 by C.Duval

#include <stdio.h>
#include <string.h>
#include "serial.h"
#include "brut_input.h"
#include "traitement.h"

#include <errno.h>
#include <fcntl.h>
#include <string.h>
#include <termios.h>
#include <unistd.h>

/*#define 0_RDWR
#define 0_NOCTTY
#define 0_SYNC*/
#define SIZE_BUF 2
#if defined _BSD_SOURCE || defined _SVID_SOURCE
 #define __USE_MISC     1
#endif


int main(void){

  // *** Etablissement liaison série *** //
  char *portname = "/dev/ttyACM0";
  //char *portname = "exemple.txt";
  int fd; //File Descriptor
  int wlen;
  int first_time=1;
  int nb_lines = 0;
  char hexc_Left[3];
  char hexc_Right[3];
  Point_carth points_C[720];
  float angle = -90; //angle actuel du détecteur !à réactualisation flux continu
  int cpt_pts = 0; // Index du tabeau de points_P

  int cpt_LR = 0; // Compteur savoir si poids fort ou faible décomptage

  unsigned char buf[SIZE_BUF]={'\0'};
  int rdlen, i=0;
  char c;
  char Left_res[9];
  char Right_res[9];
  char Total_Bin_Res[13];
  int distance;
  char side_play;

//  printf("sélectionner le cote de jeu (B/J):\n");
//  scanf("%c",&side_play);
  fd = open(portname, O_RDWR | O_NOCTTY | O_SYNC);
  if (fd < 0) {
     printf("Error opening %s: %s\n", portname, strerror(errno));
     return -1;
  }
  else if (fd > 0) {
     printf("open successfully \n");
  }
  /*baudrate 9600, 8 bits, no parity, 1 stop bit */
  set_interface_attribs(fd, B115200);
  set_mincount(fd, 0);                /* set to pure timed read */

//choix du mode d'encodage, demande de mesure
  printf("encodage 2 caractères\n");
  wlen = write(fd, "MS0180090000101\n", 17); //Lancement du Scan //choix encodage 2 caracères

  if (wlen != 17) {
     printf("Error from write: %d, %d\n", wlen, errno);
  }
  tcdrain(fd);    /* delay for output */


  /* simple noncanonical input */
  //Read Header of the file
/*  for (int i=0;i<38;i++){
    read(fd, &c, 1);
  }
*/  while (1) {
    rdlen = read(fd, &c, 1);
    if (rdlen > 0) {
      buf[cpt_LR]=c;
    }
    while (c!='\n'){
      if (cpt_LR == 1){
        //if(cpt_LR ==0){
        charToHex(buf[0], hexc_Left);
        charToHex(buf[1], hexc_Right);
        hexc_Left[0]=hexc_Left[0]-3; //On retire 0x30 en hexa au 1er caractère
        hexc_Right[0]=hexc_Right[0]-3; //On retire 30H au 2ème caractère
        // à faire pour le gauche
        HexToBinary(hexc_Left,Left_res);
        HexToBinary(hexc_Right,Right_res);
        fusion(Left_res,Right_res,Total_Bin_Res);
        distance = binaryToDecimal(Total_Bin_Res);
        distance = distance + 63; // On compense une erreur systématique du décodage
        //printf("%d\n",distance);
        points_C[cpt_pts] = PolaireToCarth(point_new_P(angle, distance)); //passage coordonnées polaires en carthésiennes
        printf("%d\t ; \t%d\n", points_C[cpt_pts].x, points_C[cpt_pts].y);
        angle += 0.25; // résolution du capteur en °
      }
      cpt_LR=(cpt_LR+1)%2;
      rdlen = read(fd, &c, 1);
      if (rdlen > 0) {
        buf[cpt_LR]=c;
      }
    }
    cpt_LR=0;
    nb_lines++;
  }
  return 0;
}
