/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   build_job.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/13 14:46:17 by mmondell          #+#    #+#             */
/*   Updated: 2021/10/26 13:03:46 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void	build_redirection(t_token *tok, t_job *job)
{
	int	i;
	int	count;

	i = 0;
	if (tok->type == L_HDOC)
	{
		if (build_heredoc(tok, job) == false)
			return ;
	}
	if (!job->redir)
	{
		count = count_redirections(tok);
		job->redir = (char **)ft_calloc(count + 1, sizeof(char *));
	}
	while (job->redir[i])
		i++;
	job->redir[i] = ft_calloc(ft_strlen(tok->token) + 1, sizeof(char));
	ft_strlcpy(job->redir[i], tok->token, ft_strlen(tok->token) + 1);
	i++;
	tok = tok->next;
	job->redir[i] = ft_calloc(ft_strlen(tok->token) + 1, sizeof(char));
	ft_strlcpy(job->redir[i], tok->token, ft_strlen(tok->token) + 1);
}

void	build_cmd_and_args(t_token *tok, t_job *job)
{
	int	i;
	int	count;

	i = 0;
	if (!job->cmd)
	{
		count = count_cmd_and_args(tok);
		job->cmd = (char **)ft_calloc(count + 1, sizeof(char *));
	}
	while (job->cmd[i])
		i++;
	job->cmd[i] = ft_calloc(ft_strlen(tok->token) + 1, sizeof(char));
	ft_strlcpy(job->cmd[i], tok->token, ft_strlen(tok->token) + 1);
}

t_job	*build_job(t_token *token, t_job *job)
{
	t_job	*job_head;
	t_token	*token_head;

	job = ft_calloc(1, sizeof(t_job));
	job_head = job;
	token_head = token;
	while (token->next != NULL)
	{
		if (token->type == PIPE)
		{
			ms_job_addback(&job, ms_new_job());
			job = job->next;
		}
		else if (token->type == STRING)
			build_cmd_and_args(token, job);
		else if (is_redirection(token))
		{
			build_redirection(token, job);
			token = token->next;
		}
		token = token->next;
	}
	free_list(token_head);
	return (job_head);
}
