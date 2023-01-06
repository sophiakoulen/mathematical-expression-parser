#include "eval.h"

/*
	tok_list is a global variable that will contain the linked list of tokens.
	We also need to keep a reference to the start of the list.
*/
t_tree	*tok_list;
t_tree	*tok_start;

int main(int argc, char **argv)
{
	char	*expr;
	int		action;
	t_value	n;
	t_tree	*tree;
	t_token	*tok;
	int		status;

	if (parse_args(argc, argv, &expr, &action) != 0)
	{
		return (1);
	}
	tree = 0;

	tok_list = construct_tok_list(expr);
	tok_start = tok_list;

	if ((status = parse_expression(&expr, &tree)) != -1)
	{
		tok = scan_token(expr);
		if (tree == NULL || (tok && tok->type != end))
		{
			printf("Error while parsing tree\n");
			status = 1;
		}
		else if (action == COMPUTE)
		{
			n = evaluate(tree);
			printf("%f\n", n);
		}
		else
		{
			auto_print_tree(tree);
		}
	}
	cleanup_token_list(tok_start);
	//cleanup_tree(tree);
	return (status);
}
