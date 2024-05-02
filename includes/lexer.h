//57:57
#pragma once
#include <iostream>
#include <variant>
#include <vector>

enum SyntaxKind {
	NumberToken,
	WhitespaceToken,
	PlusToken,
	MinusToken,
	StarToken,
	SlashToken,
	OpenParenthesisToken,
	CloseParenthesisToken,
	EndOfFileToken,
	BadToken,
	Expression,
	NumberExpression,
	BinaryExpression,
	ParenthesizedExpression,
	UnaryExpression,
	SyntaxTreeExpression
};

class SyntaxNode {
	public:
		SyntaxNode();
		virtual ~SyntaxNode();
		SyntaxNode(const SyntaxNode&);
		SyntaxNode& operator=(const SyntaxNode&);
		virtual SyntaxKind GetKind() = 0;
		virtual std::vector<SyntaxNode *> GetChildren() = 0;
};

class SyntaxToken : virtual public SyntaxNode {
	public:
		SyntaxToken() {
			m_kind = SyntaxKind::BadToken;
			m_position = 0;
			m_text = "";
			m_value = 0;
		}
		SyntaxToken(SyntaxKind kind, int position, std::string text, std::variant<int, std::string> value) {
			m_kind = kind;
			m_position = position;
			m_text = text;
			m_value = value;
		}	
		virtual ~SyntaxToken() {}
		SyntaxKind GetKind() override {
			return m_kind;
		}
		std::vector<SyntaxNode *> GetChildren() override {
			return std::vector<SyntaxNode *>();
		}
		std::string GetText() const {
			return m_text;
		}
		int GetPosition() const {
			return m_position;
		}
		std::variant<int, std::string> GetValue() const {
			return m_value;
		}
		SyntaxToken(const SyntaxToken &other) {
			*this = other;
		}
		SyntaxToken &operator=(const SyntaxToken &other) {
			m_kind = other.m_kind;
			m_position = other.m_position;
			m_text = other.m_text;
			m_value = other.m_value;
			return *this;
		}
	private:
		SyntaxKind m_kind;
		int m_position;
		std::string m_text;
		std::variant<int, std::string> m_value;
};

class Lexer {
	public:
		Lexer(std::string text);
		~Lexer();
		Lexer(const Lexer&) = delete;
		Lexer& operator=(const Lexer&) = delete;
		SyntaxToken GetNextToken();
		std::vector<std::string> GetDiagnostics() const {
			return diagnostics;
		}
	private:

		char Current() const;
		void next();
		std::vector<std::string> diagnostics;
		std::string text;
		int pos;	
};
