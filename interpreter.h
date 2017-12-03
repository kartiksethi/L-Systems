#include<bits/stdc++.h>
#include <cmath>
#include "canvas.h"
#include "cfg.h"

using namespace std;
#ifndef INTERPRETER_H
#define INTERPRETER_H
#define PI 3.14159265

class Interpreter {
private:
    CFG grammar;
    Canvas *canvas;
    map<char, vector<pair<int, pair<double, Color> > > > operations_map;
public:
    /**
     *
     * @param axiom Denotes the first generation
     * @param canvas Denotes a pointer of class Canvas
     */
    Interpreter(char axiom[], Canvas *canvas) : grammar(axiom) {
        this->canvas = canvas;
    }
    /**
     * Used to declare a character used in the grammar and define its meaning i.e. define the operation to be performed when the constant is encountered
     * @param character The character whose meaning is being defined
     * @param operation The operation to be performed when the character is encountered. Can take any value from 0 to 5. 0 stands for do nothing, 1 stands for draw forward, 2 stands for pushing current coordinates and inclination to stack, 3 stands for popping a set of coordinates and inclinations, 4 stands for turning left, 5 stands for turning right and 6 stands for drawing a circle.
     * @param attribute The value corresponding to a particular operation. Eg. Forward length of the pen, angle of rotation, etc.
     */
    void addMeaning(char character, int operation, double attribute = 0, Color *color = NULL);
    /**
     * Function to draw a line of fixed length starting at the given coordinates and inclined at the given inclination. Updates the current coordinates with the end points computed.
     * @param x Denotes the x coordinate of the starting point
     * @param y Denotes the y coordinate of the starting point
     * @param inclination Denotes the inclination of the line
     * @param length Denotes the length of the line segment to be drawn on the canvas
     * @param color Denotes the color of the line
     */
    void drawLine(int &x, int &y, double inclination, int length, Color color);
    /**
     * Interprets the current string of the series and produces an interpretation i.e. image of it.
     */
    void interpret();
    /**
     * Function to add a production to the grammar. Wrapper for the function provided by the CFG class
     * @param symbol Represents the LHS symbol of the production
     * @param rhs Represents the RHS of the production
     */
    inline void addProduction(char symbol, char rhs[]) {
        grammar.addProduction(symbol, rhs);
    }
    /**
     * Creates next generation string. Wrapper for the function provided by the CFG class.
     */
    inline void createNewGeneration() {
        grammar.createNewGeneration();
    }
    /**
     * Function to return the string of the most recent(current) generation
     * @param buf Denotes the buffer to be populated with the current generation string
     */
    inline void getCurrent(char buf[]) {
        grammar.getCurrent(buf);
    }
};

#endif //INTERPRETER_H