/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_execute.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 13:14:29 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/22 20:11:19 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"
typedef struct s_l{
	int n;
	struct s_l *next;
}t_l;

t_l *ft_l_new(int n)
{
	t_l *node;

	node = malloc(sizeof(t_l));
	if (node == NULL)
		return (NULL);
	node->n = n;
	node->next = NULL;
	return (node);
}
void	ft_ladd_back(t_l **lst, t_l *new)
{
	t_l	*head;

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
void	tree_help(t_tree *tree, t_list **list, int *output,int *input)
{
	t_tree	*root;
	int fd;

	root = (tree);
	if (!root)
		return;
	if (root->command[0] == OUTPUT || root->command[0] == INPUT)
	{
		if (root->left && root->command[0] == OUTPUT)
		{
			fd = open(root->left->command,O_CREAT|O_WRONLY|O_TRUNC,0777);
			if (fd != -1)
				*output = fd;;
		}
		if (root->left && root->command[0] == INPUT)
		{
			fd = open(root->left->command,O_RDONLY,0777);
			if (fd != -1)
				*input = fd;
		}
	}
	if (root->command[0] != OUTPUT && root->command[0] != INPUT)
	{
		// printf("(%s)\t",root->command);
		ft_lstadd_back(list,ft_lstnew(root->command));
	}
	tree_help(tree->right, list,output, input);
}

void	ft_execute(t_list_pipe *lst , int *fd)
{
	t_tree	*root;
	t_list	*list;
	int input;
	int output;
	int tmp_input;
	int tmp_output;
	// int org = dup(STDOUT_FILENO);

	input = dup(STDIN_FILENO);
	output = dup(STDOUT_FILENO);
	// printf("Before: %d\n",output);
	tmp_input = input;
	tmp_output = output;
	root = lst->root;
	list = NULL;
	tree_help(root, &list, &output,&input);
	t_list *tmp;
	tmp = list;
	int len = 0;
	while (tmp)
	{
		tmp =tmp->next;
		len++;
	}
	char	**arr = malloc((len + 1) * sizeof(char*));
	if (arr == NULL)
		return ;
	int i = 0;
	while (i < len)
	{
		arr[i] = list->content;
		list = list->next;
		i++;
	}
	arr[len] = NULL;
	i = 0;
	
	// int org_input = dup(STDIN_FILENO);
	int pid = fork();
	// int check = 0;
	if (pid == 0)
	{
		close(fd[0]);
		// printf("After %d\n",output);
		// {
		if (lst->next)
			dup2(fd[1],STDOUT_FILENO);
		if (output != tmp_output)
			dup2(output, STDOUT_FILENO);
	
		// }
		execve(ft_strjoin("/bin/", arr[0]), arr, NULL) ;
	}
	waitpid(pid, NULL,0);
	close(fd[1]);
	// dup2(input, STDIN_FILENO);
	// if (lst->next && input == 6)
	// {
	// 	write(1, "HHH\n",4);
	
	if (lst->next)
		dup2(fd[0],STDIN_FILENO);
	if (input != tmp_input)
		dup2(input, STDIN_FILENO);
	// }
}


void handle_multiple_pipe(t_list_pipe *lst) {
	int fd[2];
    int org_stdout = dup(STDOUT_FILENO); 
    int org_stdin = dup(STDIN_FILENO); 
    while (lst) {
		pipe(fd);
    	ft_execute(lst, fd);
        lst = lst->next;
    }
	dup2(org_stdout, STDOUT_FILENO);
	dup2(org_stdin, STDIN_FILENO);
}


// #include "../../includes/minishell.h"
// typedef struct s_l{
// 	int n;
// 	struct s_l *next;
// }t_l;

// t_l *ft_l_new(int n)
// {
// 	t_l *node;

// 	node = malloc(sizeof(t_l));
// 	if (node == NULL)
// 		return (NULL);
// 	node->n = n;
// 	node->next = NULL;
// 	return (node);
// }
// void	ft_ladd_back(t_l **lst, t_l *new)
// {
// 	t_l	*head;

// 	head = *lst;
// 	if (new == NULL)
// 		return ;
// 	if (*lst == NULL)
// 		*lst = new;
// 	else
// 	{
// 		while (head->next)
// 			head = head->next;
// 		head->next = new;
// 	}
// }
// void	tree_help(t_tree *tree, t_list **list, t_l **files,int *input)
// {
// 	t_tree	*root;
// 	int fd;

// 	root = (tree);
// 	if (!root)
// 		return;
// 	if (root->command[0] == OUTPUT || root->command[0] == INPUT)
// 	{
// 		if (root->left && root->command[0] == OUTPUT)
// 		{
// 			fd = open(root->left->command,O_CREAT|O_WRONLY|O_TRUNC,0777);
// 			ft_ladd_back(files, ft_l_new(fd));
// 		}
// 		else if (root->left == NULL && root->command[0] == OUTPUT)
// 		{
// 			fd = 1;
// 			ft_ladd_back(files, ft_l_new(fd));

// 		}
// 		if (root->left && root->command[0] == INPUT)
// 		{
// 			fd = open(root->left->command,O_RDONLY,0777);
// 			if (fd != -1)
// 				*input = fd;
// 		}
// 		else if (root->left == NULL && root->command[0] == INPUT)
// 		{
// 			*input = 0;
// 		}
// 	}
// 	if (root->command[0] != OUTPUT && root->command[0] != INPUT)
// 	{
// 		// printf("(%s)\t",root->command);
// 		ft_lstadd_back(list,ft_lstnew(root->command));
// 	}
// 	tree_help(tree->right, list,files, input);
// }

// void	ft_execute(t_list_pipe *lst)
// {
// 	t_tree	*root;
// 	t_list	*list;
// 	t_l	*files;
// 	int input;
// 	// int output;

// 	input = 0;
// 	list = NULL;
// 	files = NULL;
// 	// int fd[2];
// 	// int org_input = dup(STDIN_FILENO);
// 	// int org = dup(STDOUT_FILENO);
// 	int org = dup(STDOUT_FILENO);
// 	// while (root)
// 	// {
// 	// while (lst)
// 	// {
// 		// pipe(fd);
// 		root = lst->root;
// 		tree_help(root, &list, &files,&input);
// 		// 	root = root->right;
// 		// }
// 		t_list *tmp;
// 		tmp = list;
// 		int len = 0;
// 		while (tmp)
// 		{
// 			// printf("%s\t",(char*)tmp->content);
// 			tmp =tmp->next;
// 			len++;
// 		}
// 		char	**arr = malloc((len + 1) * sizeof(char*));
// 		if (arr == NULL)
// 			return ;
// 		int i = 0;
// 		while (i < len)
// 		{
// 			arr[i] = list->content;
// 			list = list->next;
// 			i++;
// 		}
// 		arr[len] = NULL;
// 		i = 0;
// 		// printf("%d",input);
// 		// int org_input = dup(STDIN_FILENO);
// 		dup2(input, STDIN_FILENO);
// 		// close(fd[0]);
// 		if (!files)
// 		{
// 			int pid = fork();
// 			dup2(org, STDOUT_FILENO);
// 			if (pid == 0)
// 				execve(ft_strjoin("/bin/", arr[0]), arr, NULL);
// 		}
// 		while (files && files->next)
// 			files = files->next;
// 		if (files)
// 		{
// 			int pid = fork();
			
// 			dup2(files->n, STDOUT_FILENO);
// 			// close(fd[1]);
// 			if (pid == 0)
// 				execve(ft_strjoin("/bin/", arr[0]), arr, NULL);
// 		}
// 		wait(NULL);
// 		// lst = lst->next;
// 	// }
// 	// dup2(org, STDOUT_FILENO);
// 	// dup2(org_input, STDIN_FILENO);
// }
