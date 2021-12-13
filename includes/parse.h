/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: mafortin <mafortin@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2021/10/04 14:05:36 by mmondell          #+#    #+#             */
/*   Updated: 2021/11/30 16:21:10 by mafortin         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSE_H
# define PARSE_H

# define SPACES " \n\t\v\f\r"
# define QUOTES "\"\'"

typedef enum e_state
{
	TEXT,
	D_QUOTE,
	S_QUOTE,
}	t_state;

typedef struct s_parser
{
	char	*input;
	int		index;
	t_state	state;
}	t_parser;

typedef struct s_quote
{
	bool	singlequote;
	bool	doublequote;
}	t_quote;

typedef struct s_dollar
{
	char	*new_string;
	char	*name;
	char	*value;
	int		index;
	int		found;
	t_quote	*state;

}	t_dollar;

typedef struct s_job	t_job;
typedef struct s_quote	t_quote;
int			find_closing_quote(t_parser *par, char quote);
char		*trim_input(char *input);
void		init_parser(t_parser *par, char *input);
bool		validate_tokens_syntax(t_token *head);
t_token		*find_token(t_parser *par, t_token *token);
t_token		*tokenize_string(t_parser *par, t_token *token);
t_token		*tokenize_operator(t_parser *par, t_token *token);
t_token		*add_token_to_list(t_parser *par, t_token *token);
t_job		*parse_input(char *input, t_job *job_head);
t_job		*build_job(t_token *token_head, t_job *job_head);
t_job		*parse_input(char *input, t_job *job_head);
bool		find_dollarsign(t_job *job_head);
void		dollarsign_main(t_job *current);

/* PARSE UTILITIES */

int			token_length(t_parser *par);
char		index_char(t_parser *par);
char		*reset_parser(t_parser *par, char *input);
void		check_state(t_parser *par, int index);
bool		input_is_not_empty(char *input);
void		dollarstruct_init(t_dollar *d_sign);
void		dollarsign_free(t_dollar *d_sign, t_quote *state);
int			count_redirections(t_token *token);
int			count_cmd_and_args(t_token *token);
void		trimquotes_main(t_job *current);
void		update_quotestatus(char type, t_quote *state);
t_job		*dollarsign_redir(t_job *current);
t_dollar	*dollarsign_exit(t_dollar *d_sign);
t_dollar	*dollarsign_join(t_dollar *d_sign);
t_dollar	*dollarsign_name(char *string, t_dollar *d_sign, t_quote *state);
char		*dollarsign_loop(char *string);

/* HEREDOCS */

void		free_all_hdoc(char *input, char *hdoc, t_job *h, t_token *tok);
bool		build_heredoc(t_token *token, t_job *job, t_job *job_head);
bool		create_pipe(int *fd);
bool		invalid_process_id(int pid);
char		*find_delimiter(t_token *token);
char		*join_inputs(char *input, char *heredoc);
void		add_hdoc_job(t_job *job, char *heredoc, int *fd);

#endif
