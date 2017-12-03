#include "canvas.h"
#include <GL/gl.h>
#include <GL/glut.h>
#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>
#define signum(x) ((x) >= 0 ? 1 : -1)
#define drawCirclePoint(x, y, c) {\
drawPoint((x), (y), (c));\
drawPoint((-x), (y), (c));\
drawPoint((-x), (-y), (c));\
drawPoint((x), (-y), (c));\
drawPoint((y), (x), (c));\
drawPoint((-y), (x), (c));\
drawPoint((-y), (-x), (c));\
drawPoint((y), (-x), (c));\
}

Canvas* current;

Canvas::Canvas(int width, int height)
{
    this->height = height;
    this->width = width;
    this->background = Color(0, 0, 0);
    this->origin = std::make_pair(0, 0);
}

void Canvas::drawLine(int x1, int y1, int x2, int y2, Color c)
{
    if(y2 == y1)
    {
        for(int i = std::min(x2, x1); i <= std::max(x2, x1); i++)
        {
            drawPoint(i, y1, c);
        }
    }
    else if(x2 == x1)
    {
        for(int i = std::min(y2, y1); i <= std::max(y2, y1); i++)
        {
            drawPoint(x1, i, c);
        }
    }
    else
    {
        int sign = (signum(y2 - y1) * signum(x2 - x1));
        int diag = abs(y2 - y1) == abs(x2 - x1);
        if(diag)
        {
            auto temp = x2 < x1 ? std::make_pair(x2, y2) : std::make_pair(x1, y1);
            while(temp.first <= std::max(x2, x1))
            {
                drawPoint(temp.first, temp.second, c);
                temp.first++;
                temp.second += sign;
            }
        }
        else
        {
            int vertical = abs(y2 - y1) > abs(x2 - x1);
            int A = y2 - y1;
            int B = x1 - x2;
            if(vertical)
            {
                int temp = A;
                A = B;
                B = temp;
            }
            if(B > 0)
            {
                A *= -1;
                B *= -1;
            }
            int d = 2 * A + sign * B;
            int del1 = 2 * A;
            int del2 = 2 * A + sign * 2 * B;
            int start;
            int end;
            int start_other;
            if(vertical)
            {
                if(y2 < y1)
                {
                    start = y2;
                    end = y1;
                    start_other = x2;
                }
                else
                {
                    start = y1;
                    end = y2; 
                    start_other = x1;
                }
            }
            else
            {
                if(x2 < x1)
                {
                    start = x2;
                    end = x1;
                    start_other = y2;
                }
                else
                {
                    start = x1;
                    end = x2;
                    start_other = y1;
                }
            }
            vertical ? drawPoint(start_other, start, c) : drawPoint(start, start_other, c);
            for(int i = start + 1; i <= end; i++)
            {
                if(sign * d > 0)
                {
                    start_other += sign;
                    d += del2;
                }
                else
                {
                    d += del1;
                }
                vertical ? drawPoint(start_other, i, c) : drawPoint(i, start_other, c);
            }           
        }
    }
}

void Canvas::drawCircle(int x, int y, int r, Color c)
{
    int d = 1 - r;
    int dE = 3;
    int dSE = -2 * r + 5;
    setOrigin(x, y);
    drawCirclePoint(0, r, c);
    int X = 0, Y = r;
    while(Y > X)
    {
        if(d < 0)
        {
            d += dE;
            dSE += 2;
        }
        else
        {
            d += dSE;
            dSE += 4;
            Y--;
        }
        dE += 2;
        X++;
        drawCirclePoint(X, Y, c);
    }
    setOrigin(-x, -y);
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);
    glBegin(GL_POINTS);
    for(auto i : current->points)
    {
	glColor3f(i.second.getR()/255.0f, i.second.getG()/255.0f, i.second.getB()/255.0f);
	glVertex2i(i.first / current->getHeight(), i.first % current->getHeight());
    }
    glEnd();
    glFlush();
}

void Canvas::display()
{
    int x = 0;
    current = this;
    glutInit(&x, NULL);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowPosition(0,0);
    glutInitWindowSize(width, height);
    glutCreateWindow("Canvas");
    glClearColor(background.getR()/255.0f, background.getG()/255.0f, background.getB()/255.0f,0);
    gluOrtho2D(0, width, 0, height);
    glutDisplayFunc(draw);
    glutMainLoop();    
}


