#include "color.h"
#include "ray.h"

#include <iostream>

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
color ray_color(const ray &r) {
    vec3 unit_direction = unit(r.direction());
    auto a = 0.5 * (unit_direction.y() + 1.0);

    // we're using white to blue
    return (1.0 - a) * color(1.0, 1.0, 1.0) + a * color(0.5, 0.7, 1.0);
}
