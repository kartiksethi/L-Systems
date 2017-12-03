#include<bits/stdc++.h>
using namespace std;
#ifndef CFG_H
#define CFG_H

/**
 * Class representing the Context Free Grammar being used to generate the image.
 */
class CFG
{
    private:
        map<char,char[1000000]> productions;
        char current[1000000];
    public:
        /**
         * Constructor which initializes the string with the axiom
         * @param axiom The string representing the first generation of the series
         */
        CFG(char axiom[])
        {
            strcpy(current,axiom);
        }
        /**
         * Function to add a production to the grammar
         * @param symbol Represents the LHS symbol of the production
         * @param rhs Represents the RHS of the production
         */
        void addProduction(char symbol,char rhs[]);
        /**
         * Generates the offspring of the current string by simultaneously replacing all the symbols by the RHS's of their respective rules.
         */
        void createNewGeneration();
        /**
         * Returns the current generation string
         */
        void getCurrent(char buffer[]);
};
#endif //CFG_H