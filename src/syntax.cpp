#include "../includes/lexer.h"
#include "../includes/parser.hpp"
#include <vector>

SyntaxNode::SyntaxNode()
{
}

SyntaxNode::~SyntaxNode()
{
}

namespace Syntax {


	SyntaxTree::SyntaxTree(std::vector<std::string> diagnostics, ExpressionSyntax *root, SyntaxToken endOfFileToken):
		m_diagnostics(diagnostics), m_root(root), m_endOfFileToken(endOfFileToken)
	{
	}

	SyntaxTree::~SyntaxTree()
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

	LiteralExpressionSyntax::~LiteralExpressionSyntax()
	{
	}

	LiteralExpressionSyntax::LiteralExpressionSyntax(const LiteralExpressionSyntax& other)
	{
		*this = other;
	}

	LiteralExpressionSyntax& LiteralExpressionSyntax::operator=(const LiteralExpressionSyntax& other)
	{
		m_literalToken = other.m_literalToken;
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

	// UnaryExpressionSyntax

	UnaryExpressionSyntax::~UnaryExpressionSyntax()
	{
	}

	UnaryExpressionSyntax::UnaryExpressionSyntax(const UnaryExpressionSyntax& other)
	{
		*this = other;
	}

	UnaryExpressionSyntax& UnaryExpressionSyntax::operator=(const UnaryExpressionSyntax& other)
	{
		m_operatorToken = other.m_operatorToken;
		m_operand = other.m_operand;
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
}
