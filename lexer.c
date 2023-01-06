#include "eval.h"

extern t_tree	*tok_list;

/* 
	Return the next token from the token_list.
*/
t_token	*scan_token(void)
{
	if (!tok_list)
		return (0);
	else
		return (tok_list->tok);
}

/*
	Move the pointer to the next token from the token_list.
*/
void	next_token(void)
{
	tok_list = tok_list->right;
}

/**
 * This will make a new linked list of the found tokens.
 * It will be a doubly linked list that re-uses the t_tree struct
 * with left / right corresponding to the previous / next item in the list.
 */
t_tree	*construct_tok_list(char *str)
{
	t_tree	*start;
	t_tree	*current;
	t_tree	*tmp;
	t_token	*tok;

	start = NULL;
	while (1)
	{
		tok = lexer(&str);
		if (tok == NULL)
			return (start);
		tmp = factory(tok);
		if (tmp == NULL)
			return (NULL);
		if (start == NULL)
		{
			start = tmp;
			current = tmp;
		}
		else
		{
			current->right = tmp;
			tmp->left = current;
			tmp->right = 0;
			current = tmp;
		}
		if (tok->type == end)
			return (start);
	}
}

/*
	Return a token and move the string pointer to the next character
	to analyse.

	TODO: here we can add the code to detect multi character word as identifiers
	either match agaist a dictionary of possibilities, like pi pow sqrt etc..
	or single letter constants like e or G
	or record the string to be used as a variable name
	for now it's just invalid whatever this does, it would need to advance str
*/
t_token	*lexer(char **str)
{
	t_token *tok;

	while (isspace(**str))
		(*str)++;
	tok = malloc(sizeof(*tok));
	if (!tok)
	{
		perror(0);
		return (NULL);
	}
	if (**str == '\0')
	{
		tok->type = end;
	}
	else if (strchr(SYMBOLS, **str))
	{
		tok->type = symbol;
		tok->value.c = **str;
		(*str)++;
	}
	else if (isdigit(**str))
	{
		tok->type = value;
		tok->value.v = parse_float(str);
	}
	else
	{
		tok->type = invalid;
		(*str)++;
	}
	return (tok);
}
