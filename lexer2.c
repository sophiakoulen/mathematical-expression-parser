#include "eval.h"

/**
 * This will make a new linked list of the found tokens.
 * It will be a doubly linked list that re-uses the t_tree struct
 * with left / right corresponding to the previous / next item in the list.
 */
t_tree	*tokenizer(char *str)
{
	t_tree	*start;
	t_tree	*current;
	t_tree	*tmp;
	t_token	*tok;

	start = NULL;
	while (1)
	{
		tok = lexer2(&str);
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
*/
t_token	*lexer2(char **str)
{
	t_token *tok;

	// printf("tokenizing <%s>\n", *str);
	while (isspace(**str))
		(*str)++;
	tok = (t_token *)malloc(sizeof(t_token));
	if (!tok)
	{
		perror(0);
		return (NULL);
	}
	if (**str == '\0')
	{
		printf("token: end\n");
		tok->type = end;
	}
	else if (strchr(SYMBOLS, **str))
	{
		tok->type = symbol;
		tok->value.c = **str;
		printf("token: %c\n", tok->value.c);
		(*str)++;
	}
	else if (isdigit(**str))
	{
		tok->type = value;
		tok->value.v = parse_float(str);
		printf("token: %f\n", tok->value.v);
	}
	else
		// TODO: here we can add the code to detect multi character word as identifiers
		// either match agaist a dictionary of possibilities, like pi pow sqrt etc..
		// or single letter constants like e or G
		// or record the string to be used as a variable name
		// for now it's just invalid
		// whatever this does, it would need to advance str
	{
		tok->type = invalid;
		printf("token: invalid\n");
		(*str)++;
	}
	return (tok);
}
