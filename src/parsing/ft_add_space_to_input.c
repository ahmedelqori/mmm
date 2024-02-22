/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_add_space_to_input.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/11 14:18:41 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/13 09:44:32 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

int	ft_count_space_input(char *s)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (s[i])
	{
		if (s[i] == INPUT && s[i + 1] && s[i + 1] != 32 && s[i + 1] != INPUT)
			count++;
		if (i != 0 && s[i] == INPUT && s[i - 1] != 32 && s[i - 1] != INPUT)
			count++;
		i++;
	}
	return (count);
}

char	*ft_add_space_to_input(char *s)
{
	int	len;
	int	i;
	int j;
	char *new;

	len = ft_strlen(s) + ft_count_space_input(s);
	new = malloc(sizeof(char) * (len + 1));
	if(new == NULL )
		return (NULL);
	i = 0;
	j = 0;
	int tmp = 0;
	while (s[i])
	{
		if (s[i] != INPUT)
			new[j] = s[i];
		else
		{
			tmp = j;
			if (i != 0 && s[i] == INPUT && s[i - 1] != 32 && s[i - 1] != INPUT)
			{
				new[j] = ' ';
				j++;
				new[j] = s[i];
			}
			if (s[i] == INPUT && s[i + 1] && s[i + 1] != 32 && s[i + 1] != INPUT)
			{
				new[j] = s[i];
				j++;
				new[j] = ' ';
			}
			if (tmp == j)
				new[j] = s[i];
		}
		i++;
		j++;
	}
	new[len] = 0;
	return (new);
}