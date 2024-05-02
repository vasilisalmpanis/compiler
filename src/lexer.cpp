#include "../includes/lexer.h"
#include <exception>

Lexer::Lexer(std::string text) {
	this->text = text;
	this->pos = 0;
}


Lexer::~Lexer() {
}


// Private
char Lexer::Current() const {
	if (pos >= static_cast<int>(text.length())) {
		return '\0';
	}
	return text[pos];
}

void Lexer::next() {
	pos++;
}

SyntaxToken Lexer::GetNextToken()
{
	if (pos >= static_cast<int>(text.length())) {
		return SyntaxToken(SyntaxKind::EndOfFileToken, pos, "", 0);
	}
	if (std::isdigit(Current())) {
		int start = pos;
		while (std::isdigit(Current()))
			next();
		int length = pos - start;
		std::string temp_text = text.substr(start, length);
		try {
			int temp_value = std::stoi(temp_text);
			return SyntaxToken(SyntaxKind::NumberToken, start, temp_text, temp_value);
		}
		catch (const std::exception& e) {
			std::string error_string = "ERROR: number out of range: ";
			error_string += temp_text;
			diagnostics.push_back(error_string);
			return SyntaxToken(SyntaxKind::BadToken, start, temp_text, 0);
		}
	}
	if (std::iswspace(Current())) {
		int start = pos;
		while (std::iswspace(Current()))
			next();
		int length = pos - start;
		std::string temp_text = text.substr(start, length);
		return SyntaxToken(SyntaxKind::WhitespaceToken, start, temp_text, 0);
	}
	if (Current() == '+') {
		return SyntaxToken(SyntaxKind::PlusToken, pos++, "+", 0);
	}
	if (Current() == '-') {
		return SyntaxToken(SyntaxKind::MinusToken, pos++, "-", 0);
	}
	if (Current() == '*') {
		return SyntaxToken(SyntaxKind::StarToken, pos++, "*", 0);
	}
	if (Current() == '/') {
		return SyntaxToken(SyntaxKind::SlashToken, pos++, "/", 0);
	}
	if (Current() == '(') {
		return SyntaxToken(SyntaxKind::OpenParenthesisToken, pos++, "(", 0);
	}
	if (Current() == ')') {
		return SyntaxToken(SyntaxKind::CloseParenthesisToken, pos++, ")", 0);
	}
	std::string error_string = "ERROR: bad character input: ";
	error_string += Current();
	std::cout << error_string << std::endl;
	diagnostics.push_back(error_string);
	SyntaxToken token = SyntaxToken(SyntaxKind::BadToken, pos, text.substr(pos, 1), 0);
	next();
	return token; 
}
