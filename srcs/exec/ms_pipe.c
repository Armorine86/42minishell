/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_pipe.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/21 11:29:54 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/30 15:27:00 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_pipe_dup(t_job *current, t_pipe *data, int index)
{
	if (index > 0)
	{
		if (dup2(data->prev_pipe[0], 0) == -1)
		{
			perror("Minishell:");
			exit (1);
		}
		close(data->prev_pipe[0]);
		close(data->prev_pipe[1]);
	}
	if (current->next)
	{
		if (dup2(data->pipe_fd[1], 1) == -1)
		{
			perror("Minishell:");
			exit (1);
		}
		close(data->pipe_fd[1]);
		close(data->pipe_fd[0]);
	}
}

void	ms_pipe_exec(t_job *current, t_pipe *data, int index, t_job *job_head)
{
	bool	ret;

	ms_pipe_dup(current, data, index);
	free(data);
	ret = ms_exec_prep(current);
	if (ret == true)
	{
		if (ms_check_builtin(current) == false)
			ms_fork(current, job_head);
	}
	ms_free_fork(job_head);
	exit(g_ms.exit);
}

void	ms_pipe_wait(t_job *job_head, t_pipe *data)
{
	t_job	*current;
	int		index;

	current = job_head;
	(void)job_head;
	index = 0;
	while (index <= data->nb_pipe)
	{
		waitpid(current->pid, &(current->status), 0);
		if (current->next)
			current = current->next;
		index++;
	}
	ms_fork_signal(current->status);
}

void	ms_pipe_loop(t_job *current, t_job *job_head, t_pipe *data)
{
	int		index;

	index = 0;
	(void)job_head;
	while (index <= data->nb_pipe)
	{
		if (index < data->nb_pipe)
		{
			if (pipe(data->pipe_fd) == -1)
				return (perror("Minishell Pipe:"));
		}
		current->pid = fork();
		if (invalid_process_id(current->pid))
			return ;
		if (!current->pid)
			ms_pipe_exec(current, data, index, job_head);
		if (index > 0)
			ms_close_pipe(data->prev_pipe);
		if (current->next == NULL)
			break ;
		current = current->next;
		ms_pipe_save(data);
		index++;
	}
	ms_pipe_wait(job_head, data);
}

bool	ms_pipe_main(t_job *job_head)
{
	t_job	*current;
	t_pipe	*data;

	data = malloc(sizeof(t_pipe));
	current = job_head;
	data->nb_pipe = ms_pipe_number(current);
	signal(SIGINT, ms_donothing);
	signal(SIGQUIT, ms_donothing);
	ms_pipe_loop(current, job_head, data);
	free(data);
	data = NULL;
	return (true);
}
