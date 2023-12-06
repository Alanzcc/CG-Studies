#include "../Reality/include/Canvas.hpp"
#include "../Reality/include/Space.hpp"
#include "../Algebra/include/Vec3.hpp"
#include "../Algebra/include/Point.hpp"
#include "../Algebra/include/Ray.hpp"
#include "../Lights/include/Intensity.hpp"
#include "../Lights/include/Directional_Light.hpp"
#include "../Lights/include/Point_Light.hpp"
#include "../Lights/include/Spotlight.hpp"
#include "../Objects/include/Sphere.hpp"

#include <iostream>
#include <vector>

int main()
{
    // Create a canvas
    Canvas canvas(1000, 1000);

    // Create a space
    Space space();

    // Create a sphere
    Sphere sphere(Point(0, 0, 0), 1);

    // Create a light
    Point_Light light(Point(0, 0, 0), Intensity(1, 1, 1));

    // Add the sphere and the light to the space
    space.add_object(&sphere);
    space.add_light(&light);

    // Create a camera
    Point camera(0, 0, -5);

    // Create a ray
    Ray ray(camera, Vec3(0, 0, 1));

    // Calculate the color of the sphere at the intersection point
    std::optional<IntCol> color = space.intercept(ray);

    // Draw the color of the sphere at the intersection point on the canvas
    canvas.draw(color.value());

    // Save the canvas as a PPM file
    //canvas.save("Kirby.ppm");

    return 0;
}
