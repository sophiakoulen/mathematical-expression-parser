#include "eval.h"

t_tree	*factory(t_token *t)
{
	t_tree	*new_node;

	new_node = malloc(sizeof(t_tree));
	if (!new_node)
	{
		perror(0);
		return (0);
	}
	new_node->tok = t;
	new_node->left = 0;
	new_node->right = 0;
	return (new_node);
}

t_tree	*create_node(t_token *new_token, t_tree *left, t_tree *right)
{
	t_tree	*new_node;

	new_node = factory(new_token);
	if (!new_node)
		return (0);
	new_node->left = left;
	new_node->right = right;
	return	(new_node);
}

int	parse_expression(char **str, t_tree **left_tree)
{
	t_token *tok;
	t_tree	*right_tree;
	t_tree	*tmp;

	right_tree = 0;
	if (parse_term(str, left_tree) == -1) //here is the evil leak, in left_tree
	{
		return (-1);
	}
	while (1)
	{
		tok = scan_token();
		if (!tok || tok->type == end)
			return 0;
		if (!(tok->type == symbol && (tok->value.c == '+' || tok->value.c == '-')))
		{
			return (0);
		}
		else
		{
			next_token();
			if (parse_term(str, &right_tree) == -1)
			{
				//cleanup_tree(right_tree);
				return (-1);
			}
			tmp = create_node(tok, *left_tree, right_tree);
			if (!tmp)
			{
				//cleanup_tree(right_tree);
				return (-1);
			}
			*left_tree = tmp;
		}
	}
}

int	parse_term(char **str, t_tree **left_tree)
{
	t_token	*tok;
	t_tree	*right_tree;
	t_tree	*tmp;

	right_tree = 0;
	if (parse_factor(str, left_tree) == -1) //here is the evil leak, in left_tree
	{
		return (-1);
	}
	while (1)
	{
		tok = scan_token();
		if (!tok || tok->type == end)
			return (0);
		if (!(tok->type == symbol && (tok->value.c == '*' || tok->value.c == '/')))
		{
			return (0);
		}
		else
		{
			next_token();
			if (parse_factor(str, &right_tree) == -1)
			{
				//cleanup_tree(right_tree);
				return (-1);
			}
			tmp = create_node(tok, *left_tree, right_tree);
			if (!tmp)
			{
				//cleanup_tree(right_tree);
			}
			*left_tree = tmp;
		}
	}
}

int parse_factor(char **str, t_tree **tree)
{
	t_token *tok;
	t_tree	*tmp;

	tok = scan_token();
	if (!tok || tok->type == end) // check if scan_token returned a valid token
	{
		printf("Parse error: unexpected end of input\n");
		return -1;
	}
	next_token();
	if (tok->type == symbol && tok->value.c == '(')
	{
		if (parse_expression(str, tree) == -1)
		{
			return (-1);
		}
		// Check if the next token is a close parenthesis
		tok = scan_token();
		if (tok && tok->type == symbol && tok->value.c == ')')
		{
			next_token();
		}
		else
		{
			printf("Parse error: expecting closing parenthesis\n");
			return (-1);
		}
	}
	else if (tok->type == symbol && tok->value.c == '-')
	{
		if (parse_factor(str, tree) == -1)
		{
			return (-1);
		}
		tmp = create_node(tok, *tree, 0);
		if (!tmp)
		{
			return (-1);
		}
	}
	else if (tok->type == value)
	{
		*tree = factory(tok);
		if (!*tree)
		{
			return (-1);
		}
	}
	else
	{
		printf("Parse error: unexpected token\n");
		return (-1);
	}
	return 0;
}
