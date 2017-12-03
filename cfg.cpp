#include "cfg.h"
using namespace std;

void CFG::addProduction(char symbol,char rhs[])
{
    strcpy(productions[symbol],rhs);
}

void CFG::createNewGeneration()
{
    char new_string[1000000];
    int pos = 0;
    for (long i = 0;current[i]!='\0'; ++i)
    {
        if(productions.find(current[i])!=productions.end())
        {
            for(long j=0;j<strlen(productions[current[i]]);++j)
            {
                new_string[pos++] = productions[current[i]][j];
            }
        }
        else
            new_string[pos++] = current[i];
    }
    new_string[pos] = '\0';
    strcpy(current,new_string);
}

void CFG::getCurrent(char buffer[])
{
    strcpy(buffer,current);
}