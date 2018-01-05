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
    unsigned char values[(NbCol - 2 * PRE) * (NbLine - 2 * PRE)][neigh_size];
    for (int x = 0; x < NbLine - 2 * PRE; x++)
    {
        for (int y = 0; y < NbCol - 2 * PRE; y++)
        {
            for (int i = 0; i < 2 * PRE + 1; i++)
                for (int j = 0; j < 2 * PRE + 1; j++)
                    values[x * (NbCol - 2 * PRE) + y][i * (2 * PRE + 1) + j] = pucImaRes[(x + i) * NbCol + (y + j)];

            printf("-----------\n");
            printf("-----------\n");
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][0]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][1]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][2]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][3]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][4]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][5]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][6]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][7]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][8]);

            for (int i = 0; i < neigh_size; i++)
            {
                for (int j = 0; j < neigh_size; j++)
                {
                    if (values[x * (NbCol - 2 * PRE) + y][i]
                      < values[x * (NbCol - 2 * PRE) + y][j])
                    {
                        unsigned char tmp        = values[x * (NbCol - 2 * PRE) + y][i];
                        values[x * (NbCol - 2 * PRE) + y][i] = values[x * (NbCol - 2 * PRE) + y][j];
                        values[x * (NbCol - 2 * PRE) + y][j] = tmp;
                    }
                }
            }

            printf("-----------\n");
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][0]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][1]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][2]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][3]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][4]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][5]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][6]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][7]);
            printf("%d\n", values[x * (NbCol - 2 * PRE) + y][8]);
        }
    }
}
