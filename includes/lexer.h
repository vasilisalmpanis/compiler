//57:57
#pragma once
#include <cassert>
#include <cstdint>
#include <iostream>
#include <utility>
#include <variant>
#include <vector>

enum class SyntaxKind : std::uint8_t {
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

using Number = int;
using String = std::string;

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
		using ValueType = std::variant< Number, String, SyntaxKind>; 
		SyntaxToken() noexcept = default;
		SyntaxToken(SyntaxKind kind, int position, std::string text, ValueType value)
		: m_value{ std::move(value) }
		{
			m_kind = kind;
			m_position = position;
			m_text = text;
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
		std::variant<Number, String, SyntaxKind> GetValue() const {
			return m_value;
		}
		SyntaxToken(const SyntaxToken &other) {
			*this = other;
		}
		template<typename T>
		[[ nodiscard ]] bool is() const noexcept
		{
			return std::holds_alternative<T>(m_value);
		}
		template<typename T>
		[[ nodiscard ]] bool &get() const noexcept
		{
			assert(is <T>());
			return std::get<T>(m_value);
		}
		template<typename T>
		[[ nodiscard ]] ValueType const & value() const noexcept
		{
			return m_value;
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
		ValueType m_value;
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
