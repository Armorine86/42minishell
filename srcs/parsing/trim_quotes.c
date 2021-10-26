/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/14 10:43:19 by mafortin          #+#    #+#             */
/*   Updated: 2021/10/26 09:42:24 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	update_quotestatus(char type, t_quote *state)
{
	if (type == '\"')
	{
		if (state->doublequote == false && state->singlequote == false)
		{
			state->doublequote = true;
			return ;
		}
		if (state->doublequote == true && state->singlequote == false)
			state->doublequote = false;
	}
	if (type == '\'')
	{
		if (state->singlequote == false && state->doublequote == false)
		{
			state->singlequote = true;
			return ;
		}
		if (state->singlequote == true && state->doublequote == false)
			state->singlequote = false;
	}
}

char	*swap_trimmed(char *string, char *trimmed)
{
	free (string);
	string = NULL;
	if (!trimmed)
		string = ft_strdup("\0");
	else
	{
		string = ft_strdup(trimmed);
		free (trimmed);
	}
	return (string);
}

char	*append_trimmed(char string, char *trimmed)
{
	char	*temp;

	temp = ft_append_string(trimmed, string);
	trimmed = ft_strdup(temp);
	free(temp);
	temp = NULL;
	return (trimmed);
}

char	*trimquotes_loop(char *string)
{
	char	*trimmed;
	t_quote	*state;
	int		index;

	state = malloc(sizeof(t_quote));
	index = 0;
	trimmed = NULL;
	state->doublequote = false;
	state->singlequote = false;
	while (string[index])
	{
		if ((string[index] == '\'' && state->doublequote == false)
			|| (string[index] == '\"' && state->singlequote == false))
			update_quotestatus(string[index], state);
		else
			trimmed = append_trimmed(string[index], trimmed);
		index++;
	}
	string = swap_trimmed(string, trimmed);
	free(state);
	return (string);
}

void	trimquotes_main(t_job *current)
{
	int	index;

	index = 0;
	while (current->cmd[index])
	{
		if (current->cmd[index][0])
			current->cmd[index] = trimquotes_loop(current->cmd[index]);
		index++;
	}
	index = 0;
	if (current->redir)
	{
		while (current->redir[index])
		{
			index++;
			if (current->redir[index][0])
				current->redir[index] = trimquotes_loop(current->redir[index]);
			if (!current->redir[index + 1])
				break ;
			index += 2;
		}
	}
}
