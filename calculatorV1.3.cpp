#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>

const int MAXOP = 20;
const int MAXNODES = 1000;

int lastNode = -1;

/********************
ENUMS
********************/

enum Token {
    ADD, SUB, MUL, DIV, POW, SQRT, LN, EXP, SIN, COS, TAN, ASIN, ACOS, ATAN, LPARA, RPARA, EQUALS, NUM, VAR
};

std::string tokenStr[MAXOP] = {"+", "-", "*", "/", "^", "sqrt", "ln", "exp", "sin", "cos", "tan", "asin", "acos", "atan", "(", ")", "=", "NUM", "VAR"};

bool strIsOperator(std::string str) {
    for (int i = 0; i < MAXOP; i++) {
        if (str == tokenStr[i]) return true;
    }
    return false;
}

string numToStr(long double x) {
    float tmp = float(x);
    ostringstream ss;
    ss << tmp;
    return ss.str();
}

int getPrecedenceToken(Token token) {
    switch(token) {
        case EQUALS: return 0;
        case ADD: case SUB: return 1;
        case MUL: case DIV: return 2;
        case POW: return 3;
        case SIN: case COS: case TAN: case ASIN: case ACOS: case ATAN: case LN: case EXP: case SQRT: return 4;
        default: return 5;
    }
}


Token convertEnum(std::string s) {
    if (s == "+") return ADD;
    if (s == "-") return SUB;
    if (s == "*") return MUL;
    if (s == "/") return DIV;
    if (s == "^") return POW;
    if (s == "sqrt") return SQRT;
    if (s == "ln") return LN;
    if (s == "exp") return EXP;
    if (s == "sin") return SIN;
    if (s == "cos") return COS;
    if (s == "tan") return TAN;
    if (s == "asin") return ASIN;
    if (s == "acos") return ACOS;
    if (s == "atan") return ATAN;
    if (s == "(") return LPARA;
    if (s == ")") return RPARA;
    if (s == "=") return EQUALS;
    if ('0' <= s[0] && s[0] <= '9' || s[0] == '.') return NUM;
    return VAR;
}

std::string convertString(Token t) {
    if (t == ADD) return "ADD";
    if (t == SUB) return "SUB";
    if (t == MUL) return "MUL";
    if (t == DIV) return "DIV";
    if (t == POW) return "POW";
    if (t == SQRT) return "SQRT";
    if (t == LN) return "LN";
    if (t == EXP) return "EXP";
    if (t == SIN) return "SIN";
    if (t == COS) return "COS";
    if (t == TAN) return "TAN";
    if (t == ASIN) return "ASIN";
    if (t == ACOS) return "ACOS";
    if (t == ATAN) return "ATAN";
    if (t == LPARA) return "LPARA";
    if (t == RPARA) return "RPARA";
    if (t == NUM) return "NUM";
    if (t == EQUALS) return "EQUALS";
    return "VAR";
}

/********************
NODE
********************/

class Node {
    public:
        Node() {
            this -> token = NUM;
            this -> precedence = getPrecedenceToken(NUM);
            this -> value = 0;
            this -> leftChild = nullptr;
            this -> rightChild = nullptr;
        }

        Node(Token token, long double value) {
            this -> token = token;
            this -> precedence = getPrecedenceToken(token);
            this -> value = value;
            this -> leftChild = nullptr;
            this -> rightChild = nullptr;
        }

        Node(Token token, long double value, Node* leftChild, Node* rightChild) {
            this -> token = token;
            this -> precedence = getPrecedenceToken(token);
            this -> value = value;
            this -> leftChild = leftChild;
            this -> rightChild = rightChild;
        }

        Token getToken() {
            return this -> token;
        }

        int getPrecedence() {
            return this -> precedence;
        }

        bool isOperator() {
            switch (this -> token) {
                case NUM: case VAR: case LPARA: case RPARA:
                    return false;
                default:
                    return true;
            }
        }

        bool isUnary() {
            switch (this -> token) {
                case SIN: case COS: case TAN: case ASIN: case ACOS: case ATAN: case LN: case EXP: case SQRT:
                    return true;
                default:
                    return false;
            }
        }

        bool isBinary() {
            switch (this -> token) {
                case ADD: case SUB: case MUL: case DIV: case POW: case EQUALS:
                    return true;
                default:
                    return false;
            }
        }

