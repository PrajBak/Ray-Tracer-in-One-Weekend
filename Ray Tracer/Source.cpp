#define _CRT_SECURE_NO_WARNINGS
#include "frame_buffer.h"
#include "hittable_objects.h"
#include "sphere.h"

//Storing image data into a ppm image
//in top left to bottom right order

float3 get_color(ray r, hittable_object& scene) {

    float3 color;

    hit_info hi;

    if (scene.isHit(r, 0.01f, 100.0f, hi)) {
        float3 norm = hi.normal_;
        color = 0.5f * float3(norm.x() + 1.0f, norm.y() + 1.0f, norm.z() + 1.0f);
    }
    else {
        float3 unit_direction = r.ray_direction().normalize();
        const float t = 0.5f * (unit_direction.y() + 1.0f);
        color = (1.0f - t) * float3(1.0f, 1.0f, 1.0f) + t * float3(0.5f, 0.7f, 1.0f);
    }

    return color * 255.0f;
}


//int main() {
//    float3 point1(3.0, 4.0, 5.0);
//    float3 point2(2.0);
//    std::cout << -(point2 - point1);
//}


int main() {

    //Image
    frame_buffer fb(400, 225);

    //Camera
    float asp = fb.asp();
    float view_height = 2.0;
    float view_width = view_height * asp;
    float3 ray_origin(0.0);
    float focal_length = 1.0;
    const float3 lower_left(-view_width/2.0, -view_height/2.0, -focal_length);


    //Scene
    hittable_objects scene;
    scene.add_hittable_object(std::make_shared<sphere>(float3(0.0f, 0.0f, -1.0f), 0.5f));
    scene.add_hittable_object(std::make_shared<sphere>(float3(0.0f, -100.5f, -1.0f), 100.0f));
    

    //Renderer
    for (int row = 0; row < fb.height(); ++row) {
        for (int col = 0; col < fb.width(); ++col) {

            float u = float(col) / (fb.width() - 1);
            float v = float(row) / (fb.height() - 1);

            ray r(ray_origin, lower_left + u * float3(view_width, 0.0, 0.0) 
                  + v * float3(0.0, view_height, 0.0) - ray_origin);

            float3 color = get_color(r, scene);
            fb.set_pixel(row, col, color);
        }
    }

    fb.save("D:\\image.ppm");
}