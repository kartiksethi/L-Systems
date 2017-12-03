#include <ctime>
#include <chrono>
#include<bits/stdc++.h>
#include "interpreter.h"

class LongTree {
public:
    LongTree(Color &colorBranch, Color &colorFlower, int x, int y, Canvas &canvas, int alignment, int generations = 6) {
        canvas.setOrigin(x, y);
        Interpreter pattern("^[X]", &canvas);
        pattern.addProduction('F', "FF");
        pattern.addMeaning('X', 0);
        pattern.addMeaning('F', 1, 5, &colorBranch);
        pattern.addMeaning('[', 2);
        pattern.addMeaning(']', 3);
        pattern.addMeaning('^', 4, 90);
        pattern.addMeaning('-', 4, 25);
        pattern.addMeaning('+', 4, -25);
        pattern.addMeaning('P', 5, 2, &colorFlower);
        pattern.addMeaning('G', 1, 5, &colorFlower);
        pattern.addProduction('L', "[(G(G(((G(G][)G)G)))G)G][((G(G(((G(G][))G)G)))G)G]");
        pattern.addMeaning('(', 4, 45);
        pattern.addMeaning(')', 4, -45);
        if (alignment == 1) // left alignment
            pattern.addProduction('X', "F-[XL]+F+[XL]-XL");
        else
            pattern.addProduction('X', "F+[XP]-F-[XP]+XP");

        for (int i = 0; i < generations; i++) {
            pattern.createNewGeneration();
            char buf[1000000];
            pattern.getCurrent(buf);
        }
        pattern.interpret();
        canvas.setOrigin(-x, -y);
    }
};

class Shrub {
public:
    Shrub(Color &colorBranch, Color &colorFlower, int x, int y, Canvas &canvas, int alignment, int generations = 4) {
        canvas.setOrigin(x, y);
        Interpreter pattern("^[X]", &canvas);
        pattern.addProduction('F', "FF");
        pattern.addMeaning('X', 0);
        pattern.addMeaning('F', 1, 5, &colorBranch);
        pattern.addMeaning('P', 5, 2, &colorFlower);
        pattern.addMeaning('[', 2);
        pattern.addMeaning(']', 3);
        pattern.addMeaning('^', 4, 90);
        pattern.addMeaning('-', 4, 25);
        pattern.addMeaning('+', 4, -25);
        if (alignment == 0) // left alignment
            pattern.addProduction('X', "[-X][+X][+X][-X]+FX");
        else if (alignment == 1)  // right alignment
            pattern.addProduction('X', "[+X][-X][-X][+X]-FX");
        else // symmetrical
            pattern.addProduction('X', "[-FX][+X][+X][-X]+FX");

        for (int i = 0; i < generations; i++) {
            pattern.createNewGeneration();
            char buf[1000000];
            pattern.getCurrent(buf);
        }
        pattern.interpret();
        canvas.setOrigin(-x, -y);
    }

};

class TreeD {
public:
    TreeD(Color &colorBranch, Color &colorFlower, int x, int y, Canvas &canvas, int generations = 5) {
        canvas.setOrigin(x, y);
        Interpreter pattern("^X", &canvas);
        pattern.addProduction('X', "F[+XL][-XL]FX");
        pattern.addProduction('F', "FF");
        pattern.addMeaning('X', 0);
        pattern.addMeaning('F', 1, 3, &colorBranch);
        pattern.addMeaning('P', 5, 2, &colorFlower);
        pattern.addMeaning('[', 2);
        pattern.addMeaning(']', 3);
        pattern.addMeaning('^', 4, 90);
        pattern.addMeaning('-', 4, 25.7);
        pattern.addMeaning('+', 4, -25.7);
        pattern.addMeaning('G', 1, 3, &colorFlower);
        pattern.addProduction('L', "[(G(G(((G(G][)G)G)))G)G][((G(G(((G(G][))G)G)))G)G]");
        pattern.addMeaning('(', 4, 45);
        pattern.addMeaning(')', 4, -45);

        for (int i = 0; i < generations; i++) {
            pattern.createNewGeneration();
            char buf[1000000];
            pattern.getCurrent(buf);
        }
        pattern.interpret();
        canvas.setOrigin(-x, -y);
    }

};

class Bird {
public:
    Bird(Color &bodycolor, Color &wingcolor, int x, int y, Canvas &canvas, int generations = 1) {
        canvas.setOrigin(x, y);
        Interpreter pattern("^X", &canvas);
        pattern.addProduction('F', "FF");
        pattern.addProduction('X', "[-F(G][+F)G]");
        pattern.addProduction('B', "[G]");
        pattern.addMeaning('X', 0);
        pattern.addMeaning('B', 0);
        pattern.addMeaning('F', 1, 10, &bodycolor);
        pattern.addMeaning('G', 1, 8, &wingcolor);
        pattern.addMeaning('[', 2);
        pattern.addMeaning(']', 3);
        pattern.addMeaning('^', 4, 90);
        pattern.addMeaning('-', 4, 50);
        pattern.addMeaning('+', 4, -50);
        pattern.addMeaning('(', 4, 25);
        pattern.addMeaning(')', 4, -25);
        for (int i = 0; i < generations; i++) {
            pattern.createNewGeneration();
            char buf[1000000];
            pattern.getCurrent(buf);
        }
        pattern.interpret();
        canvas.setOrigin(-x, -y);
    }
};

