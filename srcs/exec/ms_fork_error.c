/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_fork_error.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/22 11:29:06 by mafortin          #+#    #+#             */
/*   Updated: 2021/12/01 14:01:17 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_nosuchfile(char *cmd)
{
	ms_return_fd();
	ft_putstr_fd("Minishell: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putendl_fd(": No such file or directory", 1);
	g_ms.exit = 127;
}

void	ms_cmdnotfound(char *cmd)
{
	ms_return_fd();
	ft_putstr_fd("Minishell: ", 1);
	ft_putstr_fd(cmd, 1);
	ft_putendl_fd(": Command not found", 1);
	g_ms.exit = 127;
}

bool	ms_pid_error(void)
{
	ms_return_fd();
	ft_putendl_fd("minishell: FATAL: fork error", 1);
	g_ms.exit = 1;
	return (false);
}
