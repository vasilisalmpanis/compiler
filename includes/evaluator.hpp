#pragma once
#include "parser.hpp"


class Evaluator {

	public:
		Evaluator(ExpressionSyntax *root);
		Evaluator(const Evaluator &evaluator);
		Evaluator &operator=(const Evaluator &evaluator);
		~Evaluator();

		int evaluate();
	private:
		int EvaluateExpression(ExpressionSyntax *root);
		ExpressionSyntax *root;
};
