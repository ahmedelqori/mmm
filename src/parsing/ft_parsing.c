/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_parsing.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 13:34:08 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/16 16:00:03 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"



int	ft_is_redirections(char c)
{
	if (c == '|' || c == '<' || c == '>')
		return (1);
	return (0);
}

int	ft_action_1(char *s)
{
	int	i;
	int	single_quotes;
	int	double_quotes;

	single_quotes = 1;
	double_quotes = 1;
	i = 0;
	while (s[i])
	{
		if ((s[i] == ' ' || ft_is_redirections(s[i])) && (single_quotes == -1 || double_quotes == -1))
			s[i] *= -1;
		if (s[i] == '"')
			double_quotes *= -1;
		if (s[i] == '\'')
			single_quotes *= -1;
		i++;
	}
	i = 0;
	while (s[i])
	{
		if (s[i] == OUTPUT ||  s[i] == INPUT)
		{
			i++;
			while (s[i])
			{
				if (s[i] == ' ')
					i++;
				else if ((s[i] == OUTPUT || s[i] == INPUT) && (s[i - 1] == OUTPUT || s[i - 1] != INPUT))
				{
					printf("Error\n");
					return (1);
				}
				else 
					break;
			}
		}
		else
			i++;
	}
	return 0;
}


char	*ft_parsing(char *input)
{
	char	*space_to_pipe;
	char	*space_to_input;
	char	*space_to_ouput;

	if (ft_action_1(input))
		return NULL;
	space_to_pipe =  ft_add_space_to_pipe(input);
	space_to_input = ft_add_space_to_input(space_to_pipe);
	space_to_ouput = ft_add_space_to_output(space_to_input);
	free(space_to_pipe);
	free(space_to_input);
	return (space_to_ouput);
}