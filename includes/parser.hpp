#pragma once
#include <iostream>
#include "lexer.h"
#include <vector>

namespace Syntax {
	class ExpressionSyntax : virtual public SyntaxNode {
		public:
			ExpressionSyntax();
			virtual ~ExpressionSyntax();
			ExpressionSyntax(const ExpressionSyntax&);
			ExpressionSyntax& operator=(const ExpressionSyntax&);
			virtual SyntaxKind			GetKind();
			[[nodiscard]] virtual std::vector<SyntaxNode *>	GetChildren();
	};


	class LiteralExpressionSyntax : virtual public ExpressionSyntax {
		public:
			LiteralExpressionSyntax(SyntaxToken literalToken)
			{
				m_literalToken = literalToken;
			}
			virtual ~LiteralExpressionSyntax();
			LiteralExpressionSyntax(const LiteralExpressionSyntax&);
			LiteralExpressionSyntax& operator=(const LiteralExpressionSyntax&);
			[[nodiscard]] virtual SyntaxKind			GetKind() override { return SyntaxKind::LiteralExpression; }
			[[nodiscard]] virtual std::vector<SyntaxNode *>	GetChildren() override { return std::vector<SyntaxNode *>(); }
			[[nodiscard]] SyntaxToken				GetNumberToken() { return m_literalToken; }
			[[nodiscard]] int					GetValue() { return std::get<int>(m_literalToken.GetValue()); }
		private:
			SyntaxToken m_literalToken;
	};

	class BinaryExpressionSyntax : virtual public ExpressionSyntax
	{
		public:
			BinaryExpressionSyntax(ExpressionSyntax *left, SyntaxToken *operatorToken, ExpressionSyntax *right)
				: m_left(left), m_operatorToken(operatorToken), m_right(right)
			{
			}
			virtual ~BinaryExpressionSyntax();
			BinaryExpressionSyntax(const BinaryExpressionSyntax&);
			BinaryExpressionSyntax& operator=(const BinaryExpressionSyntax&);
			[[nodiscard]] virtual SyntaxKind		GetKind() override { return SyntaxKind::BinaryExpression; }
			[[nodiscard]] virtual std::vector<SyntaxNode *>	GetChildren() override { return { m_left, m_operatorToken, m_right };}
			[[nodiscard]] ExpressionSyntax*			GetLeft() { return m_left; }
			[[nodiscard]] SyntaxToken*			GetOperatorToken() { return m_operatorToken; }
			[[nodiscard]] ExpressionSyntax*			GetRight() { return m_right; }
		private:
			ExpressionSyntax *m_left;
			SyntaxToken *m_operatorToken;
			ExpressionSyntax *m_right;
	};

	class UnaryExpressionSyntax: virtual public ExpressionSyntax
	{
		public:
			UnaryExpressionSyntax(SyntaxToken *operatorToken, ExpressionSyntax *operand)
				: m_operatorToken(operatorToken), m_operand(operand)
			{
			}
			virtual ~UnaryExpressionSyntax();
			UnaryExpressionSyntax(const UnaryExpressionSyntax&);
			UnaryExpressionSyntax&				operator=(const UnaryExpressionSyntax&);
			[[nodiscard]] virtual SyntaxKind		GetKind() override { return SyntaxKind::UnaryExpression; }
			[[nodiscard]] virtual std::vector<SyntaxNode *>	GetChildren() override { return { m_operatorToken, m_operand};}
			[[nodiscard]] SyntaxToken*			GetOperatorToken() { return m_operatorToken; }
			[[nodiscard]] ExpressionSyntax*			GetOperand() { return m_operand; }
	private:
		SyntaxToken *m_operatorToken;
		ExpressionSyntax *m_operand;
};

	class ParenthesizedExpressionSyntax : virtual public ExpressionSyntax
	{
		public:
			ParenthesizedExpressionSyntax(SyntaxToken *openParenthesisToken, ExpressionSyntax *expression, SyntaxToken *closeParenthesisToken)
				: m_openParenthesisToken(openParenthesisToken), m_expression(expression), m_closeParenthesisToken(closeParenthesisToken)
			{
			}
			ParenthesizedExpressionSyntax(const ParenthesizedExpressionSyntax&);
			virtual ~ParenthesizedExpressionSyntax();
			ParenthesizedExpressionSyntax&				operator=(const ParenthesizedExpressionSyntax&);
			[[nodiscard]] virtual SyntaxKind			GetKind() override { return SyntaxKind::ParenthesizedExpression; }
			[[nodiscard]] virtual std::vector<SyntaxNode *>		GetChildren() override { return { m_openParenthesisToken, m_expression, m_closeParenthesisToken }; }
			[[nodiscard]] ExpressionSyntax				*GetExpression() { return m_expression; }
	
		private:
			SyntaxToken *m_openParenthesisToken;
			ExpressionSyntax *m_expression;
			SyntaxToken *m_closeParenthesisToken;
	};
	class SyntaxTree;
}


using namespace Syntax;
class Parser {
	public:
		Parser(std::string Text);
		~Parser();
		Parser(const Parser&) = delete;
		Parser& operator=(const Parser&) = delete;
		[[nodiscard]] SyntaxTree*	Parse();
		[[nodiscard]] ExpressionSyntax*	ParseMultiplicativeExpression();
		[[nodiscard]] std::vector<std::string>	GetDiagnostics() const { return m_diagnostics; }
		void				setDiagnostics(std::vector<std::string> diagnostics) { m_diagnostics = diagnostics; }
		struct SyntaxFact 
		{
			[[nodiscard]] static int GetUnaryOperatorPrecedence(SyntaxKind kind);
			[[nodiscard]] static int GetBinaryOperatorPrecedence(SyntaxKind kind);
		};
	private:
		SyntaxToken			peek(int offset);
		SyntaxToken			current();
		SyntaxToken			nextToken();
		ExpressionSyntax*		parsePrimaryExpression();
		ExpressionSyntax*		ParseExpression(int parentPrecedence = 0);
		static int			GetBinaryOperatorPrecedence(SyntaxKind kind);
		static int			GetUnaryOperatorPrecedence(SyntaxKind kind);
		SyntaxToken			matchToken(SyntaxKind kind);

		std::vector<std::string>	m_diagnostics;
		std::vector<SyntaxToken>	m_tokens;
		int 				m_position;

};

class Syntax::SyntaxTree : virtual public ExpressionSyntax {
	public:
		SyntaxTree(std::vector<std::string> diagnostics, ExpressionSyntax *root, SyntaxToken endOfFileToken);
		virtual ~SyntaxTree();
		SyntaxTree(const SyntaxTree&);
		SyntaxTree&				operator=(const SyntaxTree&);
		[[nodiscard]] virtual SyntaxKind		GetKind() override { return SyntaxKind::SyntaxTreeExpression; }
		[[nodiscard]] virtual std::vector<SyntaxNode *>	GetChildren() override { return { m_root }; }
		[[nodiscard]] static ExpressionSyntax*		Parse(std::string text) {
			Parser parser(text);
			return parser.Parse();
		}
	private:
		std::vector<std::string>	m_diagnostics;
		ExpressionSyntax		*m_root;
		SyntaxToken			m_endOfFileToken;
};
