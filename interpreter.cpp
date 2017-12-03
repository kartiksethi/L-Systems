#include "interpreter.h"
using namespace std;

void Interpreter::addMeaning(char character, int operation, double attribute, Color *color) {
    pair<int, pair<double, Color> > temp;
    temp.first = operation;
    temp.second.first = attribute;
    if (color != NULL)
        temp.second.second = *color;
    operations_map[character].push_back(temp);
}

void Interpreter::drawLine(int &x, int &y, double inclination, int length, Color color) {
    /*
     * Computing the ending coordinates of the line segment
     */
    double rad = inclination * PI / 180.0;
    int end_x = x + round((double) length * cos(rad));
    int end_y = y + round((double) length * sin(rad));
    (*canvas).drawLine(x, y, end_x, end_y, color);
    /*
     * Updating the current coordinates with the end points computed
     */
    x = end_x;
    y = end_y;
}

void Interpreter::interpret() {
    char current[1000000];
    grammar.getCurrent(current);
    long length = strlen(current);
    int current_x = 0;
    int current_y = 0;
    double inclination = 0;
    stack<pair<int, int> > stack_coordinates;
    stack<double> stack_inclinations;
    for (int i = 0; i < length; ++i) {
        for (int j = 0; j < operations_map[current[i]].size(); ++j) {
            /*
             * Do nothing
             */
            if (operations_map[current[i]][j].first == 0)
                continue;
                /*
                 * Draw a forward line at the current coordinates
                 */
            else if (operations_map[current[i]][j].first == 1)
                drawLine(current_x, current_y, inclination, round(operations_map[current[i]][j].second.first),
                         operations_map[current[i]][j].second.second);
                /*
                 * Push current coordinates and inclination to stack
                 */
            else if (operations_map[current[i]][j].first == 2) {
                stack_coordinates.push(pair<int, int>(current_x, current_y));
                stack_inclinations.push(inclination);
            }
                /*
                 * Restore coordinates and inclination by popping from stack
                 */
            else if (operations_map[current[i]][j].first == 3) {
                current_x = stack_coordinates.top().first;
                current_y = stack_coordinates.top().second;
                inclination = stack_inclinations.top();
                stack_coordinates.pop();
                stack_inclinations.pop();
            }
                /*
                 * Rotate left (or right) by specified number of degrees
                 */
            else if (operations_map[current[i]][j].first == 4)
                inclination = inclination + operations_map[current[i]][j].second.first;
                /*
                 * Draw a circle at the current coordinates
                 */
            else if (operations_map[current[i]][j].first == 5)
                (*canvas).drawCircle(current_x, current_y, round(operations_map[current[i]][j].second.first),
                                     operations_map[current[i]][j].second.second);
                /**
                 *  Pen Up and take the cursor to a specified coordinate
                 */
            else
                cout << "Error 97: Unspecified constant found " << current[i] << " "
                     << operations_map[current[i]][j].first << endl;
        }
    }
}