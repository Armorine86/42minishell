/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_lst_utils.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/01 21:59:24 by mmondell          #+#    #+#             */
/*   Updated: 2021/10/14 08:17:21 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

void free_list(t_token *head)
{
   t_token	*tmp;

   while (head)
    {
       tmp = head;
       head = head->next;
	   free(tmp->valid_token);
       free(tmp);
    }
}

t_token	*token_lst_last(t_token *token)
{
	while (token)
	{
		if (token->next == NULL)
			return (token);
		token = token->next;
	}
	return (token);
}

void	token_lst_addback(t_token **token, t_token *new)
{
	t_token	*last;

	if (token)
	{
		if (*token)
		{
			last = token_lst_last(*token);
			last->next = new;
			new->prev = last;
		}
		else
			*token = new;
	}
}

t_token	*token_lst_addnew(void	*valid_token)
{
	t_token	*new;

	new = ft_calloc(1, sizeof(t_token));
	if (!new)
		return (NULL);
	new->valid_token = valid_token;
	new->type = EMPTY;
	new->prev = NULL;
	new->next = NULL;
	return (new);
}