void night() {
    // Night by KAT
    Canvas canvas(1368, 700);
    Color brown(165, 42, 42);
    Color pink(255, 192, 170);
    Color green(98, 204, 28);
    Color yellow(255, 170, 34);
    Color white(255, 255, 255);
    Color black(0, 0, 0);


    for (int i = 1; i <= 200; i++)
        canvas.drawCircle(500, 450, i, white);

    for (int i = 0; i < 30; i++) {
        int x = rand() % 400 + 50;
        int y = rand() % 100 + 0;
        int randomnum = rand() % 2;
        int randomnum2 = rand() % 2;
        if (randomnum == 0)
            LongTree longTree1(brown, pink, x, y, canvas, randomnum, 6 - randomnum2);
        else
            LongTree longTree2(brown, green, x, y, canvas, randomnum, 6 - randomnum2);
    }

    for (int i = 0; i < 30; i++) {
        int x = rand() % 400 + 900;
        int y = rand() % 100 + 0;
        int randomnum = rand() % 2;
        int randomnum2 = rand() % 2;
        if (randomnum == 0)
            LongTree longTree(brown, pink, x, y, canvas, randomnum, 6 - randomnum2);
        else
            LongTree longTree3(brown, green, x, y, canvas, randomnum, 6 - randomnum2);
    }

    for (int i = 1; i <= 100; i++) {
        Color gradient(10, 10, 142 * i * 0.01);
        canvas.drawLine(0, i, 1368, i, gradient);
    }

    canvas.display();

}

void sunset() {
    //Sunset by KAT
    Canvas canvas(1368, 700);
    Color brown(165, 42, 42);
    Color pink(255, 192, 170);
    Color green(98, 204, 28);
    Color yellow(255, 170, 34);
    Color darkbrown(107, 47, 47);
    Color darkgreen(23, 73, 17);
    Color white(255, 255, 255);
    Color wintersnow(240, 247, 239);
    Color black(0, 0, 0);
    Color grey(130, 130, 130);
    Color suncolor(255, 255, 0);
    Color groundcolor(117, 100, 23);

    for (int i = 300; i <= 700; i++) {
        Color gradient(255, 97 - 0.1 * i, 0 + 0.1 * i);
        canvas.drawLine(0, i, 1368, i, gradient);
    }

    for (int i = 1; i <= 150; i++)
        canvas.drawCircle(500, 250, i, suncolor);

    for (int i = 300; i >= 0; i--) {
        canvas.drawLine(0, i, 1368, i, groundcolor);
    }

    for (int i = 0; i < 15; i++) {
        int y = rand() % 300 + 410;
        int x = rand() % 1250 + 50;
        Bird b(black, black, x, y, canvas);
    }


    for (int i = 0; i < 70; i++) {
        int x = rand() % 480 + 20;
        int y = rand() % 220 + 20;
        Shrub(yellow, green, x, y, canvas, 1, 4);
    }

    int x = 500;
    int y = 0;
    for (int i = 0; i < 13; i++, x += 40, y += 20) {
        TreeD t2(darkbrown, darkgreen, x, y, canvas);
    }

    int x1 = 500, y1 = 0;
    int x2 = 1020, y2 = 300;
    for (int i = 0; i < 520; i++, x1++, x2++) {
        canvas.drawLine(x1, y1, x2, y2, grey);
    }

    x = 1020;
    y = 0;
    for (int i = 0; i < 13; i++, x += 50, y += 20) {
        TreeD t2(darkbrown, darkgreen, x, y, canvas);
    }
    canvas.display();

}

