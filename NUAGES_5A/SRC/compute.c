#include <stdio.h>
#include <gtk/gtk.h>

#define PRE 1

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

    int neigh_size = (2 * PRE + 1) * (2 * PRE + 1);
    unsigned char values[(NbCol - 1) * (NbLine - 1)][neigh_size];
    for (int x = PRE; x < NbLine - PRE; x++)
    {
        for (int y = PRE; y < NbCol - PRE; y++)
        {
            for (int i = -PRE; i <= PRE; i++)
                for (int j = -PRE; j <= PRE; j++)
                    values[(x - 1) * NbCol + (y - 1)][i * PRE + j] = pucImaRes[(x + i) * NbCol + (y + j)];

            printf("-----------\n");
            printf("-----------\n");
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][0]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][1]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][2]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][3]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][4]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][5]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][6]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][7]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][8]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][9]);

            for (int i = 0; i < neigh_size; i++)
            {
                for (int j = 0; j < neigh_size; j++)
                {
                    if (values[(x - 1) * NbCol + (y - 1)][i]
                      < values[(x - 1) * NbCol + (y - 1)][j])
                    {
                        unsigned char tmp                    = values[(x - 1) * NbCol + (y - 1)][i];
                        values[(x - 1) * NbCol + (y - 1)][i] = values[(x - 1) * NbCol + (y - 1)][j];
                        values[(x - 1) * NbCol + (y - 1)][j] = tmp;
                    }
                }
            }

            printf("-----------\n");
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][0]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][1]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][2]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][3]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][4]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][5]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][6]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][7]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][8]);
            printf("%d\n", values[(x - 1) * NbCol + (y - 1)][9]);
        }
    }
}
