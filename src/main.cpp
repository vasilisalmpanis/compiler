#include <cstddef>
#include <iostream>
#include <string>
#include "../includes/parser.hpp"
#include "../includes/evaluator.hpp"

static void freeSyntaxTree(SyntaxNode *node)
{
	std::vector<SyntaxNode *> children = node->GetChildren();
	for (size_t i = 0; i < children.size(); i++)
		freeSyntaxTree(children[i]);
	delete node;
}

static void PrettyPrint(SyntaxNode *node, std::string indent, bool isLast)
{
	// just print the kinds of each node
	if (indent != "")
	{
		std::string marker = (isLast) ? "└──" : "├──";
		std::cout << indent << marker << " ";
		if (dynamic_cast<SyntaxToken *>(node))
		{
			SyntaxToken *token = dynamic_cast<SyntaxToken *>(node);
			std::cout << token->GetText();
		}
		else
		{
			NumberExpressionSyntax *num = dynamic_cast<NumberExpressionSyntax *>(node);
			if (num)
			{
				std::cout << std::get<int>(num->GetNumberToken().GetValue());
			}
		}
		std::cout << std::endl;
	}
	if (indent == "")
		indent += (isLast) ? " " : "│   ";
	else
		indent += (isLast) ? "    " : "│   ";
	std::vector<SyntaxNode *> children = node->GetChildren();
	for (size_t i = 0; i < children.size(); i++)
		PrettyPrint(children[i], indent, i == children.size() - 1);
}

int main()
{
	std::string input;
	bool printTree = false;
	while (true) {
		std::cout << "Write an arithmetic expression: ";
		std::getline(std::cin, input);
		if (input == "exit")
			break;
		if (input == "print")
		{
			printTree = !printTree;
			continue;
		}
		// Create a syntax tree
		ExpressionSyntax *expression = SyntaxTree::Parse(input);
		if (printTree)
			PrettyPrint(expression, "", true);
		// Create an evaluator and evaluate the expression
		std::vector<SyntaxNode *> children = expression->GetChildren();
		Evaluator evaluator(dynamic_cast<ExpressionSyntax *>(children[0]));
		try {
			// Evaluate the expression
			int result = evaluator.evaluate();
			std::cout << "Result: " << result << std::endl;
		}
		catch (const std::exception &e)
		{
			std::cout << e.what() << std::endl;
			freeSyntaxTree(expression);
			return 1;
		}
		freeSyntaxTree(expression);
	}
	return 0;
}
