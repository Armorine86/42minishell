/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/21 18:25:12 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/30 15:48:37 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

t_exec	g_ms = {0};

void	print_header(void)
{
	ft_putstr("\e[96m  _________________\e[92m____________________\n");
	ft_putstr("\e[92m/  __  __ _       _\e[96m     _          _ _  \\ \n");
	ft_putstr("\e[92m| |  \\/  (_)_ __ (_)\e[96m___| |__   ___| | | |\n");
	ft_putstr("\e[92m| | |\\/| | | '_ \\| \e[96m/ __| '_ \\ / _ \\ | | | \n");
	ft_putstr("\e[92m| | |  | | | | | | \e[96m\\__ \\ | | |  __/ | | |\n");
	ft_putstr("\e[92m| |_|  |_|_|_| |_|_|\e[96m___/_| |_|\\___|_|_| |\n");
	ft_putstr("\e[96m\\ _________________\e[92m____________________ /\e[0m\n");
	ft_putstr("______________________________________________\n");
	ft_putstr("Created by: Marc-Andre Fortin & Maxime Mondello\n");
	ft_putstr("Version: 1.2\n");
	ft_putstr("______________________________________________");
	ft_putstr("\n\n\n");
}

bool	ms_empty_input(char *input)
{
	char	*trim;

	trim = ft_trim_string(input, ' ');
	if (trim[0] == '\0')
	{
		free (trim);
		return (true);
	}
	free (trim);
	return (false);
}

//*loop de readline qui envoie les infos au parsing et qui execute 
//*le retour du parsing.
void	ms_readline_loop(t_job *job_head)
{
	char	*input;

	ms_setsignals();
	while (true)
	{
		input = readline(PROMPT);
		if (!input)
		{
			ft_putendl_fd("Exit", 2);
			ft_free_tab(g_ms.env);
			ft_free_tab(g_ms.export);
			exit(g_ms.exit);
		}
		if (ms_empty_input(input) == true)
		{
			free(input);
			continue ;
		}
		add_history(input);
		job_head = parse_input(input, job_head);
		free(input);
		if (job_head)
			ms_exec_main(job_head);
		ms_free_job(job_head);
	}
}

char	**ms_export_cpy(char **env)
{
	int		x;
	int		i;
	int		len;
	char	**export;

	x = 0;
	i = 0;
	len = ft_matrice_size(env);
	if (len == 0)
		len = 1;
	export = ft_calloc(len + 1, sizeof(char *));
	while (env[x])
	{
		if (ft_strncmp(env[x], "_=", 2) != 0)
		{
			export[i] = ft_strdup(env[x]);
			i++;
		}
		x++;
	}
	return (export);
}

int	main(int argc, char **argv, char **envp)
{
	t_job		*job_head;
	char		**sorted_env;

	job_head = NULL;
	(void)argv;
	if (argc > 1)
	{
		ft_putstr_fd("Error\nminishell: invalid number of arguments\n", 1);
		exit(-1);
	}
	g_ms.env = ft_matrice_cpy(envp);
	sorted_env = ft_sort_strtab(g_ms.env);
	g_ms.export = ms_export_cpy(sorted_env);
	ft_free_tab(sorted_env);
	print_header();
	ms_saved_fd();
	ms_readline_loop(job_head);
	ft_free_tab(g_ms.env);
	ft_free_tab(g_ms.export);
}
