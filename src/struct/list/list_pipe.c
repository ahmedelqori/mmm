/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   list_pipe.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:26:35 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/15 10:12:49 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

t_list_pipe	*ft_lstpipe_new(t_tree	*root)
{
	t_list_pipe *lst_pipe;

	lst_pipe = malloc(sizeof(t_list_pipe));
	if (lst_pipe == NULL)
		return (NULL);
	lst_pipe->root = root;
	lst_pipe->next = NULL;
	return (lst_pipe);
}

void	ft_lstpipe_add_back(t_list_pipe **lst, t_list_pipe *new)
{
	t_list_pipe	*head;

	head = *lst;
	if (new == NULL)
		return ;
	if (*lst == NULL)
		*lst = new;
	else
	{
		while (head->next)
			head = head->next;
		head->next = new;
	}
}

void	ft_print_tree(t_tree *root)
{
	if (!root)
		return;
	printf(BOLDGREEN"ROOT: %s\n"RESET,root->command);

	if (root->left)
	{
		printf(BOLDYELLOW"ROOT: %s\t LEFT: %s\n"RESET,root->command , root->left->command);
		ft_print_tree(root->left);
	}
	if (root->right)
	{
		printf(BOLDMAGENTA"ROOT: %s\t RIGHT: %s\n"RESET,root->command , root->right->command);
		ft_print_tree(root->right);
	}
}

void	ft_print_lstpipe(t_list_pipe	*lst)
{
	while(lst)
	{
		ft_print_tree(lst->root);
		printf(BOLDBLUE"\n==========================\n");
		lst = lst->next;
	}
}



t_list_pipe	*ft_create_list(char	**arr)
{
	t_list_pipe	*head;
	t_tree		*root;
	int			i;

	i = 0;
	head = NULL;
	while (arr[i])
	{		
		root = NULL;
		while (arr[i] && arr[i][0] != PIPE)
		{
			ft_tree_insert(&root, ft_tree_new(arr[i]));
			i++;
		}
		ft_lstpipe_add_back(&head,ft_lstpipe_new(root));
		if (arr[i])
			i++;
	}
	return (head);
}