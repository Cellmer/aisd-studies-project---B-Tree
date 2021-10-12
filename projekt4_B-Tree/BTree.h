#pragma once
#include "Node.h"

class BTree
{
public:
	BTree();
	BTree(int order);
	void insert(int key);
	Node* search(Node* node, int key) const;
	Node* getRoot() const { return root; }
	void setRoot(Node* node);
	int getTreeOrder() const { return treeOrder; }
	void print(Node* node) const;
	void load(); //tworzy drzewo o strukturze wyznaczonej przez format
	void save(Node* node) const; //zapisuje drzewo ukorzenione w node w danym formacie
	void remove(Node* node, int key); //usuñ key z poddrzewa ukorzenionego w node
	int getDepth() const{ return depth; }
	void resetDepth();


private:
	int treeOrder; //stopieñ drzewa
	Node* root; //korzeñ drzewa
	void splitChild(Node* parent, int sonNo); //podziel sonNo-tego syna wêz³a parent (bo jest on pe³ny)
	void insertNonFull(Node* node, int key); //wstawia klucz key do node lub wywo³uje siê rekurencyjnie dla jego potomków a¿ dotrze do liœci
	void addChild(Node* node, int i); // dodaj i-tego syna do wêz³a node
	int findPredecessor(Node* node); //znajdŸ w poddrzewie ukorzenionym w node poprzednika klucza key
	int findSuccessor(Node* node); //znajdŸ w poddrzewie ukorzenionym w node nastêpnika klucza key
	void merge(Node* node, int index); //scal synów node (poprzednik i nastêpnik key o indeksie index)
	mutable int depth; //g³êbokoœæ klucza w drzewie mo¿liwa do odczytania po ka¿dorazowym wywo³aniu search

};

