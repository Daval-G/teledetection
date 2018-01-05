#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "compute.h"

int minimized_distances(int **means, int **old_means, double min_distance)
{
  for (int i = 0; i < NB_CLUSTERS; ++i)
  {
    double distance = 0;
    for (int j = 0; j < NB_POINTS; ++j)
      distance += (means[i][j] - old_means[i][j]) * (means[i][j] - old_means[i][j]);
    if (distance > min_distance)
      return 0;
  }
  return 1;
}

int get_max_label(int **means)
{
  int max_label = 0;
  int max = 0;
  for(int i = 0; i < NB_CLUSTERS; ++i)
  {
    int mean = 0;
    for(int j = 0; j < NB_POINTS; ++j)
      mean += means[i][j];
    if (mean > max)
    {
      max = mean;
      max_label = i;
    }
  }
  return max_label;
}

double treat_image(unsigned char **x_values, int size, int *lengths, int *labels, int **means)
{
  int label = get_max_label(means);
  for (int i = 0; i < size; ++i)
  {
    if (labels[i] != label)
      x_values[i][0] = 0;
  }
  return (double)lengths[label] / size * 100;
}

int get_min(unsigned char **x_values, int size)
{
  int min = NB_POINTS * 256 * 256;
  for (int i = 0; i < size; ++i)
    if (x_values[i][0] < min)
      min = x_values[i][0];
  return min;
}

int get_max(unsigned char **x_values, int size)
{
  int max = 0;
  for (int i = 0; i < size; ++i)
    if (x_values[i][0] > max)
      max = x_values[i][0];
  return max;
}


double k_means(unsigned char **x_values, int size, int max_iterations, double min_distance)
{
  int *labels = malloc(size * sizeof(int));
  int **means = malloc(NB_CLUSTERS * sizeof(int*));
  for (int i = 0; i < NB_CLUSTERS; ++i)
    means[i] = malloc(NB_POINTS * sizeof(int));
  int **old_means = malloc(NB_CLUSTERS * sizeof(int*));
  for (int i = 0; i < NB_CLUSTERS; ++i)
    old_means[i] = malloc(NB_POINTS * sizeof(int));
  int *lengths = malloc(NB_CLUSTERS * sizeof(int));
  int nb_iterations = 0;
  int min = get_min(x_values, size);
  int max = get_max(x_values, size);
  for (int i = 0; i < NB_CLUSTERS; ++i)
    for (int j = 0; j < NB_POINTS; ++j)
      means[i][j] = min + max * i / NB_CLUSTERS;
  do
  {
    for(int i = 0; i < NB_CLUSTERS; ++i)
      for(int j = 0; j < NB_POINTS; ++j)
        old_means[i][j] = means[i][j];
    for(int i = 0; i < size; i++)
    {
      int label_mean = 0;
      int min_mean = NB_POINTS * 256 * 256;
      for (int j = 0; j < NB_CLUSTERS; ++j)
      {
        int mean = 0;
        for (int k = 0; k < NB_POINTS; ++k)
          mean += (x_values[i][k] - means[j][k])
            * (x_values[i][k] - means[j][k]);
        if (mean < min_mean)
        {
          min_mean = mean;
          label_mean = j;
        }
      }
      labels[i] = label_mean;
    }
    for (int i = 0; i < NB_CLUSTERS; ++i)
      lengths[i] = 0;
    for (int i = 0; i < NB_CLUSTERS; ++i)
      for (int j = 0; j < NB_POINTS; ++j)
        means[i][j] = 0;
    for (int i = 0; i < size; ++i)
    {
      lengths[labels[i]]++;
      for (int j = 0; j < NB_POINTS; ++j)
        means[labels[i]][j] += x_values[i][j];
    }
    for (int i = 0; i < NB_CLUSTERS; ++i)
      for (int j = 0; j < NB_POINTS; ++j)
        if (lengths[i])
          means[i][j] /= lengths[i];
    nb_iterations++;
  } while(nb_iterations < max_iterations
      && !minimized_distances(means, old_means, min_distance));
  return treat_image(x_values, size, lengths, labels, means);
}
