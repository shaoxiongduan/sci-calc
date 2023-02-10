#ifndef NODE_H
#define NODE_H

#include "Util.h"

class Node {
    public:
        Node();

        Node(Token token, long double value);

        Node(Token token, std::string name);

        Node(Token token, long double value, Node* leftChild, Node* rightChild);

        Token getToken();

        int getPrecedence();
        
        long double getValue();

        std::string getName();

        Node* getLeftChild();

        Node* getRightChild();

        void setToken(Token token);

        void setValue(long double value);

        void setLeftChild(Node* leftChild);

        void setRightChild(Node* rightChild);

        void setChild(Node* target, Node* child);

        bool isOperator();

        bool isUnary();

        bool isBinary();

        bool isLeftAssociative();

        void printNode();

    private:
        Token token;
        int precedence;
        long double value;
        std::string name; // this is for variables
        Node* leftChild;
        Node* rightChild;
};

extern Node nodeList[MAXNODES];

Node* addNode(Node node);

Node* copyExpression(Node* target); //Copies the expression with the root target, returns the new copied expression's root

Node* printExpressionDebug(Node* target);

void printNodeVector(std::vector <Node> nodes);

#endif