#include "eval.h"

static void	print_token(t_token *tok)
{
	// printf("%.5s\n%.5s\n%.5s\n", dict_type(tok), dict_category(tok), dict_name(tok));
	printf("\033[1D");
	if (tok->type == value)
	{
		// printf(":%.1g", tok->value.v);
		printf("%2.3g", tok->value.v);
		return ;
	}
	if (tok->type == operation)
	{
		printf("%c", tok->value.c);
		return ;
	}
	//printf("%2.3s", dict_type(tok));
}

static void print_connector(t_pos p, char dir, int depth)
{
	if (dir == 'l')
	{
		while (depth--)
		{
			printf("\033[%d;%dH/", p.y+1, p.x-1);
			p = (t_pos){p.x - 1, p.y + 1};
		}
	}
	else if (dir == 'r')
	{
		while (depth--)
		{
			printf("\033[%d;%dH\\", p.y+1, p.x+1);
			p = (t_pos){p.x + 1, p.y + 1};
		}
	}
}

void	print_tree(t_pos p, t_tree *tree)
{
	t_token *tok;
	int		size;

	tok = tree->tok;
	size = 3;
	if (tok->type == operation)
	{
		printf("\033[%d;%dH", p.y, p.x + 1);
		print_token(tok);

		size = get_tree_max_width(tree);
		// printf("\033[%d;0H", p.y);
		// printf("s:%d", get_tree_max_width(tree));
		if (tree->left != NULL)
		{
			print_connector(p, 'l', size);
			print_tree((t_pos){p.x - size, p.y + size}, tree->left);
		}
		if (tree->right != NULL)
		{
			print_connector(p, 'r', size);
			print_tree((t_pos){p.x + size, p.y + size}, tree->right);
		}
	}
	else if (tok->type == value)
	{
		printf("\033[%d;%dH", p.y, p.x);
		print_token(tok);
	}
}

// wrapper for the print tree that
// calculates very roughly the space it needs
void	auto_print_tree(t_tree *tree)
{
	int	width;
	int	height;

	width = get_tree_max_width(tree) * 6;
	height = get_tree_height(tree) * 4;
	printf("\033[2J\033[1;1H");
	print_tree((t_pos){width, 2}, tree);
	printf("\033[%d;0H", height);
	printf("ans = %g", evaluate(tree));
	printf("\n");
}
