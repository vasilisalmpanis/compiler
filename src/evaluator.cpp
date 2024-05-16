#include "../includes/evaluator.hpp"
#include "../includes/parser.hpp"
#include <vector>


Evaluator::Evaluator(ExpressionSyntax *root) : root(root) {
}

Evaluator::Evaluator(const Evaluator &evaluator) : root(evaluator.root) {
}

Evaluator &Evaluator::operator=(const Evaluator &evaluator) {
	if (this != &evaluator) {
		root = evaluator.root;
	}
	return *this;
}

Evaluator::~Evaluator() {
}

int Evaluator::evaluate() {
	return EvaluateExpression(root);
}

int Evaluator::EvaluateExpression(ExpressionSyntax *root) {
	LiteralExpressionSyntax *literal = dynamic_cast<LiteralExpressionSyntax *>(root);
	BinaryExpressionSyntax *binary = dynamic_cast<BinaryExpressionSyntax *>(root);
	ParenthesizedExpressionSyntax *parenthesized = dynamic_cast<ParenthesizedExpressionSyntax *>(root);

	if (literal)
		return literal->GetValue();
	if (binary) {
		std::vector<SyntaxNode *> children = binary->GetChildren();
		ExpressionSyntax *left = dynamic_cast<ExpressionSyntax *>(children[0]);
		ExpressionSyntax *right = dynamic_cast<ExpressionSyntax *>(children[2]);
		SyntaxToken *operatorToken = dynamic_cast<SyntaxToken *>(children[1]);
		int leftValue = EvaluateExpression(left);
		int rightValue = EvaluateExpression(right);
		if (operatorToken->GetKind() == SyntaxKind::PlusToken)
			return leftValue + rightValue;
		if (operatorToken->GetKind() == SyntaxKind::MinusToken)
			return leftValue - rightValue;
		if (operatorToken->GetKind() == SyntaxKind::StarToken)
			return leftValue * rightValue;
		if (operatorToken->GetKind() == SyntaxKind::SlashToken)
			return leftValue / rightValue;
		else
			throw std::runtime_error("Unexpected binary operator");
	}
	if (parenthesized) {
		ExpressionSyntax *expression = dynamic_cast<ExpressionSyntax *>(parenthesized->GetExpression());
		return EvaluateExpression(expression);
	}
	//std::cerr << "Unexpected node: " << root->GetKind() << std::endl;
	throw std::runtime_error("Unexpected node");
}
