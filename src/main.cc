#include "camera.hpp"
#include "common.hpp"
#include "hittable_list.hpp"
#include "sphere.hpp"
#include "vec3.hpp"

int main() {
    hittable_list world;

    world.add(make_shared<Sphere>(point3(0, 0, -1), 0.5));
    world.add(make_shared<Sphere>(point3(0, -100.5, -1), 100));

    Camera cam;

    cam.aspect_ratio_ = 16.0 / 9.0;
    cam.samples_per_pixel_ = 100;
    cam.image_w_ = 640;
    cam.max_depth_ = 50;

    cam.Render(world);
}
