#include "color.h"
#include "common.h"
#include "hittable.h"

void write_color(std::ostream &out, const color &pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // We have to translate the [0, 1] component range to byte range [0, 255]
    // Note: using 255 would work just fine, but we'll follow the book's conventions
    int rbyte = int(255.999 * r);
    int gbyte = int(255.999 * g);
    int bbyte = int(255.999 * b);

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}

// Using linear interpolation (lerp) to blend colors
// blendedValue = (1-a) * startValue + (a * endValue);
color ray_color(const ray &r, const hittable &world) {
    const color pink = color(1, 0.847, 0.929);
    const color violet = color(0.733, 0.772, 0.976);

    hit_record rec;
    if (world.hit(r, 0, infinity, rec)) {
        return 0.5 * (rec.normal + color(1, 1, 1));
    }

    // Lerp blend rest of viewport
    vec3 unit_dir = unit(r.direction());
    auto a = 0.5 * (unit_dir.y() + 1.0);
    return (1.0 - a) * violet + a * pink;
}
