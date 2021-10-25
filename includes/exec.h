/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/09/29 16:58:58 by mafortin          #+#    #+#             */
/*   Updated: 2021/10/25 17:20:49 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXEC_H
# define EXEC_H

typedef struct s_pipes
{
	int	**fd_pipe;
	int	status;
}	t_pipes;

typedef struct s_job	t_job;
//BUILTIN
int		ms_pwd_main(int fd);
int		ms_cd_main(char **cmd);
int		ms_echo_main(char **args, int fd);
int		ms_env_main(char **args, int fd);
void	ms_exec_error(char *value, char *cmd_name, char *error_str);
void	ms_print_exec_error(char *value, char *cmd_name, char *error_str);
int		ms_export_main(char **args);
int		ms_unset_main(char **args);
void	ms_exec_main(t_job *job_head);
int		ms_exit_main(t_job *current);
bool	ms_check_builtin(t_job *current);
//EXECVE
bool	ms_exec_prep(t_job *current);
char	*ms_findpath(char *cmd);
bool	ms_pathname_error(char *cmd_name);
char	*ms_get_cmdpath(char *cmd);
char	**ms_create_paths(void);
void	ms_cmdnotfound(char *cmd);
void	ms_nosuchfile(char *cmd);
bool	ms_exec_fork(t_job *current);
void	ms_fork(char **cmd);
bool	ms_pid_error(void);
bool	ms_fork_exit(int status);
//REDIRECTIONS
void	ms_return_fd(void);
bool	ms_redirection_main(t_job *current);
void	ms_saved_fd(void);
//PIPES
bool	ms_pipe_signal(int	status);
int		ms_pipe_number(t_job *job_head);
bool	ms_pipe_main(t_job *job_head);

#endif