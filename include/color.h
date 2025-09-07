#ifndef COLOR_H
#define COLOR_H

using color = vec3;

void write_color(std::ostream &out, const color &pixel_color);
color ray_color(const ray &r);

#endif
