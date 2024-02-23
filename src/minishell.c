/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:10:17 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/22 21:32:56 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	fix_input_arr(char **arr)
{
	int i;
	int j;

	i = 0;
	while (arr[i])
	{
		j = 0;
		while (arr[i][j])
		{
			if (arr[i][j] < 0)
				arr[i][j] *= -1;
			j++;
		}
		i++;
	}
}

void	ft_print_arr(char **arr)
{
	int i;

	i = 0;
	while (arr[i])
	{
		printf("%s\t",arr[i]);
		i++;
	}	
	printf("\n");
}

void	minishell(t_env *env)
{
	char	**arr;
	char	*input;
	char	*prompt;
	char	*fixed_input;
	t_list_pipe	*lst;
	// int org_input = dup(STDIN_FILENO);
	// int org = dup(STDOUT_FILENO);

	lst = NULL;
	while (1)
	{
		ft_signals();
		prompt = ft_prompt(env);
		input = readline(prompt);
		if (input == NULL)
			exit(1);
		add_history(input);
		fixed_input = ft_parsing(input);
		if (fixed_input == NULL)
			continue;
		arr = ft_split(fixed_input, ' ');
		fix_input_arr(arr);
		// ft_print_arr(arr);
		lst = ft_create_list(arr);
		// ft_execute(lst);
		handle_multiple_pipe(lst);
		// ft_print_lstpipe(lst);
		// dup2(org, STDOUT_FILENO);
		// dup2(org_input, STDIN_FILENO);
		(void)lst;
	}
}

int main(int ac, char **av, char **env_arr)
{
	t_env *env;

	(void)ac;
	(void)av;
	env = ft_env(env_arr);
	minishell(env);
}