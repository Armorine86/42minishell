/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ms_exec_fork_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/20 11:24:55 by mafortin          #+#    #+#             */
/*   Updated: 2021/12/01 14:02:15 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

char	*ms_find_cmdpath(char *cmd_name, char **paths)
{
	int		index;
	char	*cmd_path;

	index = 0;
	while (paths[index])
	{
		cmd_path = ft_strjoin(paths[index], cmd_name);
		if (!cmd_path)
			perror("Minishell");
		if (access(cmd_path, F_OK) == 0)
		{
			free (cmd_name);
			ft_free_tab(paths);
			return (cmd_path);
		}
		free(cmd_path);
		index++;
	}
	ms_cmdnotfound(cmd_name + 1);
	free(cmd_name);
	ft_free_tab(paths);
	return (NULL);
}

char	*ms_get_cmdpath(char *cmd)
{
	char	**paths;
	char	*cmd_name;

	cmd_name = ft_strjoin("/", cmd);
	paths = ms_create_paths();
	if (!paths)
	{
		ms_nosuchfile(cmd);
		free(cmd_name);
		free(paths);
		return (NULL);
	}
	return (ms_find_cmdpath(cmd_name, paths));
}

char	*ms_join_currentdir(char *cmd)
{
	char	*pwd;
	char	*join;
	int		i;

	i = 0;
	pwd = NULL;
	pwd = getcwd(pwd, 0);
	while (cmd[i])
	{
		if (cmd[i] == '/')
		{
			break ;
		}
		i++;
	}
	join = ft_strjoin(pwd, cmd + i);
	return (join);
}

char	**ms_create_paths(void)
{
	int		index;
	bool	found;

	index = 0;
	(void)found;
	found = false;
	while (g_ms.env[index])
	{
		if (ft_strncmp("PATH=", g_ms.env[index], 5) == 0)
		{
			found = true;
			return (ft_split(g_ms.env[index] + 5, ':'));
		}
		index ++;
	}
	return (NULL);
}
