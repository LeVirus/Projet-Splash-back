#include <iostream>
#include "Algo.hpp"
#include "Grille.hpp"

using namespace std;

extern Grille *memGrille;

Algo::Algo(){

}

void Algo::jouer(){
	unsigned int x, y;
	do{
		if(!memGrille)return;
		cout<<"x?"<<endl;
		cin>>x;
		cout<<"y?"<<endl;
		cin>>y;
		memGrille->appliquerClick(x,y);
	}while(true);
}

void Algo::resolution(){

}

Algo::~Algo(){

}
