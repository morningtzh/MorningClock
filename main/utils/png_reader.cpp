//
// Created by MorningTZH on 2024/4/17.
//

#include "png_reader.hpp"
#include <esp_log.h>
#include <png.h>
#include <cstring>

static const char *MODULE = "PNG";

int PngReadAll(const char *path)
{
    FILE *fp_read = fopen(path, "rb");

    png_structp png_read = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    png_infop infop_read = png_create_info_struct(png_read);
    png_init_io(png_read, fp_read);

    png_read_png(png_read, infop_read, PNG_TRANSFORM_EXPAND, 0);

    // PNG_COLOR_TYPE_RGB_ALPHA
    int color_type = png_get_color_type(png_read, infop_read);
    ESP_LOGI(MODULE, "color_type:%d\n", color_type);

    uint32_t w = png_get_image_width(png_read, infop_read);
    uint32_t h = png_get_image_height(png_read, infop_read);
    ESP_LOGI(MODULE, "w:%lu, h:%lu\n", w, h);

    png_bytep buff = (png_bytep)malloc(h * w * 3 * sizeof(png_byte));
    memset(buff, 0, (h * w * 3 * sizeof(png_byte)));

    png_bytep *row_pointers = png_get_rows(png_read, infop_read);

    switch (color_type)
    {
        case PNG_COLOR_TYPE_RGB_ALPHA:
        {
            int i, j;
            for (i = 0; i < h; i ++)
            {
                for (j = 0; j < w; j ++)
                {
                    buff[i * w + 3 * j + 0] = row_pointers[i][3 * j + 0];
                    buff[i * w + 3 * j + 1] = row_pointers[i][3 * j + 1];
                    buff[i * w + 3 * j + 2] = row_pointers[i][3 * j + 2];
                }
            }
            break;
        }
        default:
            break;
    }

    return 0;
}

int PngReadPart(const char *path, Point &p, Size &s, RGB8 **buffer)
{
    FILE *fp_read = fopen(path, "rb");
    if (fp_read == nullptr) {
        ESP_LOGE(MODULE, "Open file failed: %s", path);
        return -1;
    }

    png_structp png_read = png_create_read_struct(PNG_LIBPNG_VER_STRING, NULL, NULL, NULL);
    if (png_read == nullptr) {
        ESP_LOGE(MODULE, "png_create_read_struct failed: %s", path);
        return -1;
    }
    png_infop infop_read = png_create_info_struct(png_read);
    if (infop_read == nullptr) {
        ESP_LOGE(MODULE, "png_create_info_struct failed: %s", path);
        return -1;
    }
    png_init_io(png_read, fp_read);

    png_read_png(png_read, infop_read, PNG_TRANSFORM_EXPAND, 0);

    // PNG_COLOR_TYPE_RGB_ALPHA
    int color_type = png_get_color_type(png_read, infop_read);
    ESP_LOGI(MODULE, "color_type:%d\n", color_type);

    uint32_t w = png_get_image_width(png_read, infop_read);
    uint32_t h = png_get_image_height(png_read, infop_read);
    ESP_LOGI(MODULE, "w:%lu, h:%lu\n", w, h);

    png_bytep *row_pointers = png_get_rows(png_read, infop_read);

    switch (color_type)
    {
        case PNG_COLOR_TYPE_RGB_ALPHA:
        {
            for (int j = 0; j < s.h; j++)
            {
                for (int i = 0; i < s.w; i++)
                {
                    if (row_pointers[i + p.y][4 * (j + p.x) + 3] == 3) {
                        buffer[(s.h-1)-j][i].mask = true;
                    }
                    buffer[(s.h-1)-j][i].mask = false;
                    buffer[(s.h-1)-j][i].r = row_pointers[i + p.y][4 * (j + p.x) + 0];
                    buffer[(s.h-1)-j][i].g = row_pointers[i + p.y][4 * (j + p.x) + 1];
                    buffer[(s.h-1)-j][i].b = row_pointers[i + p.y][4 * (j + p.x) + 2];
                }
            }
            break;
        }
        case PNG_COLOR_TYPE_RGB:
        {
            for (int j = 0; j < s.h; j++)
            {
                for (int i = 0; i < s.w; i++)
                {
                    buffer[(s.h-1)-j][i].r = row_pointers[i + p.y][3 * (j + p.x) + 0];
                    buffer[(s.h-1)-j][i].g = row_pointers[i + p.y][3 * (j + p.x) + 1];
                    buffer[(s.h-1)-j][i].b = row_pointers[i + p.y][3 * (j + p.x) + 2];
                }
            }
            break;
        }
        default:
            break;
    }

    png_destroy_read_struct(&png_read, &infop_read, 0);

    fclose(fp_read);

    return 0;
}