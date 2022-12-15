/**
 * @file color.h
 * @brief Defines the Color class that represents a color in RGB space.
 */

#ifndef COLOR_H
#define COLOR_H

#include <ostream>

/**
 * @class Color
 * @brief Represents a color in RGB space.
 */
class Color {
  public:
    /**
     * @brief The red channel of the color.
     */
    float r;
    /**
     * @brief The green channel of the color.
     */
    float g;
    /**
     * @brief The blue channel of the color.
     */
    float b;
    /**
     * @brief Constructs a new Color object with the given values.
     * @param r_ The red channel of the color.
     * @param g_ The green channel of the color.
     * @param b_ The blue channel of the color.
     */
    Color(float r_ = 0., float g_ = 0.,float b_ = 0.);
    Color & operator+=(Color c);
    Color & operator*=(float f);
};

/**
 * @brief Converts a float to an integer.
 * @param f The floating point value to convert.
 * @return 255*f rounded to the nearest integer.
 */
int floatToInt(float f);

Color operator+ (const Color &c1, const Color &c2);
Color operator* (const float f, const Color &c);

std::ostream & operator<< (std::ostream &st, const Color &c);

#endif