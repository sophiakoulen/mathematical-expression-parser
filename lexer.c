#include "eval.h"

extern t_tree	*tok_list;

t_token *scan_token(char *str)
{
	(void)str;
	if (!tok_list)
		return (0);
	else
		return (tok_list->tok);
}

void next_token(char **str)
{
	(void)str;
	tok_list = tok_list->right;
}

t_token *lexer(char **str)
{
	t_token *tok;

	while (isspace(**str))
	{
		(*str)++;
	}
	if (**str == '\0')
	{
		return (0);
	}
	else
	{
		tok = malloc(sizeof(t_token));
		if (!tok)
		{
			perror(0);
			return (0);
		}
		if (isdigit(**str))
		{
			tok->type = value;
			tok->value.v = parse_float(str);
			return (tok);
		}
		else
		{
			if (**str == '(')
			{
				tok->type = open;
			}
			else if (**str == ')')
			{
				tok->type = close;
			}
			else
			{
				// Check for invalid tokens :)
				if (**str != '+' && **str != '-' && **str != '*' && **str != '/')
				{
					tok->type = invalid;
					return (tok);
				}
				tok->type = operation;
				tok->value.c = **str;
			}
			(*str)++;
			return (tok);
		}
	}
}
