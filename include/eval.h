#ifndef EVAL_H
# define EVAL_H

# include <stdio.h>
# include <stdlib.h>
# include <ctype.h>
# include <string.h>
# include <math.h>

# define COMPUTE 0
# define PRINT_TREE 1
# define SYMBOLS "-+*/^()"

typedef struct s_pos
{
	int	x;
	int	y;
}	t_pos;

typedef enum e_token_type
{
	open,
	close,
	operation, // only using the below, leaving for compatibility wile working
	value,
	symbol,
	identifier, // not used now for the future when we might have pow, etc
	invalid,
	end
} t_token_type;

typedef double t_value;

// TODO: this will need revising to accept a char *
//        if we want to add pow sqrt etc.
typedef union u_token_value
{
	char		c;
	t_value		v;
} t_token_value;

typedef struct s_token
{
	t_token_type	type;
	t_token_value	value;
}  t_token;

typedef struct s_tree
{
	t_token			*tok;
	struct s_tree	*left;
	struct s_tree	*right;
} t_tree;


// args
int		parse_args(int argc, char **argv, char **expr, int *action);

// cleanup
void	cleanup_tree(t_tree *tree);
void	cleanup_token_list(t_tree *list);

//evaluate.c
t_value	evaluate(t_tree *tree);

//lexer.c
t_token	*scan_token(void);
void	next_token(void);
t_token	*lexer(char **str);

//lexer.c
t_tree	*construct_tok_list(char *str);
t_token	*lexer(char **str);

//parse_float.c
t_value parse_float(char **str);

//parser.c
t_tree	*factory(t_token *t);
t_tree	*create_node(t_token *new_token, t_tree *left, t_tree *right);
int		parse_expression(char **str, t_tree **left_tree);
int		parse_term(char **str, t_tree **left_tree);
int		parse_factor(char **str, t_tree **tree);

//print.c
void	print(t_tree *tree);
void	print_token2(t_token *t);
void	print_token_list(t_tree *t);

// print_tree.c
void	print_tree(t_pos p, t_tree *tree);
void	auto_print_tree(t_tree *tree);

// tree_ops.c
int		get_tree_width(t_tree *tree, int level);
int		get_tree_height(t_tree *tree);
int		get_tree_max_width(t_tree *tree);

#endif
