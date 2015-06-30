#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>

/* 
 * data from: http://yann.lecun.com/exdb/mnist/
 */
#define PHOTO_TRAIN "train-images.idx3-ubyte"
#define LABEL_TRAIN "train-labels.idx1-ubyte"

#define PHOTO_TEST "t10k-images.idx3-ubyte"
#define LABEL_TEST "t10k-labels.idx1-ubyte"

uint8_t *image_data;
uint8_t *image_labels; 

void swap_endianess(uint32_t *n) {
  uint8_t d = (*n >> 24) & 0xff;
  uint8_t c = (*n >> 16) & 0xff;
  uint8_t b = (*n >> 8) & 0xff;
  uint8_t a = (*n >> 0) & 0xff;
  *n = (a << 24) | (b << 16) | (c << 8) | d;
}

void read_images(uint8_t **image_data, uint32_t *image_count, const char *fname) {
  uint32_t magic_num, num_images, image_width, image_height;
  FILE *file = fopen(fname, "rb");

  if (file == NULL) {
    printf("file not found.\n");
    exit(-1);
  }

  fread(&magic_num, sizeof(uint32_t), 1, file);
  swap_endianess(&magic_num);

  fread(&num_images, sizeof(uint32_t), 1, file);
  swap_endianess(&num_images);

  fread(&image_height, sizeof(uint32_t), 1, file);
  swap_endianess(&image_height);

  fread(&image_width, sizeof(uint32_t), 1, file);
  swap_endianess(&image_width);

  printf("magic: %d\n", magic_num);
  printf("images: %d\n", num_images);
  printf("image_height: %d\n", image_height);
  printf("image_width: %d\n", image_width);

  uint32_t num_pixels = num_images * image_width * image_height;
  *image_data = (uint8_t*)malloc(sizeof(uint8_t) * num_pixels);
  fread(*image_data, sizeof(uint8_t), num_pixels, file);

  if (image_count) {
    *image_count = num_images;
  }
}

void read_labels(uint8_t **image_labels, uint32_t *label_count, const char *fname) {
  uint32_t magic_num, num_labels;
  FILE *file = fopen(fname, "rb");

  if (file == NULL) {
    printf("file not found.\n");
    exit(-1);
  }

  fread(&magic_num, sizeof(uint32_t), 1, file);
  swap_endianess(&magic_num);

  fread(&num_labels, sizeof(uint32_t), 1, file);
  swap_endianess(&num_labels);

  printf("magic: %d\n", magic_num);
  printf("labels: %d\n", num_labels);

  *image_labels = (uint8_t*)malloc(sizeof(uint8_t) * num_labels);
  fread(*image_labels, sizeof(uint8_t), num_labels, file);

  if (label_count) {
    *label_count = num_labels;
  }
}


int main() {
  uint32_t num_images, num_labels;
  read_images(&image_data, &num_images, PHOTO_TRAIN);
  read_labels(&image_labels, NULL, LABEL_TRAIN);

  printf("%d\n", num_images);
}
