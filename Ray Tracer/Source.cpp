#define _CRT_SECURE_NO_WARNINGS
#include "light.h"
#include "camera.h"
#include "frame_buffer.h"
#include "hittable_objects.h"
#include "sphere.h"


float3 get_color(ray r, hittable_object& scene, light li) {

    float3 color;

    hit_info hi;

    if (scene.isHit(r, 0.001f, 1000.0f, hi)) {

        //Computing if a point is in shadow.
        hit_info shadow_hi;
        const float3 point = hi.poc_;
        const float3 point_to_light = li.position() - point;
        const ray shadow_ray(point, point_to_light);
        if (scene.isHit(shadow_ray, 0.001f, 1000.0f, shadow_hi)) {
            color = float3(0.01f);
        }
        else
            color = li.compute_color(hi);
    }
    else {
        color = float3(0.5f, 0.5f, 0.5f);
    }

    return clamp(color * 255.0f, 0.0f, 255.0f);
}


int main() {

    //Image
    frame_buffer fb(400, 225);

    //Camera
    camera cam(float3(0.0f), fb.width(), fb.height());


    //Scene
    hittable_objects scene;

    scene.add_hittable_object(std::make_shared<sphere>(
        float3(0.0f, 0.0f, -1.0f), 0.5f,
        float3(0.5f, 0.0f, 0.0f), float3(0.5f, 0.0f, 0.0f), float3(0.5f, 0.0f, 0.0f)) );

    scene.add_hittable_object(std::make_shared<sphere>(
        float3(0.0f, -100.5f, -1.0f), 100.0f,
        float3(0.0f, 0.5f, 0.0f) , float3(0.0f, 0.5, 0.0f), float3(0.0f, 0.5, 0.0f)) );

    light light1(1.0f, 0.5f, float3(0.0f, 0.0f, 0.0f));


    //Renderer
    const int samples_per_pixel = 10;
    float factor = 1.0f / samples_per_pixel;
    float3 color;

    for (int row = 0; row < fb.height(); ++row) {
        for (int col = 0; col < fb.width(); ++col) {

            color = float3(0.0f);
            for (int sample_no = 0; sample_no < samples_per_pixel; sample_no++) {

                float u = float(col + random_float()) / (fb.width() - 1);
                float v = float(row + random_float()) / (fb.height() - 1);

                ray r = cam.get_ray_to(u, v);

                color += get_color(r, scene, light1);
            }

            fb.set_pixel(row, col, color, factor);
        }
    }
    fb.save("D:\\image.ppm");
}