#include <iostream>
#include <cstdio>
#include <algorithm>
#include <cstring>
#include <vector>
#include <stack>
#include <queue>
#include <cmath>

const int MAXOP = 25;
const long double EPSILON = 1e-8;
const int MAXNODES = 1000;

int lastNode = -1;

/********************
ENUMS
********************/

enum Token {
    ADD, SUB, MUL, DIV, POW, SQRT, LN, EXP, SIN, COS, TAN, SEC, CSC, COT, ASIN, ACOS, ATAN, LPARA, RPARA, EQUALS, NEGATIVE, NUM, VAR
};

std::string tokenStr[MAXOP] = {"+", "-", "*", "/", "^", "sqrt", "ln", "exp", "sin", "cos", "tan", "sec", "csc", "cot", "asin", "acos", "atan", "(", ")", "=", "-", "NUM", "VAR"};

bool strIsOperator(std::string str) {
    for (int i = 0; i < MAXOP; i++) {
        if (str == tokenStr[i]) return true;
    }
    return false;
}

bool cmpLongDouble(long double a, long double b) {
    if (fabsl(a - b) <= EPSILON) return true;
    return false;
}

std::string numToStr(long double x) {
    
}

int getPrecedenceToken(Token token) {
    switch(token) {
        case EQUALS: return 0;
        case ADD: case SUB: return 1;
        case MUL: case DIV: return 2;
        case POW: return 3;
        case SIN: case COS: case TAN: case SEC: case CSC: case COT: case ASIN: case ACOS: case ATAN: case LN: case EXP: case SQRT: case NEGATIVE: return 4;
        default: return 5;
    }
}


Token convertToEnum(std::string s) {
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
    if (s == "sec") return SEC;
    if (s == "csc") return CSC;
    if (s == "cot") return COT;
    if (s == "asin") return ASIN;
    if (s == "acos") return ACOS;
    if (s == "atan") return ATAN;
    if (s == "(") return LPARA;
    if (s == ")") return RPARA;
    if (s == "=") return EQUALS;
    if ('0' <= s[0] && s[0] <= '9' || s[0] == '.') return NUM;
    return VAR;
}

