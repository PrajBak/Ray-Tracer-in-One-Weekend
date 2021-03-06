#pragma once
#include<cstdio>
#include<cstdlib>
#include<cstdint>
#include "s1mo_maths.h"

//framebuffer is used to create a datastructur  ...
//to hold the image data and store it in a file ...
//specified by a path provided bu the user as a ...
//PPM file in P3 format.
//Created by s1mo

class frame_buffer {
    public:
        frame_buffer()
            :   width_(0),
                height_(0),
                channels_(0),
                data_(NULL) {}

        frame_buffer(int width, int height)
            :   width_(width),
                height_(height),
                channels_(3),
                data_((float*)malloc(double(channels_) * double(width_) * double(height_) * double(sizeof(float)))) {}
    
        ~frame_buffer() {
            free(data_);
        }
    
        void set_pixel(
            const int row,
            const int col,
            const float3& color,
            const float factor) {
    
            float3 temp_color = clamp(color * factor, 0.0f, 255.0f);
            set_pixel(row, col, temp_color.x(), temp_color.y(), temp_color.z());
            
        }
    
        //save(...) -> saves the data_ to a file    ...
        //with (0, 0) as the image's top left corner.
        void save(const char* image_path) {

            FILE* fp = fopen(image_path, "w");
            if (fp == NULL) {
                printf("Error in creating a file.");
                return;
            }

            fprintf(fp, "P3\n%d %d\n255\n", width_, height_);
            auto data_size = channels_ * width_ * height_;

            for (auto i = 0; i < data_size; ++i) {
                fprintf(fp, "%f\n", data_[i]);
            }
            fclose(fp);
        }
    
        const int width() const {
            return width_;
        }
    
        const int height() const {
            return height_;
        }

    private:
        void set_pixel(
            const int row,
            const int col,
            const float r,
            const float g,
            const float b) {

            //To accomodate (0, 0) being the bottom ...
            //left corner rather than top right.
            const int adjusted_row = height_ - 1 - row;

            const int idx = channels_ * (adjusted_row * width_ + col);
            data_[idx + 0] = r;
            data_[idx + 1] = g;
            data_[idx + 2] = b;
        }
    
    private:
        const int width_;
        const int height_;
        const int channels_;
        float* data_;
    
};