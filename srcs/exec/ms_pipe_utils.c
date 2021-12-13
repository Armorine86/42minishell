/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 14:30:23 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/30 15:30:31 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

bool	ms_pipe_signal(int status)
{
	if (WIFEXITED(status))
		g_ms.exit = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
		{
			ft_putendl_fd("", 1);
			return (false);
		}
		if (WTERMSIG(status) == SIGQUIT)
			return (false);
	}
	return (true);
}

int	ms_pipe_number(t_job *job_head)
{
	int		nb;
	t_job	*node;

	nb = 0;
	node = job_head;
	if (!node->next)
		return (0);
	while (node->next)
	{
		nb++;
		node = node->next;
	}
	return (nb);
}

void	ms_free_fork(t_job *current)
{
	ft_free_tab(g_ms.env);
	ft_free_tab(g_ms.export);
	ms_free_job(current);
}

void	ms_pipe_save(t_pipe *data)
{
	data->prev_pipe[0] = data->pipe_fd[0];
	data->prev_pipe[1] = data->pipe_fd[1];
}

void	ms_close_pipe(int pipe_fd[2])
{
	close(pipe_fd[0]);
	close(pipe_fd[1]);
}
