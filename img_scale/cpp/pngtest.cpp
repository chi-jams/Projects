
#include <png.h>
#include <stdio.h>
#include <iostream>

struct png_data {
    int width,
        height;
    png_byte color_type,
             bit_depth;
    png_bytep *row_ptrs;
};

png_data read_image(char* file_name) {

    // TODO: Make less terrible
    // Begin section ripped from https://gist.github.com/niw/5963798
    FILE *fp = fopen(file_name, "rb");

    // TODO: Make less terrible
    png_structp png = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png) abort();

    // TODO: Make less terrible
    png_infop info = png_create_info_struct(png);
    if(!info) abort();

    // TODO: Make less terrible
    if(setjmp(png_jmpbuf(png))) abort();

    // End section ripped from from https://gist.github.com/niw/59637988
    png_init_io(png, fp);

    png_read_info(png, info);
   
    png_data img; 
    img.width = png_get_image_width(png, info),
    img.height = png_get_image_height(png, info);
    img.color_type = png_get_color_type(png, info),
    img.bit_depth = png_get_bit_depth(png, info);
    
    // TODO: Make more C++ like
    img.row_ptrs = (png_bytep*)malloc(sizeof(png_bytep) * img.height);
    for (int y = 0; y < img.height; y++) {
        img.row_ptrs[y] = (png_byte*)malloc(png_get_rowbytes(png, info));
    }

    png_read_image(png, img.row_ptrs);
 
    fclose(fp);
    
    return img;
}

void write_image(char* file_name, png_data img) {
   
    FILE *fp = fopen(file_name, "wb");
    if(!fp) abort();

    // TODO: Make less terrible
    png_structp png = png_create_write_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if(!png) abort();

    // TODO: Make less terrible
    png_infop info = png_create_info_struct(png);
    if(!info) abort();

    png_init_io(png, fp);

    png_set_IHDR(png, info, img.width, img.height, img.bit_depth,
                 img.color_type, PNG_INTERLACE_NONE,
                 PNG_COMPRESSION_TYPE_DEFAULT, PNG_FILTER_TYPE_DEFAULT);

    png_write_info(png, info);
    
    png_write_image(png, img.row_ptrs);
    png_write_end(png, NULL);

    for (int y = 0; y < img.height; y++) {
        free(img.row_ptrs[y]);
    }
    free(img.row_ptrs);

    fclose(fp);
}

int main(int argc, char *argv[]) {
    
    if (argc != 3) {
        std::cerr << "Usage: ./img_scale <path_to_in> <path_to_out>"
                  << std::endl;
        exit(EXIT_FAILURE);
    }
    
    png_data img = read_image(argv[1]);
    write_image(argv[2], img);
    std::cout << "This image is " << img.width << " by " << img.height 
              << std::endl;
    return 0;
}
