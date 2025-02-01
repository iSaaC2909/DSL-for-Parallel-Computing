#include <iostream>
#include <vector>
#include <string>
#include <memory>
#include <unordered_map>
#include <algorithm>

using namespace std;

// AST Node Definitions
struct ASTNode {
    virtual ~ASTNode() = default;
    virtual void print() const = 0;
    string result; // Used to store the result of intermediate code generation
};

struct NumberNode : ASTNode {
    int value;
    NumberNode(int val) : value(val) {}
    void print() const override {
        cout << "Number(" << value << ")";
    }
};

struct IdentifierNode : ASTNode {
    string name;
    IdentifierNode(const string& n) : name(n) {}
    void print() const override {
        cout << "Identifier(" << name << ")";
    }
};

struct BinaryOpNode : ASTNode {
    string op;
    unique_ptr<ASTNode> left, right;
    BinaryOpNode(const string& o, unique_ptr<ASTNode> l, unique_ptr<ASTNode> r)
        : op(o), left(move(l)), right(move(r)) {}
    void print() const override {
        cout << "BinaryOp(" << op << ", ";
        left->print();
        cout << ", ";
        right->print();
        cout << ")";
    }
};

struct AssignmentNode : ASTNode {
    string identifier;
    unique_ptr<ASTNode> expression;
    AssignmentNode(const string& id, unique_ptr<ASTNode> expr)
        : identifier(id), expression(move(expr)) {}
    void print() const override {
        cout << "Assignment(" << identifier << ", ";
        expression->print();
        cout << ")";
    }
};

// Parser Class
class Parser {
    vector<string> tokens;
    size_t pos = 0;

    string peek() const {
        return (pos < tokens.size()) ? tokens[pos] : "";
    }

    string consume() {
        return (pos < tokens.size()) ? tokens[pos++] : "";
    }

    bool match(const string& expected) {
        if (peek() == expected) {
            consume();
            return true;
        }
        return false;
    }

    unique_ptr<ASTNode> parseExpression();
    unique_ptr<ASTNode> parseTerm();
    unique_ptr<ASTNode> parseFactor();

public:
    Parser(const vector<string>& t) : tokens(t) {}

    unique_ptr<ASTNode> parseProgram() {
        vector<unique_ptr<ASTNode>> statements;
        while (pos < tokens.size()) {
            if (peek() == "int" || peek() == "float") {
                // Handle variable declarations (not implemented here)
                consume();
            } else if (isalpha(peek()[0])) {
                statements.push_back(parseAssignment());
            } else {
                statements.push_back(parseExpression());
            }
        }
        // For simplicity, return the last statement
        return move(statements.back());
    }

    unique_ptr<ASTNode> parseAssignment() {
        string id = consume();
        if (!match("=")) {
            throw runtime_error("Expected '=' in assignment");
        }
        auto expr = parseExpression();
        return make_unique<AssignmentNode>(id, move(expr));
    }

    unique_ptr<ASTNode> parseExpression() {
        auto left = parseTerm();
        while (peek() == "+" || peek() == "-") {
            string op = consume();
            auto right = parseTerm();
            left = make_unique<BinaryOpNode>(op, move(left), move(right));
        }
        return left;
    }

    unique_ptr<ASTNode> parseTerm() {
        auto left = parseFactor();
        while (peek() == "*" || peek() == "/") {
            string op = consume();
            auto right = parseFactor();
            left = make_unique<BinaryOpNode>(op, move(left), move(right));
        }
        return left;
    }

    unique_ptr<ASTNode> parseFactor() {
        if (match("(")) {
            auto expr = parseExpression();
            if (!match(")")) {
                throw runtime_error("Expected ')'");
            }
            return expr;
        }
        if (isdigit(peek()[0])) {
            return make_unique<NumberNode>(stoi(consume()));
        }
        if (isalpha(peek()[0])) {
            return make_unique<IdentifierNode>(consume());
        }
        throw runtime_error("Unexpected token: " + peek());
    }
};

// Symbol Table for Semantic Analysis
class SymbolTable {
    unordered_map<string, string> symbols; // Maps variable names to types

public:
    void declare(const string& name, const string& type) {
        if (symbols.find(name) != symbols.end()) {
            throw runtime_error("Variable '" + name + "' already declared");
        }
        symbols[name] = type;
    }

    string getType(const string& name) const {
        auto it = symbols.find(name);
        if (it == symbols.end()) {
            throw runtime_error("Undeclared variable '" + name + "'");
        }
        return it->second;
    }
};

