//
// Created by Lev on 23.01.2021.
//
#include <string>
#include <fstream>
#include <set>

#ifndef ASD2_LABS_2020_CORRECTOR_H
#define ASD2_LABS_2020_CORRECTOR_H

using namespace std;

const string LOWER_ALPHABET = "abcdefghijklmnopqrstuvwxyz'";

template <typename T>
class Corrector {
private:
    T dictionary;
public:

    /**
     * Constructeur, prend un fichier txt contenant des mots,
     * les nettoie, et les ajoute à la structure dictionary
     */
    Corrector(const string& dicoFilename){
        ifstream ifs(dicoFilename);
        string word;
        while(getline(ifs, word))
            dictionary.insert(cleanString(word));
    }

    /**
     * Propose des correction pour les mots faux d'un fichier texte
     * @param filenameToCorrect: le nom du fichier à corriger
     * @param filenameOutput: le fichier contenant les correction en sortie
     */
    void correctFile(const string& filenameToCorrect, const string& filenameOutput){
        ifstream fileInput;
        fileInput.open(filenameToCorrect);
        ofstream outputStream;
        outputStream.open(filenameOutput);
        if(!fileInput.is_open() || !outputStream.is_open())
            throw new exception;
        string word = cleanString(word);
        while(fileInput) {
            fileInput >> word;
            word = cleanString(word);
            if(!word.empty() and !dictionary.contains(word)){
                outputStream << "*" << word << endl;
                extraLetterHypo(word, outputStream);
                missingLetterHypo(word, outputStream);
                wrongLetterHypo(word, outputStream);
                swapLetterHypo(word, outputStream);
            }
            word.clear();
        }
    }

private:

    /**
     * ajoute au stream la correction si celle-ci existe dans le dico
     * @param corrStr, le mot à véfifier puis ajouter
     * @param hypothesis, le numéro de l'hypothèse
     * @param ofs, le stream
     */
    void addCorrectionToString(const string& corrStr, size_t hypothesis, ofstream& ofs){
        if(dictionary.contains(corrStr))
            ofs << hypothesis << ": " << corrStr << endl;
    }
    /**
     * @param toClean
     * @return toClean en minuscule sans char spéciaux sauf l'apostrophe
     */
    string cleanString(string& toClean) {
        string cleanStr;
        for(char c : toClean) {
            if(isalpha(c)  or c == '\'')
                cleanStr.push_back((char)(tolower(c)));
        }
        return cleanStr;
    }

    /**
     * il y a un char en trop
     * @param toCorrect
     * @param output
     */
    void extraLetterHypo(const string& toCorrect, ofstream& output){
        int indexHypo = 1;
        for (size_t i = 0; i < toCorrect.size(); i++) {
            string outputword(toCorrect);
            outputword.erase(i, 1);
            addCorrectionToString(outputword, 1, output);
        }
    }
    /**
     * il manque un char
     * @param toCorrect
     * @param output
     */
    void missingLetterHypo(const string& toCorrect, ofstream& output){
        int indexHypo = 2;
        string outputword(toCorrect);
        for (int i = 0; i <= toCorrect.size(); i++)
            for(char c : LOWER_ALPHABET){
                outputword.insert(outputword.begin()+i, c);
                addCorrectionToString(outputword, 2, output);
                outputword.erase(outputword.begin()+i);
            }
    }

    /**
     * Gestion de l'hypothèse 3: une lettre a été mal tapé
     * @param toCorrect le mot d'entrée
     * @param output le(s) mot(s) de sortie
     */
    void wrongLetterHypo(const string& toCorrect, ofstream& output) {
        const int indexHypo = 3;
        string outputword(toCorrect);
        for (size_t i = 0; i < toCorrect.size(); ++i) {
            for (char c : LOWER_ALPHABET) {
                outputword[i] = c;
                addCorrectionToString(outputword, 3, output);
            }
        }
    }

    /**
     * Gestion de l'hypothèse 4: 2 lettre ont été interverti
     * @param toCorrect le mot d'entrée
     * @param output le(s) mot(s) de sortie
     */
    void swapLetterHypo(const string& toCorrect, ofstream& output){
        const int indexHypo = 4;
        string outputword(toCorrect);
        for(size_t i = 0; i < outputword.size()-1;++i){
            swap(outputword.at(i), outputword.at(i+1));
            addCorrectionToString(outputword, 4, output);
            swap(outputword.at(i+1), outputword.at(i));
        }
    }
};



#endif //ASD2_LABS_2020_CORRECTOR_H