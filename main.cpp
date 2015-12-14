#include <iostream>
#include "include/BiblAudio.h"

using namespace std;

int main()
{
    BiblAudio b;
    b.bAjoutMorceau("sdfsd", "sdfsdfs", "qqsdsqqqqsdfsdgggg",0,5);
    b.bAjoutMorceau("ssazeaze", "sdfsdfs", "qqsdsqqqqsdfsdgggg",98,56);
    b.bAjoutMorceau("ssazeaze", "ddfdg", "6516651g",0,5);
    b.bAjoutMorceau("opômo", "sdfsdfs", "qqsdsqqqqsdfsdgggg",0,5);
    b.bSuprMorceau("opômo");
    b.afficherMorceaux();
    return 0;
}

