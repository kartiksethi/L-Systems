#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#include <unordered_map>
#ifndef CANVAS_H
#define CANVAS_H
/**
 * Class representing a 24 bit color
 */
class Color
{
public:
    /**
     * Constructor for a Color object
     * @param R the red value of the color (0-255)
     * @param G the green value of the color (0-255)
     * @param B the blue value of the color (0-255)
     */
    Color(int r, int g, int b):R(r), G(g), B(b) {}
    Color(){R = G = B = 0;}
    inline int getR(){ return R; }
    inline int getG(){ return G; }
    inline int getB(){ return B; }
private:
    int R;
    int G;
    int B;
};

/**
 * Class representing a canvas to draw on.
 */
class Canvas
{
public:
    /**
     * Constructs a canvas to draw on.
     * @param width The width in pixels.
     * @param height The height in pixels.
     */
    Canvas(int width, int height);
    /**
     * Sets the origin of the canvas. All further drawings will be
     * with respect to this origin.
     * @param x The x coordinate of the new origin wrt the current
     * @param y The y coordinate of the new origin wrt the current
     */
    inline void setOrigin(int x, int y)
    {
        origin.first += x;
        origin.second += y;
    }
    /**
     * Sets the background color of the image.
     * @param bg The background color.
     */
    inline void setBackgroundColor(Color bg)
    {
        background = bg;
    }
    /**
     * Returns the width of the canvas
     * @return the width
     */
    inline int getWidth()
    {
        return width;
    }
    /**
     * Returns the height of the canvas
     * @return the height
     */
    inline int getHeight()
    {
        return height;
    }
    /**
     * Draws a line between the given points.
     * @param x1 The x coordinate of the first point
     * @param y1 The y coordinate of the first point
     * @param x2 The x coordinate of the second point
     * @param y2 The y coordinate of the second point
     * @param c The color of the line
     */
    void drawLine(int x1, int y1, int x2, int y2, Color c);
    /**
     * Draws a circle on the image.
     * @param x The x coordinate of the center of the circle
     * @param y The y coordinate of the center of the circle
     * @param r The radius of the circle
     * @param c The color of the circle
     */
    void drawCircle(int x, int y, int r, Color c);
    /**
     * Draws one point to the screen
     * @param x The x coordinate of the point
     * @param y The y coordinate of the point
     * @param c The color of the point
     */
    inline void drawPoint(int x, int y, Color c)
    {
        if(x + origin.first >= 0 && x + origin.first < width && y + origin.second >= 0 && y + origin.second < height)
            points[(x + origin.first) * height + y + origin.second] = c;
    }
    /**
     * Displays the generated image. Display after everything is done.
     */
    void display();
    std::unordered_map< int, Color > points;
private:    
    std::pair< int, int > origin;
    Color background;
    int height;
    int width;
};
#endif
