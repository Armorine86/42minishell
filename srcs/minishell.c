/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: hpst <hpst@student.42.fr>                  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:25:12 by mafortin          #+#    #+#             */
/*   Updated: 2021/10/01 15:55:59 by hpst             ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

//loop de readline qui envoie les infos au parsing. FONCTIONNE
void	ms_readline_loop(char **envp_ms)
{
	char	*input;
	char	**job;


	signal(SIGINT, ms_nl_signal);
	signal(SIGQUIT, SIG_IGN);
	while (true)
	{
		input = readline("MiniShell % ");
		job = ft_split(input, ' ');
		ms_export_main(envp_ms, job, 1);
		//parse_input(input);
		//ms_exec_main(t_job *job_head, char **envp_ms);
		free (input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	**envp_ms;
	//t_job	*job_head;//structure-linkedlist peupler par le parsing et utliser pour l'execution
	//cree et placer ici une fonction pour bien init la linked list (EXEC OU PARSING)

	if (argc > 1)
	{
		ft_putstr_fd("Error\nminishell: invalid number of arguments\n", 1);
		exit(-1);
	}
	argv++;
	envp_ms = ft_matrice_cpy(envp);
	ms_readline_loop(envp_ms);
	ft_free_tab(envp_ms);
}
