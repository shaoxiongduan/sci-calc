#ifndef EXPRESSION_H
#define EXPRESSION_H

#include "../Utils/Util.h"
#include "Node.h"

// The Expression Class.
// A Expression consists of a root node, with each Node linked to others, building a tree
class Expression {

    public:
        Expression();
        Expression(Node* root);
        Expression(Node* root, bool isRPN);
        Expression(std::string str);
        Expression(std::string str, bool isRPN);
        Expression(std::vector <Node> nodes);
        Expression(std::vector <Node> nodes, bool isRPN);

        Node* const getRoot() const;

        // These are used for calculating the derivatives of Expressions
        Expression operator +(const Expression& rhs) const;
        Expression operator -(const Expression& rhs) const;
        Expression operator *(const Expression& rhs) const;
        Expression operator /(const Expression& rhs) const;
        Expression operator ^(const Expression& rhs) const;

        std::vector <Node> parseString(std::string str);
        std::vector <Node> parseStringRPN(std::string str);

        // Syntax Checking Functions, returns false when the syntax is wrong
        bool checkSyntax(std::vector <Node> nodes);
        bool checkSyntax(std::string str);

        std::queue <Node> shuntingYard(std::vector <Node> nodes);
        std::queue <Node> parseRPN(std::vector <Node> nodes);

        Node* buildTree(std::queue <Node> rpn);

        std::string getExpressionStringPointer(Node* node);
        std::string getExpressionString();

        bool simplifyPointer(Node* node); 
        // WARNING!!! simplifyPointer WOULD MODIFY NODES THAT MIGHT BE LINKED TO PREVIOUS EXPRESSIONS!!
        // IT IS ALWAYS RECOMMENDED TO DO COPYEXPRESSION FIRST, THEN SIMPLIFY ON THAT. 
        void simplify();

        // Evaluate Expressions
        long double evaluateExpressionPointer(Node* node);
        long double evaluateExpression();

        // Derivative Calculation
        Expression derivativePointer(Node* node); // needs fixing
        Expression derivative();
         
    private:
        Node* root;
        bool isValidSyntax;
        bool isRPN; // RPN mode for the expression
};

extern Expression syntaxChecker;

#endif