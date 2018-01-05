#include "compute.h"
#include <stdio.h>
#include <gtk/gtk.h>

/*******************************************************
IL EST FORMELLEMENT INTERDIT DE CHANGER LE PROTOTYPE
DES FONCTIONS
*******************************************************/


/*---------------------------------------
  Proto:


  But:

  Entrees:
      --->le tableau des valeurs des pixels de l'image d'origine
          (les lignes sont mises les unes à la suite des autres)
      --->le nombre de lignes de l'image,
      --->le nombre de colonnes de l'image,
          --->le tableau des valeurs des pixels de l'image resultat
          (les lignes sont mises les unes à la suite des autres)


  Sortie:

  Rem:

  Voir aussi:

  ---------------------------------------*/
void ComputeImage(guchar *pucImaOrig,
                  int NbLine,
                  int NbCol,
                  guchar *pucImaRes)
{
    int iNbPixelsTotal, iNumPix;
    int iNumChannel, iNbChannels = 3; /* on travaille sur des images couleurs*/
    guchar ucMeanPix;

    iNbPixelsTotal = NbCol * NbLine;
    for (iNumPix = 0;
         iNumPix < iNbPixelsTotal * iNbChannels;
         iNumPix = iNumPix + iNbChannels)
    {
        /* moyenne sur les composantes RVB */
        ucMeanPix = (unsigned char) ((*(pucImaOrig + iNumPix)
                                    + *(pucImaOrig + iNumPix + 1)
                                    + *(pucImaOrig + iNumPix + 2)) / 3);

        /* sauvegarde du resultat */
        for (iNumChannel = 0;
             iNumChannel < iNbChannels;
             iNumChannel++)
            *(pucImaRes + iNumPix + iNumChannel) = ucMeanPix;
    }

    int size = (NbCol - 2 * PRE) * (NbLine - 2 * PRE);
    int neigh_size = (2 * PRE + 1) * (2 * PRE + 1);
    unsigned char **values = malloc(size * sizeof(unsigned char*));
    for (int i = 0; i < size; ++i)
      values[i] = malloc(neigh_size * sizeof(unsigned char));
    for (int x = 0; x < NbLine - 2 * PRE; x++)
    {
        for (int y = 0; y < NbCol - 2 * PRE; y++)
        {
            for (int i = 0; i < 2 * PRE + 1; i++)
                for (int j = 0; j < 2 * PRE + 1; j++)
                    values[x * (NbCol - 2 * PRE) + y][i * (2 * PRE + 1) + j] = pucImaRes[3 * ((x + i) * NbCol + (y + j))];

            for (int i = 0; i < neigh_size; i++)
            {
                for (int j = 0; j < neigh_size; j++)
                {
                    if (values[x * (NbCol - 2 * PRE) + y][i]
                      > values[x * (NbCol - 2 * PRE) + y][j])
                    {
                        unsigned char tmp        = values[x * (NbCol - 2 * PRE) + y][i];
                        values[x * (NbCol - 2 * PRE) + y][i] = values[x * (NbCol - 2 * PRE) + y][j];
                        values[x * (NbCol - 2 * PRE) + y][j] = tmp;
                    }
                }
            }
        }
    }
    printf("Clouds: %.3f%% \n", k_means(values, size, 1000, 1));

    for (int x = 0; x < NbLine - 2 * PRE; x++)
    {
        for (int y = 0; y < NbCol - 2 * PRE; y++)
        {
            if (values[x * (NbCol - 2 * PRE) + y][0] != 0)
            {
                pucImaRes[3 * ((x + PRE) * NbCol + (y + PRE))] = 0;
                pucImaRes[3 * ((x + PRE) * NbCol + (y + PRE)) + 1] = 0;
                pucImaRes[3 * ((x + PRE) * NbCol + (y + PRE)) + 2] = 0;
            }
        }
    }
}
