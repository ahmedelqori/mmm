/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ael-qori <ael-qori@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/15 09:15:15 by ael-qori          #+#    #+#             */
/*   Updated: 2024/02/15 09:15:18 by ael-qori         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void    ft_handle_sigint(int sig)
{
    if (sig != SIGINT)
        return;
    printf("\n");
    rl_replace_line("",0);
    rl_on_new_line();
    rl_redisplay();
}

void    ft_signals(void)
{
    signal(SIGQUIT, SIG_IGN);
    signal(SIGINT, ft_handle_sigint);
}