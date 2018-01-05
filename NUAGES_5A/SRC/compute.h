
#include <gtk/gtk.h>

#define LargeurImage 360
#define PRE 1
#define NB_CLUSTERS 5
#define NB_POINTS (2 * PRE + 1) * (2 * PRE + 1)

void ComputeImage(guchar *pucImaOrig, 
		  int uiNbCol, 
		  int uiNbLine,
		  guchar *pucImaRes);
