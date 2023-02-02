#include "eval.h"

int	get_tree_width(t_tree *tree, int level)
{
	if (tree == NULL)
		return (0);
	if (level == 1)
		return (1);
	if (level > 1)
		return (get_tree_width(tree->left, level - 1)
				+ get_tree_width(tree->right, level - 1));
	return (0);
}

int	get_tree_height(t_tree *tree)
{
	int	l_height;
	int	r_height;

	if (tree == NULL)
		return (0);
	l_height = get_tree_height(tree->left);
	r_height = get_tree_height(tree->right);
	if (l_height > r_height)
		return (l_height + 1);
	return (r_height + 1);
}

int	get_tree_max_width(t_tree *tree)
{
	int	maxwidth;
	int	width;
	int	h;
	int	i;

	maxwidth = 0;
	i = 0;
	h = get_tree_height(tree);
	while (i++ < h)
	{
		width = get_tree_width(tree, i);
		if (width > maxwidth)
			maxwidth = width;
	}
	return (maxwidth);
}