void analysis() {
    Canvas canvas(1368, 700);
    Color brown(165, 42, 42);
    Color pink(255, 192, 170);
    Color green(98, 204, 28);
    Color yellow(255, 170, 34);
    Color white(255, 255, 255);
    Color black(0, 0, 0);
    Color blue(12, 43, 220);

    // generations vs time

    cout << "Generation vs Time for LongTree\n";
    for (int i = 0; i < 6; i++) {
        auto t1 = chrono::high_resolution_clock::now();
        LongTree tt(brown, green, 100, 50, canvas, 1, i + 1);
        auto t2 = chrono::high_resolution_clock::now();
        cout << "Time taken for generation " << i + 1 << " : "
             << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " milliseconds\n";
    }


    cout << "Generation vs Time for Shrub\n";
    for (int i = 0; i < 6; i++) {
        auto t1 = chrono::high_resolution_clock::now();
        Shrub tt(brown, green, 100, 50, canvas, 1, i + 1);
        auto t2 = chrono::high_resolution_clock::now();
        cout << "Time taken for generation " << i + 1 << " : "
             << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count() << " milliseconds\n";
    }

    // population vs time (generation - 6 for both of them)


    cout << "Population vs Time for LongTree\n";
    for (int i = 1; i <= 20; i++)
    {
        int j;
        auto t1 = chrono::high_resolution_clock::now();
        for (j = 0; j < 10 * i; j++) {
            LongTree t2(brown, green, 200, 50, canvas, 1, 4);
        }
        auto t2 = chrono::high_resolution_clock::now();
        cout << "Time taken for " << j << " trees : " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
             << " milliseconds\n";
    }

    cout << "Population vs Time for Shrub\n";
    for (int i = 1; i <= 20; i++) {
        int j;
        auto t1 = chrono::high_resolution_clock::now();
        for (j = 0; j < 10 * i; j++) {
            Shrub t2(brown, green, 200, 50, canvas, 1, 4);
        }
        auto t2 = chrono::high_resolution_clock::now();
        cout << "Time taken for " << j << " trees : " << chrono::duration_cast<chrono::milliseconds>(t2 - t1).count()
             << " milliseconds\n";
    }

}

void flowerTree(int treenum) {
    Canvas canvas(1368, 700);
    Color brown(165, 42, 42);
    Color pink(255, 192, 170);
    Color green(98, 204, 28);
    Color yellow(255, 170, 34);
    Color white(255, 255, 255);
    Color black(0, 0, 0);
    Color blue(12, 43, 220);
    canvas.setOrigin(500, -100);


    if (treenum == 0) {
        Interpreter pattern("^X", &canvas);
        pattern.addProduction('X', "F-[X/B]+F+[X/B]-X/B");
        pattern.addProduction('F', "FF");
        pattern.addProduction('B', "[(G))G))G))G]");
        pattern.addMeaning('X', 0);
        pattern.addMeaning('B', 0);
        pattern.addMeaning('F', 1, 6, &brown);
        pattern.addMeaning('G', 1, 6, &black);
        pattern.addMeaning('[', 2);
        pattern.addMeaning(']', 3);
        pattern.addMeaning('^', 4, 90);
        pattern.addMeaning('-', 4, 25);
        pattern.addMeaning('+', 4, -25);
        pattern.addMeaning('/', 5, 3, &yellow);
        pattern.addMeaning('(', 4, 45);
        pattern.addMeaning(')', 4, -45);
        for (int i = 0; i < 6; i++) {
            pattern.createNewGeneration();
            char buf[1000000];
            pattern.getCurrent(buf);
        }
        pattern.interpret();
    } else if (treenum == 1) {
        Interpreter pattern("^[X]", &canvas);
        pattern.addProduction('X', "F-[XB]+F+[XB]-XB");
        pattern.addProduction('F', "FF");
        pattern.addProduction('B', "[(G(G(((G(G][)G)G)))G)G][((G(G(((G(G][))G)G)))G)G]");
        pattern.addMeaning('X', 0);
        pattern.addMeaning('F', 1, 6, &brown);
        pattern.addMeaning('G', 1, 6, &pink);
        pattern.addMeaning('[', 2);
        pattern.addMeaning(']', 3);
        pattern.addMeaning('^', 4, 90);
        pattern.addMeaning('-', 4, 25);
        pattern.addMeaning('+', 4, -25);
        pattern.addMeaning('(', 4, 45);
        pattern.addMeaning(')', 4, -45);
        for (int i = 0; i < 6; i++) {
            pattern.createNewGeneration();
            char buf[1000000];
            pattern.getCurrent(buf);
        }
        pattern.interpret();
    } else {
        Interpreter pattern("^[X]", &canvas);
        pattern.addProduction('X', "F[+XL]-XL");
        pattern.addProduction('F', "FF");
        pattern.addProduction('L', "[(G++G++G][(--G--G--G][--G++G++G][++G--G--G]");
        pattern.addMeaning('X', 0);
        pattern.addMeaning('F', 1, 10, &brown);
        pattern.addMeaning('G', 1, 6, &blue);
        pattern.addMeaning('[', 2);
        pattern.addMeaning(']', 3);
        pattern.addMeaning('^', 4, 90);
        pattern.addMeaning('-', 4, 60);
        pattern.addMeaning('+', 4, -60);
        pattern.addMeaning('(', 4, 30);
        pattern.addMeaning(')', 4, -30);
        for (int i = 0; i < 6; i++) {
            pattern.createNewGeneration();
            char buf[1000000];
            pattern.getCurrent(buf);
        }
        pattern.interpret();
    }
    canvas.display();
}

using namespace std;

int main() {
    srand(15);
    night();
//    sunset();
//    flowerTree(1);
//    analysis();

    return 0;
}