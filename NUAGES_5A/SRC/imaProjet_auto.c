/*
 * This program displays the names of all files in the current directory.
 */

#include <dirent.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "compute.h"

unsigned char* readBMP(char* filename, int* nbLine, int* nbCol)
{
  int i;
  FILE* f = fopen(filename, "rb");
  unsigned char info[54];
  fread(info, sizeof(unsigned char), 54, f);

  (*nbLine) = *(int*)&info[18];
  (*nbCol) = *(int*)&info[22];

  int size = 3 * (*nbLine) * (*nbCol);
  unsigned char* data = malloc(size * sizeof(unsigned char));
  fread(data, sizeof(unsigned char), size, f);
  fclose(f);

  for(i = 0; i < size; i += 3)
  {
    unsigned char tmp = data[i];
    data[i] = data[i+2];
    data[i+2] = tmp;
  }

  return data;
}

void print_help(char* argv[])
{
  printf("Usage: %s directory_name\n", argv[0]);
}

int main(int argc, char* argv[])
{
  DIR           *d;
  struct dirent *dir;
  if (argc != 2)
  {
    print_help(argv);
    return 0;
  }
  d = opendir(argv[1]);
  if (d)
  {
    while ((dir = readdir(d)) != NULL)
    {
      if (strstr(dir->d_name, ".bmp"))
      {
        int nbLine = 0, nbCol = 0;
        char *copy = malloc((strlen(argv[1]) + strlen(dir->d_name)) * sizeof(char) + 2);
        strcpy(copy, argv[1]);
        strcat(copy, "/");
        strcat(copy, dir->d_name);
        printf("%s\n", dir->d_name);
        unsigned char *image = readBMP(copy, &nbLine, &nbCol);
        unsigned char *image_copy = malloc(nbLine * nbCol * sizeof(unsigned char));
        ComputeImage(image, nbLine, nbCol, image_copy);
      }
    }
    closedir(d);
  }
  return 0;
}
