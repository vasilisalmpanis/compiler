#include "../includes/lexer.h"
#include "../includes/parser.hpp"
#include <vector>

SyntaxTree::SyntaxTree(std::vector<std::string> diagnostics, ExpressionSyntax *root, SyntaxToken endOfFileToken):
	m_diagnostics(diagnostics), m_root(root), m_endOfFileToken(endOfFileToken)
{
}

SyntaxTree::~SyntaxTree()
{
}

SyntaxNode::SyntaxNode()
{
}

SyntaxNode::~SyntaxNode()
{
}

ExpressionSyntax::ExpressionSyntax()
{
}

ExpressionSyntax::~ExpressionSyntax()
{
}

ExpressionSyntax::ExpressionSyntax(const ExpressionSyntax& other)
{
	*this = other;
}

ExpressionSyntax& ExpressionSyntax::operator=(const ExpressionSyntax& other)
{
	return *this;
}

SyntaxKind ExpressionSyntax::GetKind()
{
	return SyntaxKind::Expression;
}

std::vector<SyntaxNode *> ExpressionSyntax::GetChildren()
{
	return std::vector<SyntaxNode *>();
}

NumberExpressionSyntax::~NumberExpressionSyntax()
{
}

NumberExpressionSyntax::NumberExpressionSyntax(const NumberExpressionSyntax& other)
{
	*this = other;
}

NumberExpressionSyntax& NumberExpressionSyntax::operator=(const NumberExpressionSyntax& other)
{
	m_numberToken = other.m_numberToken;
	return *this;
}

BinaryExpressionSyntax::~BinaryExpressionSyntax()
{
}

BinaryExpressionSyntax::BinaryExpressionSyntax(const BinaryExpressionSyntax& other)
{
	*this = other;
}

BinaryExpressionSyntax& BinaryExpressionSyntax::operator=(const BinaryExpressionSyntax& other)
{
	m_left = other.m_left;
	m_operatorToken = other.m_operatorToken;
	m_right = other.m_right;
	return *this;
}

// Parenthesis

ParenthesizedExpressionSyntax::~ParenthesizedExpressionSyntax()
{
}

ParenthesizedExpressionSyntax::ParenthesizedExpressionSyntax(const ParenthesizedExpressionSyntax& other)
{
	*this = other;
}

ParenthesizedExpressionSyntax& ParenthesizedExpressionSyntax::operator=(const ParenthesizedExpressionSyntax& other)
{
	m_openParenthesisToken = other.m_openParenthesisToken;
	m_expression = other.m_expression;
	m_closeParenthesisToken = other.m_closeParenthesisToken;
	return *this;
}

