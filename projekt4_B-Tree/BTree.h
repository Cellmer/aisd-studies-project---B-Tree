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
	void remove(Node* node, int key); //usu� key z poddrzewa ukorzenionego w node
	int getDepth() const{ return depth; }
	void resetDepth();


private:
	int treeOrder; //stopie� drzewa
	Node* root; //korze� drzewa
	void splitChild(Node* parent, int sonNo); //podziel sonNo-tego syna w�z�a parent (bo jest on pe�ny)
	void insertNonFull(Node* node, int key); //wstawia klucz key do node lub wywo�uje si� rekurencyjnie dla jego potomk�w a� dotrze do li�ci
	void addChild(Node* node, int i); // dodaj i-tego syna do w�z�a node
	int findPredecessor(Node* node); //znajd� w poddrzewie ukorzenionym w node poprzednika klucza key
	int findSuccessor(Node* node); //znajd� w poddrzewie ukorzenionym w node nast�pnika klucza key
	void merge(Node* node, int index); //scal syn�w node (poprzednik i nast�pnik key o indeksie index)
	mutable int depth; //g��boko�� klucza w drzewie mo�liwa do odczytania po ka�dorazowym wywo�aniu search

};

