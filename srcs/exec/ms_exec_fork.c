/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_fork.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/18 12:44:10 by mafortin          #+#    #+#             */
/*   Updated: 2021/12/01 14:00:21 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	ms_cmdispath(char **cmd, t_job *job_head)
{
	struct stat	info;

	if (stat(cmd[0], &info) == -1)
	{
		perror("Minishell");
		ms_free_fork(job_head);
		exit (126);
	}
	if (S_ISDIR(info.st_mode))
	{
		ft_putstr_fd("Minishell: ", 1);
		ft_putstr_fd(cmd[0], 1);
		ft_putendl_fd(": is a directory", 1);
		ms_free_fork(job_head);
		exit(126);
	}
	execve(cmd[0], cmd, g_ms.env);
	perror("Minishell");
	ms_free_fork(job_head);
	exit(126);
}

void	ms_fork(t_job *current, t_job *job_head)
{
	char	*path;

	path = NULL;
	(void)job_head;
	if (ft_char_search(current->cmd[0], '/') > 0)
		ms_cmdispath(current->cmd, job_head);
	if (ft_strncmp(current->cmd[0], ".\0", 2) == 0)
	{
		printf("Minishell: .: filename argument required\n");
		exit (2);
	}
	path = ms_get_cmdpath(current->cmd[0]);
	if (path)
	{
		if (execve(path, current->cmd, g_ms.env) == -1)
		{
			printf("Minishell: %s: command not found\n", current->cmd[0]);
			g_ms.exit = 127;
		}
		free(path);
	}
	ms_free_fork(job_head);
	exit(g_ms.exit);
}

bool	ms_fork_signal(int status)
{
	if (WIFEXITED(status))
		g_ms.exit = WEXITSTATUS(status);
	if (WIFSIGNALED(status))
	{
		if (WTERMSIG(status) == SIGINT)
			ft_putendl_fd("", 1);
		if (WTERMSIG(status) == SIGQUIT)
			ft_putendl_fd("Kit-Kat", 1);
	}
	ms_setsignals();
	if (g_ms.exit != 0)
		return (false);
	return (true);
}

bool	ms_fork_exit(int status)
{
	ms_fork_signal(status);
	ms_return_fd();
	if (g_ms.exit != 0)
		return (false);
	return (true);
}

bool	ms_exec_fork(t_job *current, t_job *job_head)
{
	pid_t	pid;
	int		status;

	pid = fork();
	signal(SIGINT, ms_donothing);
	signal(SIGQUIT, ms_donothing);
	if (pid == -1)
		return (ms_pid_error());
	if (pid == 0)
		ms_fork(current, job_head);
	waitpid(pid, &status, 0);
	return (ms_fork_exit(status));
}
