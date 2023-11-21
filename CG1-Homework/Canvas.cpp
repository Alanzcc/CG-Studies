#include "Canvas.hpp"

Canvas::Canvas(int windowWidth, int windowHeight, int windowDistance,
    int numLines, int numColumns)
{
    this->windowWidth = windowWidth;
    this->windowHeight = windowHeight;
    this->windowDistance = windowDistance;
    this->numLines = numLines;
    this->numColumns = numColumns;
    this->deltaX = windowWidth / numColumns;
    this->deltaY = windowHeight / numLines;
    this->windowMinX = -windowWidth / 2;
    this->windowMaxY = windowHeight / 2;
}

std::vector<std::vector<std::vector<double>>> Canvas::Raycast(Object* object, std::vector<double> lightSource, std::vector<double> intensity)
{
    double pixelColumn, pixelLine;
    std::vector<double> illuminated;
    std::vector<std::vector<std::vector<double>>> painting(numLines, std::vector<std::vector<double>>(numColumns, std::vector<double>(3, -2)));

    for (int l = 0; l < numLines; l++)
    {
        pixelLine = windowMaxY - (deltaY / 2) - (l * deltaY);
        for (int c = 0; c < numColumns; c++)
        {
            pixelColumn = windowMinX + (deltaX / 2) + (c * deltaX);
            std::vector<double> windowPoint;
            windowPoint.push_back(pixelColumn);
            windowPoint.push_back(pixelLine);
            windowPoint.push_back((double)-windowDistance);
            Ray Ray(lightSource, windowPoint);
            illuminated = object->Illumination(Ray, intensity);
            if (illuminated[0] != -2)
            {
                painting[l][c] = illuminated;
              
                //SDL usa valores de 0 a 255 para cores
            }
        }
    }
    return painting;
}

