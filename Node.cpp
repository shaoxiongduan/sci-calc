#include "Util.h"
#include "Node.h"


Node::Node() {
    this -> token = NUM;
    this -> precedence = getPrecedenceToken(NUM);
    this -> value = 0;
    this -> leftChild = nullptr;
    this -> rightChild = nullptr;
}

Node::Node(Token token, long double value) {
    this -> token = token;
    this -> precedence = getPrecedenceToken(token);
    this -> value = value;
    this -> leftChild = nullptr;
    this -> rightChild = nullptr;
}

Node::Node(Token token, std::string name) {
    this -> token = token;
    this -> precedence = getPrecedenceToken(token);
    this -> name = name;
    this -> value = 0;
    this -> leftChild = nullptr;
    this -> rightChild = nullptr;
}

Node::Node(Token token, long double value, Node* leftChild, Node* rightChild) {
    this -> token = token;
    this -> precedence = getPrecedenceToken(token);
    this -> value = value;
    this -> leftChild = leftChild;
    this -> rightChild = rightChild;
}

Token Node::getToken() {
    return this -> token;
}

int Node::getPrecedence() {
    return this -> precedence;
}

long double Node::getValue() {
    return this -> value;
}

std::string Node::getName() {
    return this -> name;
}

Node* Node::getLeftChild() {
    return this -> leftChild;
}

Node* Node::getRightChild() {
    return this -> rightChild;
}

void Node::setToken(Token token) {
    this -> token = token;
}

void Node::setValue(long double value) {
    this -> value = value;
}

void Node::setLeftChild(Node* leftChild) {
    this -> leftChild = leftChild;
}

void Node::setRightChild(Node* rightChild) {
    this -> rightChild = rightChild;
}

void Node::setChild(Node* target, Node* child) {
    if (this -> leftChild == target) setLeftChild(child);
    if (this -> rightChild == target) setRightChild(child);
}

bool Node::isOperator() {
    switch (this -> token) {
        case NUM: case VAR: case LPARA: case RPARA:
            return false;
        default:
            return true;
    }
}

bool Node::isUnary() {
    switch (this -> token) {
        case SIN: case COS: case TAN: case SEC: case CSC: case COT: case ASIN: case ACOS: case ATAN: case LN: case EXP: case SQRT: case NEGATIVE:
            return true;
        default:
            return false;
    }
}

bool Node::isBinary() {
    switch (this -> token) {
        case ADD: case SUB: case MUL: case DIV: case POW: case EQUALS:
            return true;
        default:
            return false;
    }
}

bool Node::isLeftAssociative() {
    switch(this -> token) {
        case POW:
            return false;
        default:
            return true;
    }
}


void Node::printNode() {
    /*
    std::cout << "Node " << this << std::endl;
    std::cout << "Token: " << convertToString(this -> token) << std::endl;
    std::cout << "Precedence: " << this -> precedence << std::endl;
    std::cout << "Value: " << this -> value << std::endl;
    std::cout << "name: " << this -> name << std::endl;
    std::cout << "leftChild: ";
    if (this -> leftChild != nullptr) std::cout << this -> leftChild << " " << this -> leftChild -> getToken() << " " << this -> leftChild -> getValue();
    std::cout << std::endl;
    std::cout << "rightChild: ";
    if (this -> rightChild != nullptr) std::cout << this -> rightChild << " " << this -> rightChild -> getToken() << " " << this -> rightChild -> getValue();
    std::cout << std::endl;
    std::cout << std::endl;
    */
}


Node nodeList[MAXNODES];

Node* addNode(Node node) {
    nodeList[++lastNode] = node;
    return &nodeList[lastNode];
}

Node* copyExpression(Node* target) { //Copies the expression with the root target, returns the new copied expression's root
    addNode(Node(target -> getToken(), target -> getValue()));
    int index = lastNode;
    Node* res = &nodeList[index];
    if (target -> getLeftChild() != nullptr) nodeList[index].setLeftChild(copyExpression(target -> getLeftChild()));
    if (target -> getRightChild() != nullptr) nodeList[index].setRightChild(copyExpression(target -> getRightChild()));
    return res;
}

Node* printExpressionDebug(Node* target) {
    int index = lastNode;
    Node* res = &nodeList[index];
    target -> printNode();
    if (target -> getLeftChild() != nullptr) printExpressionDebug(target -> getLeftChild());
    if (target -> getRightChild() != nullptr) printExpressionDebug(target -> getRightChild());
    return res;
}

void printNodeVector(std::vector<Node> nodes) {
    for (Node cur : nodes) {
        cur.printNode();
    }
}