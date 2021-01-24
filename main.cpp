//
// Created by Antoine Rochat on 23.05.20.
//

#include <iostream>
#include <fstream>
#include <chrono>
#include "HashMapWrapper.h"
#include "TernarySearchTree.h"

#include "Corrector.h"
#include "Chaining.cpp"
#include "utils.h"

template <typename dico>
void testCorrection(const string& filenameToCorrect, const string& filenameOutput,Corrector<dico> dictionary){
    chrono::time_point<chrono::system_clock> startCorr, endCorr;
    startCorr = chrono::system_clock::now();
    dictionary.correctFile(filenameToCorrect, filenameOutput);
    endCorr = chrono::system_clock::now();
    long long corrTime = chrono::duration_cast<chrono::milliseconds>(endCorr-startCorr).count();
    cout <<"Temps de correction : " << corrTime << " milliseconds" <<endl;
}

template <typename T>
Corrector<T>* loadCorrector(const string& filename){
    chrono::time_point<chrono::system_clock> startLoadDictionary, endLoadDictionary;
    startLoadDictionary = chrono::system_clock::now();
    Corrector<T> *corrector = new Corrector<T> (filename);
    //"data\\dictionary.txt"
    endLoadDictionary = chrono::system_clock::now();
    long long dicLoadTime = chrono::duration_cast<chrono::milliseconds>(endLoadDictionary-startLoadDictionary).count();
    cout <<"Dictionnary load time: " << dicLoadTime << " milliseconds" <<endl;
    return corrector;
}

using namespace std;



/**
 * Charge un dictionnaire contenu dans le fichier à filename dans un tst
 * @param filename, le chemin du fichier contenant les mots
 * @param dict, l'arbre à remplir
 */


int main() {
    //TST
    Corrector<TernarySearchTree> *c = loadCorrector<TernarySearchTree>("data\\dictionary_test.txt");
    testCorrection("data\\input_lates.txt", "data\\lates.txt", *c);


    Corrector<HashMapWrapper<string>> *c1 = loadCorrector<HashMapWrapper<string>>("data\\dictionary_test.txt");
    testCorrection("data\\input_lates.txt", "data\\lates2.txt", *c1);

     Corrector<Chaining<string>> *c2 = loadCorrector<Chaining<string>>("data\\dictionary_test.txt");
     testCorrection("data\\input_lates.txt", "data\\lates2.txt", *c2);
 }
