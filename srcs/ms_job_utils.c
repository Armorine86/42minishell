/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_job_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/08 09:49:51 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/30 15:45:16 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_job	*ms_job_lastnode(t_job *job)
{
	while (job != NULL)
	{
		if (job->next == NULL)
			return (job);
	}
	return (job);
}

void	ms_job_addback(t_job **job, t_job *new)
{
	t_job	*last;

	if (job)
	{
		if (*job)
		{
			last = ms_job_lastnode(*job);
			last->next = new;
		}
		else
			*job = new;
	}
}

t_job	*ms_new_job(void)
{
	t_job	*new;

	new = ft_calloc(1, sizeof(t_job));
	if (!new)
	{
		perror("Minishell:");
		return (NULL);
	}
	new->next = NULL;
	return (new);
}

void	ms_free_value(t_job *current)
{
	if (current->cmd)
		ft_free_tab(current->cmd);
	if (current->redir)
		ft_free_tab(current->redir);
	if (current->hdoc)
	{
		free(current->hdoc);
		current->hdoc = NULL;
	}
}

void	ms_free_job(t_job *job_head)
{	
	t_job	*save;
	int		start;

	start = 0;
	if (!job_head)
		return ;
	while (job_head != NULL)
	{
		save = job_head;
		job_head = job_head->next;
		ms_free_value(save);
		free(save);
		save = NULL;
		start++;
	}
	job_head = NULL;
}