        bool isLeftAssociative() {
            switch(this -> token) {
                case POW:
                    return false;
                default:
                    return true;
            }
        }
        
        long double getValue() {
            return this -> value;
        }

        std::string getName() {

        }

        Node* getLeftChild() {
            return this -> leftChild;
        }

        Node* getRightChild() {
            return this -> rightChild;
        }

        void setToken(Token token) {
            this -> token = token;
        }

        void setValue(long double value) {
            this -> value = value;
        }

        void setLeftChild(Node* leftChild) {
            this -> leftChild = leftChild;
        }

        void setRightChild(Node* rightChild) {
            this -> rightChild = rightChild;
        }

        void printNode() {
            std::cout << "Node " << this << std::endl;
            std::cout << "Token: " << tokenStr[this -> token] << std::endl;
            std::cout << "Value: " << this -> value << std::endl;
            std::cout << "name: " << this -> name << std::endl;
            std::cout << "leftChild: ";
            if (this -> leftChild != nullptr) std::cout << this -> leftChild << " " << this -> leftChild -> getToken() << " " << this -> leftChild -> getValue();
            std::cout << std::endl;
            std::cout << "rightChild: ";
            if (this -> rightChild != nullptr) std::cout << this -> rightChild << " " << this -> rightChild -> getToken() << " " << this -> rightChild -> getValue();
            std::cout << std::endl;
            std::cout << std::endl;
        }

    private:
        Token token;
        int precedence;
        long double value;
        std::string name; // this is for variables
        Node* leftChild;
        Node* rightChild;
};

/********************
NODE STUFF
********************/

//std::vector <Node> nodeList;
Node nodeList[MAXNODES];

void addNode(Node node) {
    nodeList[++lastNode] = node;
}

Node* copyExpression(Node* target) { //Copies the expression with the root target, returns the new copied expression's root
    addNode(Node(target -> getToken(), target -> getValue()));
    int index = lastNode;
    Node* res = &nodeList[index];
    if (target -> getLeftChild() != nullptr) nodeList[index].setLeftChild(copyExpression(target -> getLeftChild()));
    if (target -> getRightChild() != nullptr) nodeList[index].setRightChild(copyExpression(target -> getRightChild()));
    return res;
}

void printNodeVector(std::vector<Node> nodes) {
    for (Node cur : nodes) {
        cur.printNode();
    }
}

/********************
EXPRESSION TREE
********************/

class Expression {
    public:
        Expression(Node* root) {
            this -> root = root;
        }

        Expression(std::string str) {
            this -> root = buildTree(shuntingYard(parseString(str)));
            
        }

        Expression(std::vector <Node> nodes) {
            this -> root = buildTree(shuntingYard(nodes));
        }

        std::vector <Node> parseString(std::string str) {
            std::vector <Node> nodes;
            int prev = 0;
            for (int i = 0; i < str.size(); i++) {
                if (strIsOperator(str.substr(prev, i - prev + 1))) {
                    if ((convertEnum(str.substr(prev, i - prev + 1)) == SUB && nodes.size() == 0) || (convertEnum(str.substr(prev, i - prev + 1)) == SUB && nodes[nodes.size() - 1].getToken() != NUM && nodes[nodes.size() - 1].getToken() != RPARA)) nodes.push_back(Node(NUM, 0));
                    nodes.push_back(Node(convertEnum(str.substr(prev, i - prev + 1)), 0));
                    prev = i + 1;
                }
                else if ('0' <= str[i] && str[i] <= '9') {
                    long double res = 0;
                    int j = i;
                    bool pastDecimalPoint = false;
                    long double cnt = 1;
                    while ('0' <= str[j] && str[j] <= '9' || str[j] == '.') {
                        if (j == str.size()) break;
                        if (pastDecimalPoint) cnt *= 10;
                        if (str[j] == '.') pastDecimalPoint = true;
                        if ('0' <= str[j] && str[j] <= '9') res = res * 10 + (str[j] - '0');
                        j++;
                    }
                    res /= cnt;
                    i = j - 1;
                    nodes.push_back(Node(NUM, res));
                    prev = i + 1;
                } 
            }
            return nodes;
        }

