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
