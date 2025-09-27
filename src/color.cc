#include "color.hpp"

double color::LinearToGamma(double linear_component) {
    if (linear_component > 0) {
        return std::sqrt(linear_component);
    }
    return 0.0;
}

void color::WriteColor(std::ostream &out, const Color &pixel_color) {
    auto r = pixel_color.x();
    auto g = pixel_color.y();
    auto b = pixel_color.z();

    // Linear gamma transform for gamma 2
    r = color::LinearToGamma(r);
    g = color::LinearToGamma(g);
    b = color::LinearToGamma(b);

    // We have to translate the [0, 1] component range to byte range [0, 255]
    static const Interval intensity(0.000, 0.999);
    int rbyte = int(256 * intensity.Clamp(r));
    int gbyte = int(256 * intensity.Clamp(g));
    int bbyte = int(256 * intensity.Clamp(b));

    out << rbyte << ' ' << gbyte << ' ' << bbyte << '\n';
}