        std::queue <Node> shuntingYard(std::vector <Node> nodes) {
            std::queue <Node> output;
            std::stack <Node> operators;
            for (int i = 0; i < nodes.size(); i++) {
                if (nodes[i].getToken() == NUM || nodes[i].getToken() == VAR) {
                    output.push(nodes[i]);
                }
                if (nodes[i].isOperator()) {
                    if (nodes[i].isUnary()) {
                        operators.push(nodes[i]);
                    }
                    if (nodes[i].isBinary()) {
                        while (!operators.empty() && (operators.top().isUnary() || operators.top().getPrecedence() > nodes[i].getPrecedence() || (operators.top().getPrecedence() == nodes[i].getPrecedence() && operators.top().isLeftAssociative())) && operators.top().getToken() != LPARA) {
                            output.push(operators.top());
                            operators.pop();
                        }
                        operators.push(nodes[i]);
                    }
                }
                if (nodes[i].getToken() == LPARA) {
                    operators.push(nodes[i]);
                }
                if (nodes[i].getToken() == RPARA) {
                    while (!operators.empty() && operators.top().getToken() != LPARA) {
                        output.push(operators.top());
                        operators.pop();
                    }
                    operators.pop(); 
                }
            }

            while (!operators.empty()) {
                output.push(operators.top());
                operators.pop();
            }
            return output;
        }

        Node* buildTree(std::queue <Node> rpn) {
            std::stack <Node*> stk;

            while (!rpn.empty()) {
                Node cur = rpn.front();
                rpn.pop();
                if (cur.getToken() == NUM || cur.getToken() == VAR) {
                    addNode(cur);
                    stk.push(&nodeList[lastNode]);
                }
                else {
                    addNode(cur);
                    if (cur.isUnary()) {
                        if (!stk.empty()) {
                            nodeList[lastNode].setLeftChild(stk.top());
                            stk.pop();
                        }
                    }
                    if (cur.isBinary()) {
                        if (!stk.empty()) {
                            nodeList[lastNode].setRightChild(stk.top());
                            stk.pop();
                        }
                        if (!stk.empty()) {
                            nodeList[lastNode].setLeftChild(stk.top());
                            stk.pop();
                        }
                    }
                    stk.push(&nodeList[lastNode]);
                }
            }

            return stk.top();
        }

        std::string getExpressionStringPointer(Node* node) {
            if (node -> getToken() == NUM) {
                return numToStr(node -> getValue());
            }
            if (node -> getToken() == VAR) {
                return node -> getName();
            }
            if (node -> isOperator()) {
                if (node -> isUnary()) {
                    return tokenStr[node -> getToken()] + "(" + getExpressionStringPointer(node -> getLeftChild()) + ")";
                }
                if (node -> isBinary()) {
                    
                }
            }
        }

        std::string getExpressionString() {
            
        }

        long double evaluateExpression() {

        }


        Node* const getRoot() const {
            return this -> root;
        }

        Expression operator +(const Expression& rhs) const {
            addNode(Node(ADD, 0, this -> root, rhs.getRoot()));
            int index = lastNode;
            return Expression(&nodeList[index]);
        }

        Expression operator -(const Expression& rhs) const {
            addNode(Node(SUB, 0, this -> root, rhs.getRoot()));
            int index = lastNode;
            return Expression(&nodeList[index]);
        }

        Expression operator *(const Expression& rhs) const {
            addNode(Node(MUL, 0, this -> root, rhs.getRoot()));
            int index = lastNode;
            return Expression(&nodeList[index]);
        }

        Expression operator /(const Expression& rhs) const {
            addNode(Node(DIV, 0, this -> root, rhs.getRoot()));
            int index = lastNode;
            return Expression(&nodeList[index]);
        }
        

        
         
    private:
        Node* root;

};

int main() {
    
    //addNode(Node(NUM, 1));
    //addNode(Node(NUM, 2));
    //Expression a(&nodeList[0]);
    //Expression b(&nodeList[1]);

    //Expression c = a + b; 
    //Expression d(copyExpression(c.getRoot()));
    Expression d("-1+3");
    //printNodeVector(d.TokenizeString("-1+(2*3.5)-(-3+sin(2.0))"));

    std::cout << std::endl;
    for (int i = 0; i <= lastNode; i++) {
        nodeList[i].printNode();
    }
    
    return 0;
}