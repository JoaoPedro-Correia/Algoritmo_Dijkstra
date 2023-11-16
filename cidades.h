#ifndef CIDADES_H
#define CIDADES_H
#include <stdio.h>
void printCidade(int cidade);

enum cidades_conectadas {
  Nelabamibec = 0,
  Daroowekeho,
  Duqacoxajio,
  Wuroseyuleb,
  Efoarabenac,
  Digexapuler,
  Elonupipufu,
  Koopomooqon,
  Wukaewusemu,
  Bauqolejivi,
  Wedaqebuixa,
  Veribejutis,
  Nowaqojuafi,
  Dorasofaben,
  Uvehefusuqe,
  Woquacuhehe,
  Varemenozik,
  Popuraxoite,
  Yuacohokecu,
  Coenitemogo,
  Wuwacapuiqu,
  Kiyidacodiw,
  Hoacaoharet,
  Qovacugipoo,
  Qosioagewun,
  Yoxozegogap,
  Berebonoade,
  Ugaumeqedau,
  Botikixuoac,
  Hedomexudey,
};

/*------------------------------------------------------------*/
void printCidade(int cidade) {
  if (cidade >= Nelabamibec && cidade <= Hedomexudey) {
    switch (cidade) {
    case (Nelabamibec):
      printf("Nelabamibec");
      break;
    case (Daroowekeho):
      printf("Daroowekeho");
      break;
    case (Duqacoxajio):
      printf("Duqacoxajio");
      break;
    case (Wuroseyuleb):
      printf("Wuroseyuleb");
      break;
    case (Efoarabenac):
      printf("Efoarabenac");
      break;
    case (Digexapuler):
      printf("Digexapuler");
      break;
    case (Elonupipufu):
      printf("Elonupipufu");
      break;
    case (Koopomooqon):
      printf("Koopomooqon");
      break;
    case (Wukaewusemu):
      printf("Wukaewusemu");
      break;
    case (Bauqolejivi):
      printf("Bauqolejivi");
      break;
    case (Wedaqebuixa):
      printf("Wedaqebuixa");
      break;
    case (Veribejutis):
      printf("Veribejutis");
      break;
    case (Nowaqojuafi):
      printf("Nowaqojuafi");
      break;
    case (Dorasofaben):
      printf("Dorasofaben");
      break;
    case (Uvehefusuqe):
      printf("Uvehefusuqe");
      break;
    case (Woquacuhehe):
      printf("Woquacuhehe");
      break;
    case (Varemenozik):
      printf("Varemenozik");
      break;
    case (Popuraxoite):
      printf("Popuraxoite");
      break;
    case (Yuacohokecu):
      printf("Yuacohokecu");
      break;
    case (Coenitemogo):
      printf("Coenitemogo");
      break;
    case (Wuwacapuiqu):
      printf("Wuwacapuiqu");
      break;
    case (Kiyidacodiw):
      printf("Kiyidacodiw");
      break;
    case (Hoacaoharet):
      printf("Hoacaoharet");
      break;
    case (Qovacugipoo):
      printf("Qovacugipoo");
      break;
    case (Qosioagewun):
      printf("Qosioagewun");
      break;
    case (Yoxozegogap):
      printf("Yoxozegogap");
      break;
    case (Berebonoade):
      printf("Berebonoade");
      break;
    case (Ugaumeqedau):
      printf("Ugaumeqedau");
      break;
    case (Botikixuoac):
      printf("Botikixuoac");
      break;
    case (Hedomexudey):
      printf("Hedomexudey");
      break;
    }
  }
}
#endif
