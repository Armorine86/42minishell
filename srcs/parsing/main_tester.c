/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main_tester.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mmondell <mmondell@student.42quebec.com    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/05 09:31:21 by mmondell          #+#    #+#             */
/*   Updated: 2021/10/13 15:48:29 by mmondell         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

int	main(void)
{
	t_job	*job;
	char	*input;

	job = NULL;
	job = ms_create_node(job);
	input = " echo blab blabb bla > test ";
	parse_input(input, job);
}
