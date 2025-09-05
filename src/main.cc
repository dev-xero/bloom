#include <iostream>

int main() {
    int image_width = 256;
    int image_height = 256;

    // Render a simple PPM image
    std::cout << "P3\n" << image_width << ' ' << image_height << "\n255\n";

    for (int j = 0; j < image_height; j++) {
        std::clog << "\rScanlines remaining: " << (image_height - j) << ' ' << std::flush;

        for (int i = 0; i < image_width; i++) {
            // red goes from fully off to on from left to right
            // green goes from fully off to on from top to bottom
            auto r = double(i) / (image_width - 1);
            auto g = double(j) / (image_width - 1);
            auto b = 0.0;

            int ir = int(255.999 * r);
            int ig = int(255.999 * g);
            int ib = int(255.999 * b);

            std::cout << ir << ' ' << ig << ' ' << ib << '\n';
        }
    }

    std::clog << "\rDone.                 \n";
}
