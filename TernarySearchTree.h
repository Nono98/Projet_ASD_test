//
// Created by Lev on 18.01.2021.
//

#ifndef ASD2_LABS_2020_TERNARYSEARCHTREE_H
#define ASD2_LABS_2020_TERNARYSEARCHTREE_H
#include <algorithm>
#include <string>
#include <utility>

using namespace std;

class TernarySearchTree {

private:
    struct Node {
    public:
        bool wordEnd;
        char c;
        Node* left;
        Node* mid;
        Node* right;
        int nodeHeight;
        Node(char key) : c(key), left(nullptr), mid(nullptr), right(nullptr),
                         nodeHeight(0), wordEnd(false){}
    };

    //Racine de l'arbre
    Node* root;

    // HELPER: Methode aide pour le methodes d'effacement. Efface del et retourne ret.
    Node* deleteAndReturn( Node* del, Node* ret) {
        delete del;
        return ret;
    }

    // HELPER: Mise à jour de la hauteur d'un sous-arbre à partir des hauteurs de ses enfants
    void updateNodeHeight(Node* x) {
        x->nodeHeight = std::max(height(x->right), height(x->left)) + 1;
    }

    //
    // Source: AVL: rotation droite avec mise à jour des tailles et hauteurs
    //
    Node* rotateRight(Node* x) {
        Node* y = x->left;
        x->left = y->right;
        y->right = x;

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }

    //
    // Source: AVL: rotation gauche avec mise à jour des tailles et hauteurs
    //
    Node* rotateLeft(Node* x) {
        Node* y = x->right;
        x->right = y->left;
        y->left = x;

        updateNodeHeight(x);
        updateNodeHeight(y);
        return y;
    }

public:
    //Constructeur avec racine vide
    TernarySearchTree(): root(nullptr){};

    //Destructeur
    ~TernarySearchTree(){
        deleteSubTree(root);
        delete root;
    }

public:

    /**
     * Supprime le sous arbre avec la clé en paramètre
     * @param key
     */
    void erase(const string& key) {
        deleteSubTree(get(root, key, 0));
    }

private:

    /**
     * Supprime le sous arbre qui part du noeud x
     * @param x, le noeud racine
     */
    void deleteSubTree(Node* x){
        if(x == nullptr) return;
        deleteSubTree(x->left);
        deleteSubTree(x->mid);
        deleteSubTree(x->right);
        delete x;
    }

public:


    /**
     * @return la hauteur de l'arbre
     */
    int height() {
        return height(root);
    }

private:




    /**
     * @param x, le noeud racine
     * @return, renvoie la hauteure du sous arbre partant de x
     */
    int height(Node* x) {
        return (x == nullptr)? -1 : x->nodeHeight;
    }

public:

    /**
     * Insère dans l'arbre la valeur de clé
     * @param key, une string
     */
    void insert (const string& key){
        root = insert(root, key, 0);
    }

    /**
     * Insère dans le sous arbre partant de x, la valeur de la clé en paramètre
     * @param x, le noeud racine
     * @param key, la clé (string)
     * @param d
     * @return le Noeud inséré
     */
    Node* insert(Node* x, const string& key, int d){
        char c = key.at(d);
        if(x == nullptr)
            x = new Node(c);
        if(c < x->c)
            x->left = insert(x->left, key, d);
        else if(c > x->c)
            x->right = insert(x->right, key,d);
        else if (d < key.length()-1)
            x->mid = insert(x->mid, key, d+1);
        else if(d == key.length()-1)
            x->wordEnd = true;
        return restoreBalance(x);
    }

public:

    /**
     *
     * @param key
     * @return La valeur du noeud ayant la clé en paramètre
     */
    /*
   int get(const string& key){
       Node* x = get(root, key, 0);
       if(x == nullptr) return 0;
       return x->value;
   }*/

private:

    /**
     *
     * @param x, racine du sous arbre
     * @param key, la clé
     * @param d
     * @return, le noeud du sous arbre ayant la clé en paramètre
     */
    Node* get(Node* x, const string& key, int d){
        //TODO verif que key n'est pas vide
        if(x == nullptr) return nullptr;
        char c = key.at(d);
        if(c < x->c)
            return get(x->left, key, d);
        else if(c > x->c)
            return get(x->right, key, d);
        else if( d < key.length()-1)
            return get(x->mid, key, d+1);
        else
            return x;
    }

public:
    /**
     * Indique si l'arbre contient la clé
     * @param key
     * @return true si l'arbre contient la clé
     */
    bool contains(const string& key) {
        return contains(root, key, 0);
    }
private:
    bool contains(Node* x, const string& key, int d){
        if(x == nullptr)
            return 0;
        char c = key.at(d);
        if(c < x->c)
            return contains(x->left, key, d);
        else if(c > x->c)
            return contains(x->right, key, d);
        else if(d < key.length() - 1)
            return contains(x->mid, key, d+1);
        else
            return x->wordEnd;
    }

public:
    int balance(){
        return this->balance(root);
    }

private:
    /**
     * Indique si l'arbre est équilibré
     * @param x, le noeud racine
     * @return 0, si l'arbre est équilibré, le delta (arbre gauche, arbre droite) sinon
     */
    int balance(Node* x){
        if(x == nullptr) return 0;
        return height(x->left) - height(x->right);
    }
    /**
     * Rééquilibre le sous arbre partant de x
     * @param x, le noeud racine
     * @return le nouveau noeud racine
     */
    Node* restoreBalance(Node* x){
        if(balance(x) < -1) // left < right-1
        {
            if (balance(x->right)>0)
                x->right = rotateRight( x->right );
            x = rotateLeft(x);
        }
        else if( balance(x) > 1) // left > right+1
        {
            if ( balance(x->left) < 0 )
                x->left = rotateLeft( x->left );
            x = rotateRight(x);
        }
        else updateNodeHeight(x);
        return x;
    }

};

#endif //ASD2_LABS_2020_TERNARYSEARCHTREE_H