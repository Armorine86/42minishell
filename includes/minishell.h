/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/17 15:01:34 by mafortin          #+#    #+#             */
/*   Updated: 2021/11/30 15:34:57 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <stdio.h>
# include <unistd.h>
# include <signal.h>
# include <stdlib.h>
# include <limits.h>
# include <dirent.h>
# include <stdbool.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <sys/errno.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include "../libft/libft.h"
# include "token.h"
# include "parse.h"
# include "exec.h"
# include "shell_errors.h"
# define PROMPT "\001\e[32m\002Mini\001\e[36m\002Shell \001\e[0m\002% "

typedef struct s_redir
{
	t_type	type;
	char	*file;
}	t_redir;

// linkedlist peupler par le parsing et utiliser par l'execution. 
// les nodes doivent etre free apres l'exec
typedef struct s_job
{
	char			**cmd;
	char			**redir;
	char			*hdoc;
	int				hdoc_fd[2];
	pid_t			pid;
	int				status;
	char			*input;
	struct s_job	*next;
}			t_job;

typedef struct s_exec
{
	char				**env;
	char				**export;
	int					save_in;
	int					save_out;
	unsigned int		exit;
}			t_exec;

extern t_exec	g_ms;
//SIGNALS
bool	ms_fork_signal(int status);
void	ms_nl_signal(int signal);
void	ms_donothing(int signal);
void	ms_setsignals(void);
//ENV
char	*ms_getenv(char *name, char **envp_ms);
char	**ms_setenv(char *name, char *value, char **envp_ms);
char	**ms_set_noequal(char *name, char **export_ms);
//LINKED LIST JOB
void	ms_free_job(t_job *job_head);
t_job	*init_node(t_job *node);
t_job	*ms_new_job(void);
void	ms_job_addback(t_job **job, t_job *new);
void	ms_initjob(t_job *node);

#endif
