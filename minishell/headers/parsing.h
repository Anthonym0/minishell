/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/01 13:46:15 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:33:15 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PARSING_H
# define PARSING_H

typedef struct s_token
{
	char			*str;
	int				len;
	struct s_token	*next;
}	t_token;

typedef struct s_cmd
{
	char			*command;
	t_token			*tokens;
	char			**args;
	char			***env;
	t_token			*fdout;
	char			*fdin;
	struct s_cmd	*pipe;
}	t_cmd;

//token_utils.c
void	free_tokens(t_token *token);
t_token	*token_addback(t_token *first, t_token *cur);
t_token	*last_token(t_token *token);
t_token	*new_token(char *str, int len);

//token.c
int		quotes_open(char *input);
t_token	*create_token_list(char *input);

//env_var_expansion_utils.c
int		var_len(char *str);
char	*get_var_value(char *env_var);

//env_var_expansion.c
int		expand_env_vars(t_token *list, char **envp);

//cmd_utils.c
void	free_cmds(t_cmd *cmds);
t_cmd	*new_cmd(void);
t_cmd	*last_cmd(t_cmd *cmd);
t_cmd	*cmd_addback(t_cmd *first, t_cmd *cmd);

//cmds.c
t_cmd	*create_cmd_struct(t_token *list);

//check_redirection_utils.c
int		is_next_valid(char *str);
int		is_valid_redirection(char *str);
int		is_redirection(char *str);

//check_redirection.c
int		handle_redirection_tokens(t_token *list);

//trim_quotes.c
int		has_quotes(char *str);
char	*trim_quotes(char *str, int len);

//check_pipes.c
int		is_pipe(char *str);
int		are_valid_pipes(t_token *list);

//fill_commands_utils.c
void	err_msg_input_redir_no_file(char *file_name);
void	err_msg_input_redir_permission(char *file_name);

//fill_commands.c
int		output_redirection(t_token *token, t_cmd *cmds);
int		is_in_redirection(char *str);
int		input_redirection(t_token *token, t_cmd *cmds);
int		fill_tokens(t_token *token, t_cmd *cmds);
int		fill_command(t_token *token, t_cmd *cmds);

//here_doc_utils.c
void	sigint_catched(int sig);
void	err_msg_heredoc(char *text);
char	*get_delimiter(char *str);
int		integer_length(int nb);
char	*create_file_name(int nb);

//here_doc.c
char	*here_doc(char *str);
int		heredoc_redirection(t_token *token, t_cmd *cmds);

//args.c
int		convert_tokens_in_args(t_cmd *cmds);

//parsing.c
void	err_msg_parsing(char *text);
t_cmd	*parsing(char *line, char **envp);

#endif