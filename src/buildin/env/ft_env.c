/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_env.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:12:09 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/15 09:12:31 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../../includes/minishell.h"

void    ft_print_env(t_env *env)
{
    while(env)
    {
        printf("%s=%s\n",env->key,env->value);
        env = env->next;
    }
}

t_env *ft_env(char **env_list)
{
    t_env *env;
    t_env *node;
    char    *key;
    char    *value;
    int i;

    i = 0;
    env = NULL;
    if (!env_list)
        return (NULL);
    while (env_list[i])
    {
        key = ft_getkey_env(env_list[i]);
        value = ft_getvalue_env(env_list[i]);
        node = ft_lst_new_env(key, value);
        ft_lst_env_addback(&env, node);
        i++;
    }
    return (env);
}