std::string convertToString(Token t) {
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
    if (t == SEC) return "SEC";
    if (t == CSC) return "CSC";
    if (t == COT) return "COT";
    if (t == ASIN) return "ASIN";
    if (t == ACOS) return "ACOS";
    if (t == ATAN) return "ATAN";
    if (t == LPARA) return "LPARA";
    if (t == RPARA) return "RPARA";
    if (t == NUM) return "NUM";
    if (t == EQUALS) return "EQUALS";
    if (t == NEGATIVE) return "NEGATIVE";
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

        Node(Token token, std::string name) {
            this -> token = token;
            this -> precedence = getPrecedenceToken(token);
            this -> name = name;
            this -> value = 0;
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
        
        long double getValue() {
            return this -> value;
        }

        std::string getName() {
            return this -> name;
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

        void setChild(Node* target, Node* child) {
            if (this -> leftChild == target) setLeftChild(child);
            if (this -> rightChild == target) setRightChild(child);
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
                case SIN: case COS: case TAN: case SEC: case CSC: case COT: case ASIN: case ACOS: case ATAN: case LN: case EXP: case SQRT: case NEGATIVE:
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

        void printNode() {
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

        Expression operator ^(const Expression& rhs) const {
            addNode(Node(POW, 0, this -> root, rhs.getRoot()));
            int index = lastNode;
            return Expression(&nodeList[index]);
        }



        std::vector <Node> parseString(std::string str) {
            std::vector <Node> nodes;
            int prev = 0;
            for (int i = 0; i < str.size(); i++) {
                if (strIsOperator(str.substr(prev, i - prev + 1))) {
                    if ((convertToEnum(str.substr(prev, i - prev + 1)) == SUB && nodes.size() == 0) || (convertToEnum(str.substr(prev, i - prev + 1)) == SUB && nodes[nodes.size() - 1].getToken() != NUM && nodes[nodes.size() - 1].getToken() != VAR && nodes[nodes.size() - 1].getToken() != RPARA)) {
                        nodes.push_back(Node(NEGATIVE, 0));
                    }
                    else {
                        nodes.push_back(Node(convertToEnum(str.substr(prev, i - prev + 1)), 0));
                    }
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
                else if (str.substr(prev, i - prev + 1) == "x") {
                    nodes.push_back(Node(VAR, "x"));
                    prev = i + 1;
                }
            }
            //printNodeVector(nodes);
            //std::cout << std::endl;
            return nodes;
        }

        std::queue <Node> shuntingYard(std::vector <Node> nodes) {
            std::queue <Node> output;
            std::stack <Node> operators;
            for (int i = 0; i < nodes.size(); i++) {
                if (nodes[i].getToken() == NUM || nodes[i].getToken() == VAR) {
                    //std::cout << "NUM or VAR: " << i << std::endl;
                    output.push(nodes[i]);
                }
                if (nodes[i].isOperator()) {
                    //std::cout << "OPERATOR: " << i << std::endl;
                    if (nodes[i].isUnary()) {
                        //std::cout << "UNARY PUSH: " << i << std::endl;
                        operators.push(nodes[i]);
                    }
                    if (nodes[i].isBinary()) {
                        //std::cout << "BINARY PUSH" << std::endl;
                        while (!operators.empty() && (operators.top().isUnary() || operators.top().getPrecedence() > nodes[i].getPrecedence() || (operators.top().getPrecedence() == nodes[i].getPrecedence() && nodes[i].isLeftAssociative())) && operators.top().getToken() != LPARA) {
                            //std::cout << "FFR" << std::endl;
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
            std::cout << "SHUNTINGYARD: \n";
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
                //cur.printNode();
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
            std::cout << "BUILDTREE: \n";
            //printExpressionDebug(stk.top());
            return stk.top();
        }

        std::string getExpressionStringPointer(Node* node) {
            std::string res = "";
            if (node -> getToken() == NUM) {
                return std::to_string(node -> getValue());
            }
            if (node -> getToken() == VAR) {
                return node -> getName();
            }
            if (node -> isOperator()) {
                if (node -> isUnary()) {
                    res = tokenStr[node -> getToken()] + "(" + getExpressionStringPointer(node -> getLeftChild()) + ")";
                    return res;
                }
                if (node -> isBinary()) {
                    if (node -> getLeftChild() -> getPrecedence() < node -> getPrecedence()) {
                        res += "(" + getExpressionStringPointer(node -> getLeftChild()) + ")";
                    }
                    else {
                        res += getExpressionStringPointer(node -> getLeftChild());
                    }

                    res += tokenStr[node -> getToken()];

                    if (node -> getRightChild() -> getPrecedence() < node -> getPrecedence()) {
                        res += "(" + getExpressionStringPointer(node -> getRightChild()) + ")";
                    }
                    else {
                        res += getExpressionStringPointer(node -> getRightChild());
                    }
                    return res;
                }
            }
        }

        std::string getExpressionString() {
            return getExpressionStringPointer(this -> root);
        }

        bool simplifyPointer(Node* node) { //WARNING!!! THIS FUNCTION WOULD MODIFY NODES THAT MIGHT BE LINKED TO PREVIOUS EXPRESSIONS!! IT IS ALWAYS RECOMMENDED TO DO COPYEXPRESSION FIRST, THEN SIMPLIFY ON THAT. true: has variable, false: no variables must do non variable first
            bool lson = false, rson = false;
            if (node -> getLeftChild() != nullptr) lson = simplifyPointer(node -> getLeftChild());
            if (node -> getRightChild() != nullptr) rson = simplifyPointer(node -> getRightChild());

            if (node -> getToken() == NUM) {
                return false;
            }
            else if (node -> getToken() == VAR) {
                return true;
            }
            else { // an operator
                
                if ((node -> isUnary() && lson == false) || (node -> isBinary() && lson == false && rson == false)) { // all numbers
                    std::cout << "ALL NUMS" << std::endl;
                    node -> printNode();
                    long double res = 0;
                    switch (node -> getToken()) {
                        case NEGATIVE: res = -(node -> getLeftChild() -> getValue()); break;
                        case ADD: res = (node -> getLeftChild() -> getValue()) + (node -> getRightChild() -> getValue()); break;
                        case SUB: res = (node -> getLeftChild() -> getValue()) - (node -> getRightChild() -> getValue()); break;
                        case MUL: res = (node -> getLeftChild() -> getValue()) * (node -> getRightChild() -> getValue()); break;
                        case DIV: res = (node -> getLeftChild() -> getValue()) / (node -> getRightChild() -> getValue()); break;
                        case POW: res = pow(node -> getLeftChild() -> getValue(), (node -> getRightChild() -> getValue())); break;
                        case SQRT: res = sqrtl(node -> getLeftChild() -> getValue()); break;
                        case LN: res = logl(node -> getLeftChild() -> getValue()); break;
                        case EXP: res = expl(node -> getLeftChild() -> getValue()); break;
                        case SIN: res = sinl(node -> getLeftChild() -> getValue()); break;
                        case COS: res = cosl(node -> getLeftChild() -> getValue()); break;
                        case TAN: res = tanl(node -> getLeftChild() -> getValue()); break;
                        case SEC: res = 1.0 / cosl(node -> getLeftChild() -> getValue()); break;
                        case CSC: res = 1.0 / sinl(node -> getLeftChild() -> getValue()); break;
                        case COT: res = 1.0 / tanl(node -> getLeftChild() -> getValue()); break;
                        case ASIN: res = asinl(node -> getLeftChild() -> getValue()); break;
                        case ACOS: res = acosl(node -> getLeftChild() -> getValue()); break;
                        case ATAN: res = atanl(node -> getLeftChild() -> getValue()); break;
                        default: res = 0;
                    }
                    *node = Node(NUM, res);
                    return false;
                }
                else if (node -> isUnary()) { // unary operator
                    //node -> setLeftChild(addNode(Node(NUM, res)));
                    return true;
                }
                else { // binary operator
                    //std::cout << "binary with x" << convertToString(node -> getToken()) << " " << lson.first << " " << lson.second << " " << rson.first << " " << rson.second << std::endl;
                    if (node -> getToken() == ADD) {
                        if (lson == false && cmpLongDouble(node -> getLeftChild() -> getValue(), 0)) {
                            //std::cout << "binary with x" << convertToString(node -> getToken()) << " " << lson.first << " " << lson.second << " " << rson.first << " " << rson.second << std::endl;
                            //std::cout << 1 << std::endl;
                            *node = *(node -> getRightChild());
                            return true;
                        }
                        else if (rson == false && cmpLongDouble(node -> getRightChild() -> getValue(), 0)) {
                            //std::cout << 2 << std::endl;
                            *node = *(node -> getLeftChild());
                            return true;
                        }
                    }
                    if (node -> getToken() == SUB) {
                        if (rson == false && cmpLongDouble(node -> getRightChild() -> getValue(), 0)) {
                            //std::cout << 3 << std::endl;
                            *node = *(node -> getLeftChild());
                            return true;
                        }
                    }
                    if (node -> getToken() == MUL) {
                        if (lson == false && cmpLongDouble(node -> getLeftChild() -> getValue(), 0)) {
                            //std::cout << "binary with x" << convertToString(node -> getToken()) << " " << lson.first << " " << lson.second << " " << rson.first << " " << rson.second << std::endl;
                    
                            //std::cout << 4 << std::endl;
                            *node = *(node -> getLeftChild());
                            return false;
                        }
                        else if (rson == false && cmpLongDouble(node -> getRightChild() -> getValue(), 0)) {
                            //std::cout << 5 << std::endl;
                            *node = *(node -> getRightChild());
                            return false;
                        }
                        else if (lson == false && cmpLongDouble(node -> getLeftChild() -> getValue(), 1)) {
                            //std::cout << 6 << std::endl;
                            *node = *(node -> getRightChild());
                            return true;
                        }
                        else if (rson == false && cmpLongDouble(node -> getRightChild() -> getValue(), 1)) {
                            //std::cout << 7 << std::endl;
                            *node = *(node -> getLeftChild());
                            return true;
                        }
                    }
                    if (node -> getToken() == DIV) {
                        if (lson == false && cmpLongDouble(node -> getLeftChild() -> getValue(), 0)) {
                            //std::cout << 4 << std::endl;
                            *node = *(node -> getLeftChild());
                            return false;
                        }
                    }
                    if (node -> getToken() == POW) {
                        if (rson == false && cmpLongDouble(node -> getRightChild() -> getValue(), 0)) {
                            //std::cout << 5 << std::endl;
                            *node = *(node -> getRightChild());
                            node -> setValue(1);
                            return false;
                        }
                        else if (rson == false && cmpLongDouble(node -> getRightChild() -> getValue(), 1)) {
                            //std::cout << 7 << std::endl;
                            *node = *(node -> getLeftChild());
                            return true; 
                        }
                    }
                    return true;
                }

            }

        }
        
        void simplify() {
            simplifyPointer(this -> root);
        }

        long double evaluateExpressionPointer(Node* node) {
            switch (node -> getToken()) {
                case NUM: return node -> getValue();
                case VAR:
                case NEGATIVE: return -evaluateExpressionPointer(node -> getLeftChild());
                case ADD: return evaluateExpressionPointer(node -> getLeftChild()) + evaluateExpressionPointer(node -> getRightChild());
                case SUB: return evaluateExpressionPointer(node -> getLeftChild()) - evaluateExpressionPointer(node -> getRightChild());
                case MUL: return evaluateExpressionPointer(node -> getLeftChild()) * evaluateExpressionPointer(node -> getRightChild());
                case DIV: return evaluateExpressionPointer(node -> getLeftChild()) / evaluateExpressionPointer(node -> getRightChild());
                case POW: return pow(evaluateExpressionPointer(node -> getLeftChild()), evaluateExpressionPointer(node -> getRightChild()));
                case SQRT: return sqrtl(evaluateExpressionPointer(node -> getLeftChild()));
                case LN: return logl(evaluateExpressionPointer(node -> getLeftChild()));
                case EXP: return expl(evaluateExpressionPointer(node -> getLeftChild()));
                case SIN: return sinl(evaluateExpressionPointer(node -> getLeftChild()));
                case COS: return cosl(evaluateExpressionPointer(node -> getLeftChild()));
                case TAN: return tanl(evaluateExpressionPointer(node -> getLeftChild()));
                case SEC: return 1.0 / cosl(evaluateExpressionPointer(node -> getLeftChild()));
                case CSC: return 1.0 / sinl(evaluateExpressionPointer(node -> getLeftChild()));
                case COT: return 1.0 / tanl(evaluateExpressionPointer(node -> getLeftChild()));
                case ASIN: return asinl(evaluateExpressionPointer(node -> getLeftChild()));
                case ACOS: return acosl(evaluateExpressionPointer(node -> getLeftChild()));
                case ATAN: return atanl(evaluateExpressionPointer(node -> getLeftChild()));
                default: return 0;
            }
        }

        long double evaluateExpression() {
            return evaluateExpressionPointer(this -> root);
        }

        
        Expression derivativePointer(Node* node) {
            switch (node -> getToken()) {
                case NUM: return Expression(addNode(Node(NUM, 0)));
                case VAR: return Expression(addNode(Node(NUM, 1)));
                case ADD: return derivativePointer(node -> getLeftChild()) + derivativePointer(node -> getRightChild());
                case SUB: return derivativePointer(node -> getLeftChild()) - derivativePointer(node -> getRightChild());
                case MUL: return (derivativePointer(node -> getLeftChild()) * Expression(node -> getRightChild()) + derivativePointer(node -> getRightChild()) * Expression(node -> getLeftChild()));
                case DIV: return ((derivativePointer(node -> getLeftChild()) * Expression(node -> getRightChild()) - derivativePointer(node -> getRightChild()) * Expression(node -> getLeftChild())) / (Expression(node -> getRightChild()) ^ Expression("2")));
                case POW: return (Expression(node -> getRightChild()) * (Expression(node -> getLeftChild()) ^ (Expression(node -> getRightChild()) - Expression("1"))) * derivativePointer(node -> getLeftChild()));
                case SQRT: return (Expression("1") / (Expression("2") * Expression(addNode(Node(SQRT, 0, node -> getLeftChild(), nullptr))) * derivativePointer(node -> getLeftChild())));
                case LN: return (Expression("1") / Expression(node -> getLeftChild()) * derivativePointer(node -> getLeftChild()));
                case EXP: return Expression(addNode(Node(EXP, 0, node -> getLeftChild(), nullptr))) * derivativePointer(node -> getLeftChild());
                case SIN: return Expression(addNode(Node(COS, 0, node -> getLeftChild(), nullptr))) * derivativePointer(node -> getLeftChild());
                case COS: return Expression("0") - Expression(addNode(Node(SIN, 0, node -> getLeftChild(), nullptr))) * derivativePointer(node -> getLeftChild());
                case TAN: return Expression(addNode(Node(SEC, 0, node -> getLeftChild(), nullptr))) ^ Expression("2") * derivativePointer(node -> getLeftChild());
                case SEC: return Expression(addNode(Node(SEC, 0, node -> getLeftChild(), nullptr))) * Expression(addNode(Node(TAN, 0, node -> getLeftChild(), nullptr))) * derivativePointer(node -> getLeftChild());
                case CSC: return (Expression("0") - Expression(addNode(Node(CSC, 0, node -> getLeftChild(), nullptr)))) * Expression(addNode(Node(COT, 0, node -> getLeftChild(), nullptr))) * derivativePointer(node -> getLeftChild());
                case COT: return Expression("0") - (Expression(addNode(Node(CSC, 0, node -> getLeftChild(), nullptr))) ^ Expression("2")) * derivativePointer(node -> getLeftChild());
                //case ASIN: return Expression("1") / Expression(addNode(Node(SQRT, 0, (), nullptr)));
                //case ACOS: return acosl(evaluateExpressionPointer(node -> getLeftChild()));
                //case ATAN: return atanl(evaluateExpressionPointer(node -> getLeftChild()));
                default: return 0;
            }
        }


        Expression derivative() {
            return derivativePointer(this -> root);
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
    //Expression d("1960/(sqrt(3)/2)");

    //printNodeVector(d.TokenizeString("-1+(2*3.5)-(-3+sin(2.0))"));

    //std::cout << std::endl;
    //for (int i = 0; i <= lastNode; i++) {
    //    nodeList[i].printNode();
    //} 
    //Expression e = d.derivative();

    //std::cout << d.getExpressionString() << std::endl;
    //std::cout << d.evaluateExpression() << std::endl;

    //std::cout << d.evaluateExpression() << std::endl;
    std::cout << cmpLongDouble(1, 1) << std::endl;
    while (1) {
        std::cout << "input: ";
        std::string s;
        std::cin >> s;
        Expression e(s);
        //std::cout << "= " << e.evaluateExpression() << std::endl;
        Expression de = e.derivative();
        std::cout << "dx= " << de.getExpressionString() << std::endl;
        de.simplify();
        std::cout << "simplified dx: " << de.getExpressionString() << std::endl;
        e.simplify();
        std::cout << "simplified e: " << e.getExpressionString() << std::endl;
        
        for (int i = 0; i <= lastNode; i++) {
            //nodeList[i].printNode();
        } 
    }
    return 0;
}

/*
-1+sin(2.45+3*3/53.4*exp(34.1+sqrt(-2+5)))=-1.606
*/
