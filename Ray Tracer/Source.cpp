#define _CRT_SECURE_NO_WARNINGS
#include <stdexcept>
#include "camera.h"
#include "frame_buffer.h"
#include "hittable_objects.h"
#include "sphere.h"


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
    camera cam(float3(0.0f), fb.width(), fb.height());


    //Scene
    hittable_objects scene;
    scene.add_hittable_object(std::make_shared<sphere>(float3(0.0f, 0.0f, -1.0f), 0.5f));
    scene.add_hittable_object(std::make_shared<sphere>(float3(0.0f, -100.5f, -1.0f), 100.0f));
    
    const int samples_per_pixel = 100;
    float factor = 1.0f / samples_per_pixel;
    float3 color;

    //Renderer
    for (int row = 0; row < fb.height(); ++row) {
        for (int col = 0; col < fb.width(); ++col) {

            color = float3(0.0);
            for (int sample_no = 0; sample_no < samples_per_pixel; sample_no++) {

                float u = float(col + random_float()) / (fb.width() - 1);
                float v = float(row + random_float()) / (fb.height() - 1);

                ray r = cam.get_ray_to(u, v);

                color += get_color(r, scene);
            }

            fb.set_pixel(row, col, color, factor);
        }
    }
    fb.save("D:\\image.ppm");
}