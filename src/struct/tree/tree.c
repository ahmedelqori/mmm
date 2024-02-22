/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   tree.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:28:47 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/16 15:13:39 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_tree	*ft_tree_new(char	*command)
{
	t_tree	*root;

	root = malloc(sizeof(t_tree));
	if (root == NULL)
		return (NULL);
	root->command = ft_strdup(command);
	root->left = NULL;
	root->right = NULL;
	return (root);
}

void	ft_tree_insert(t_tree **root, t_tree *new)
{
	// char	*tmp;

	if (new == NULL)
		return;
	if (*root == NULL)
		*root = new;
	else if (((*root)->command[0] == OUTPUT || (*root)->command[0] == INPUT) && (*root)->left == NULL &&
		(new->command[0] == INPUT || new->command[0] == OUTPUT) 
	)
		return;
	else if (((*root)->command[0] == OUTPUT || (*root)->command[0] == INPUT ) && (*root)->left == NULL )
		(*root)->left = new;
	else if ((*root)->right == NULL)
		(*root)->right = new;
	else	
		ft_tree_insert(&(*root)->right, new);
}