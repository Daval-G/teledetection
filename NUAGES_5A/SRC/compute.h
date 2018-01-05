
#include <gtk/gtk.h>
#include <stdlib.h>

#define LargeurImage 360
#define PRE 1
#define NB_CLUSTERS 5
#define NB_POINTS (2 * PRE + 1) * (2 * PRE + 1)

double k_means(unsigned char **x_values, int size, int max_iterations, double min_distance);

void ComputeImage(guchar *pucImaOrig, 
		  int uiNbCol, 
		  int uiNbLine,
		  guchar *pucImaRes);
