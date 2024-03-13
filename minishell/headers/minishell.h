/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 09:58:10 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:21:20 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

//standard libraries
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdlib.h>
# include <unistd.h>
# include <sys/types.h>
# include <sys/wait.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <signal.h>
# include <errno.h>
# include <limits.h>

//project's librairies
# include "prompt.h"
# include "parsing.h"
# include "executer.h"
# include "builtins.h"
# include "pwd.h"
# include "utils.h"

//colors
# define HIGH_GREEN "\e[1;92m"
# define HIGH_GREEN_BCKGRND "\e[1;30;102m"
# define RED "\e[0;31m"
# define WHITE "\e[0;37m"
# define RESET "\e[0m"

//ft_signals.c
void	init_signals(void);
void	change_sigint(char **env);
void	sigint_received(int sig);
int		return_signals(void);

//return_status.c
int		nb_len(int status);
char	*create_new_return_var(int status);
int		change_return_status(char **env, int status);

//minishell_utils.c
t_garb	*create_garbage(t_cmd *cmds, char *buff, char ***env);
void	delete_tmp_files(t_cmd *cmds);
void	err_msg_banner(void);
int		print_banner(void);

//copy_env.c
void	err_msg_env(void);
char	**copy_environnement(char **envp);

#endif