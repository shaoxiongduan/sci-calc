#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "Util.h"
#include "Node.h"


class Expression {
    public:
        Expression();

        Expression(Node* root);

        Expression(std::string str);

        Expression(std::vector <Node> nodes);

        Node* const getRoot() const;

        Expression operator +(const Expression& rhs) const;

        Expression operator -(const Expression& rhs) const;

        Expression operator *(const Expression& rhs) const;

        Expression operator /(const Expression& rhs) const;

        Expression operator ^(const Expression& rhs) const;

        std::vector <Node> parseString(std::string str);

        std::queue <Node> shuntingYard(std::vector <Node> nodes);

        Node* buildTree(std::queue <Node> rpn);

        std::string getExpressionStringPointer(Node* node);

        std::string getExpressionString();

        bool simplifyPointer(Node* node); //WARNING!!! THIS FUNCTION WOULD MODIFY NODES THAT MIGHT BE LINKED TO PREVIOUS EXPRESSIONS!! IT IS ALWAYS RECOMMENDED TO DO COPYEXPRESSION FIRST, THEN SIMPLIFY ON THAT. true: has variable, false: no variables must do non variable first
        
        void simplify();

        long double evaluateExpressionPointer(Node* node);

        long double evaluateExpression();

        Expression derivativePointer(Node* node); // needs fixing

        Expression derivative();
         
    private:
        Node* root;
};

#endif