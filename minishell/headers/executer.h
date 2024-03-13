/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   executer.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:50:05 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 12:21:15 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef EXECUTER_H
# define EXECUTER_H

# include "parsing.h"

typedef struct s_garbage
{
	t_cmd	*cmds;
	char	*buffer;
	char	***env;
}	t_garb;

//builtin.c
int		built_in(t_cmd *cmds, int pipes[2][2], int status, t_garb *g);
int		first_builtin(t_cmd *cmds, char ***envp, int *stdfds, t_garb *g);

//execute_utils.c
int		close_pipes(int *pipes);
int		is_builtin(char *command);
int		return_status(int pid);
void	free_garbage(t_garb *garbage);

//execute.c
int		set_next_command(t_cmd *cmds, int pipes[2][2], int *stdfds, t_garb *g);
int		first_command(t_cmd *cmds, char ***envp, t_garb *g);

//fds.c
int		manage_fds(t_cmd *cmds, int pipes[2][2]);
int		first_fds(t_cmd *cmds, int *pipes);
int		close_fds(void);
int		init_stdfds(int *stdfds);
int		reinstate_stdfds(int *stdfds);

//launcher.c
int		exec(t_cmd *cmds, int pipes[2][2], t_garb *g);
int		first_exec(t_cmd *cmds, char ***envp, int *stdfds, t_garb *g);

//redirections_utils.c
void	err_msg_output_redir_permission(char *file_name);
void	err_msg_file_creation(char *file_name);
void	err_msg_input_redir_exec_no_file(char *file_name);
void	err_msg_input_redir_exec_permission(char *file_name);

//redirections.c
int		output_redirect(t_token *fdout);
int		input_redirect(char *fdin);

//path_utils.c
int		path_index(char **envp);
int		path_len(char *var_value);
char	*ft_pathjoin(char *path, char *command);

//path.c
char	*find_path_command(char *command, char **envp);

#endif