// Semantic Analyzer
class SemanticAnalyzer {
    SymbolTable symbolTable;

public:
    void analyze(const ASTNode* node) {
        if (auto assign = dynamic_cast<const AssignmentNode*>(node)) {
            // Check if the variable is declared
            symbolTable.getType(assign->identifier);
            analyze(assign->expression.get());
        } else if (auto binOp = dynamic_cast<const BinaryOpNode*>(node)) {
            analyze(binOp->left.get());
            analyze(binOp->right.get());
        } else if (auto id = dynamic_cast<const IdentifierNode*>(node)) {
            // Ensure the identifier is declared
            symbolTable.getType(id->name);
        }
        // No action needed for NumberNode
    }
};

// Intermediate Representation (IR) Generator
struct TAC {
    string op;
    string arg1, arg2, result;

    TAC(const string& o, const string& a1, const string& a2, const string& res)
        : op(o), arg1(a1), arg2(a2), result(res) {}

    void print() const {
        if (op == "=") {
            cout << result << " = " << arg1 << endl;
        } else {
            cout << result << " = " << arg1 << " " << op << " " << arg2 << endl;
        }
    }
};

class IRGenerator {
    vector<TAC> instructions;
    int tempCounter = 0;

    string newTemp() {
        return "t" + to_string(tempCounter++);
    }

public:
    void generate(const ASTNode* node) {
        if (auto num = dynamic_cast<const NumberNode*>(node)) {
            string temp = newTemp();
            instructions.emplace_back("=", to_string(num->value), "", temp);
            num->result = temp;
        } else if (auto id = dynamic_cast<const IdentifierNode*>(node)) {
            string temp = newTemp();
            instructions.emplace_back("=", id->name, "", temp);
            id->result = temp;
        } else if (auto binOp = dynamic_cast<const BinaryOpNode*>(node)) {
            generate(binOp->left.get());
            generate(binOp->right.get());
            string temp = newTemp();
            instructions.emplace_back(binOp->op, binOp->left->result, binOp->right->result, temp);
            binOp->result = temp;
        } else if (auto assign = dynamic_cast<const AssignmentNode*>(node)) {
            generate(assign->expression.get());
            instructions.emplace_back("=", assign->expression->result, "", assign->identifier);
        }
    }

    void print() const {
        for (const auto& instr : instructions) {
            instr.print();
        }
    }
};

// Optimizer
class Optimizer {
public:
    void optimize(vector<TAC>& instructions) {
        for (auto& instr : instructions) {
            if (instr.op == "+" && isNumber(instr.arg1) && isNumber(instr.arg2)) {
                int val1 = stoi(instr.arg1);
                int val2 = stoi(instr.arg2);
                instr.op = "=";
                instr.arg1 = to_string(val1 + val2);
                instr.arg2 = "";
            }
            // Add more optimizations here (e.g., for *, -, /)
        }
    }

private:
    bool isNumber(const string& s) {
        return !s.empty() && all_of(s.begin(), s.end(), ::isdigit);
    }
};

// Code Generator
class CodeGenerator {
public:
    void generate(const vector<TAC>& instructions) {
        for (const auto& instr : instructions) {
            if (instr.op == "=") {
                cout << "mov eax, " << instr.arg1 << endl;
                cout << "mov [" << instr.result << "], eax" << endl;
            } else if (instr.op == "+") {
                cout << "mov eax, " << instr.arg1 << endl;
                cout << "add eax, " << instr.arg2 << endl;
                cout << "mov [" << instr.result << "], eax" << endl;
            }
            // Add more operations here (e.g., for *, -, /)
        }
    }
};

int main() {
    // Example input
    string input = "x = 10 + 20 * (30 - 5)";

    // Lexical Analysis
    DFA dfa;
    dfa.detect(input);
    vector<string> tokens = dfa.getTokens();

    // Syntax Analysis
    Parser parser(tokens);
    auto ast = parser.parseProgram();

    // Semantic Analysis
    SemanticAnalyzer semanticAnalyzer;
    semanticAnalyzer.analyze(ast.get());

    // Intermediate Code Generation
    IRGenerator irGenerator;
    irGenerator.generate(ast.get());

    // Optimization
    Optimizer optimizer;
    optimizer.optimize(irGenerator.instructions);

    // Print Intermediate Representation
    cout << "Intermediate Representation (IR):" << endl;
    irGenerator.print();

    // Code Generation
    CodeGenerator codeGenerator;
    cout << "\nGenerated Assembly Code:" << endl;
    codeGenerator.generate(irGenerator.instructions);

    return 0;
}