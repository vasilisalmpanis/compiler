#include "../includes/parser.hpp"
#include "../includes/lexer.h"
#include <cstddef>

/* 
 * Constructor
 * @param text: the text to be parsed
*/
Parser::Parser(std::string text): m_position(0)
{
	Lexer lexer(text);
	setDiagnostics(lexer.GetDiagnostics());
	std::vector<SyntaxToken> tokens;
	SyntaxToken token;
	do {
		token = lexer.GetNextToken();
		if (token.GetKind() != SyntaxKind::WhitespaceToken) {
			tokens.push_back(token);
		}
	} while (token.GetKind() != SyntaxKind::EndOfFileToken);
	m_tokens = tokens;
}

/* 
 * Destructor
*/
Parser::~Parser()
{
}

/* 
 * Parse the text
 * @return the parsed expression
*/
SyntaxTree* Parser::Parse()
{
	ExpressionSyntax *expression = ParseExpression(0);
	SyntaxToken endOfFileToken = matchToken(SyntaxKind::EndOfFileToken);
	return new SyntaxTree(m_diagnostics, expression, endOfFileToken);
}

ExpressionSyntax* Parser::ParseExpression(int parentPrecedence)
{
	ExpressionSyntax *left;
	int unaryPrecedence = SyntaxFact::GetUnaryOperatorPrecedence(current().GetKind());
	if (unaryPrecedence != 0 && unaryPrecedence >= parentPrecedence) {
		SyntaxToken *operatorToken = new SyntaxToken(current());
		nextToken();
		ExpressionSyntax *operand = ParseExpression(unaryPrecedence);
		left = new UnaryExpressionSyntax(operatorToken, operand);
	}
	else {
		left = parsePrimaryExpression();
	}
	while (true)
	{
		int precedence = SyntaxFact::GetBinaryOperatorPrecedence(current().GetKind());
		if (precedence == 0 || precedence <= parentPrecedence) {
			break;
		}
		SyntaxToken *operatorToken = new SyntaxToken(current());
		nextToken();
		ExpressionSyntax *right = ParseExpression(precedence);
		left = new BinaryExpressionSyntax(left, operatorToken, right);
	}
	return left;
}

int Parser::SyntaxFact::GetBinaryOperatorPrecedence(SyntaxKind kind)
{
	switch (kind) {
		case SyntaxKind::PlusToken:
		case SyntaxKind::MinusToken:
			return 1;
		case SyntaxKind::StarToken:
		case SyntaxKind::SlashToken:
			return 2;
		default:
			return 0;
	}
}
 int Parser::SyntaxFact::GetUnaryOperatorPrecedence(SyntaxKind kind)
{
	switch (kind) {
		case SyntaxKind::PlusToken:
		case SyntaxKind::MinusToken:
			return 3;
		default:
			return 0;
	}
}

ExpressionSyntax* Parser::ParseMultiplicativeExpression()
{
	ExpressionSyntax *left = parsePrimaryExpression();
	while (	current().GetKind() == SyntaxKind::StarToken
			||current().GetKind() == SyntaxKind::SlashToken
			) {
		SyntaxToken *operatorToken = new SyntaxToken(current());
		nextToken();
		ExpressionSyntax *right = parsePrimaryExpression();
		left = new BinaryExpressionSyntax(left, operatorToken, right);
	}
	return left;

}
// Private methods


/* 
 * Peek at the token at the current position + offset
 * @param offset: the offset to peek at
 * @return the token at the current position + offset
*/
SyntaxToken Parser::peek(int offset)
{
	size_t index = m_position + offset;
	if (index >= m_tokens.size()) {
		return m_tokens[m_tokens.size() - 1];
	}
	return m_tokens[index];
}

/* 
 * Get the current token
 * @return the token at the current position
*/
SyntaxToken Parser::current()
{
	return peek(0);
}

/* 
 * Get the next token
 * @return the token at the current position
*/
SyntaxToken Parser::nextToken()
{
	SyntaxToken currentToken = current();
	m_position++;
	return currentToken;
}

/* 
 * Parse the primary expression
 * @return the parsed expression
*/
ExpressionSyntax* Parser::parsePrimaryExpression()
{
	if (current().GetKind() == SyntaxKind::OpenParenthesisToken) {
		SyntaxToken *left = new SyntaxToken(current());
		nextToken();
		ExpressionSyntax *expression = ParseExpression();
		SyntaxToken *right = new SyntaxToken(matchToken(SyntaxKind::CloseParenthesisToken));
		return new ParenthesizedExpressionSyntax(left, expression, right);
	}
	SyntaxToken numberToken = matchToken(SyntaxKind::NumberToken);
	return new LiteralExpressionSyntax(numberToken);
}

/* 
 * Match the token with the expected kind
 * @param kind: the expected kind
 * @return the token
*/
SyntaxToken Parser::matchToken(SyntaxKind kind)
{
	if (current().GetKind() == kind) {
		return nextToken();
	}
	std::string error_message = "ERROR: unexpected token <";
	printf("%s\n", current().GetText().c_str());
	error_message += current().GetText() + ">";
	m_diagnostics.push_back(error_message);
	return SyntaxToken(kind, current().GetPosition(), "", 0);
}
