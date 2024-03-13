/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:19:10 by agranjon          #+#    #+#             */
/*   Updated: 2024/03/11 18:13:09 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BUILTINS_H
# define BUILTINS_H

//cd.c
int		cd(char **argv, char **my_env);

//env.c
int		env(char **env);

//echo.c
int		echo(char **argv);

//exit.c
int		final_value(char **env);
int		ft_exit(char **argv);

//export.c
int		export(char **vars, char ***my_env);

//export_utils.c
void	ft_error_export(char *identifier);
int		check_var_exist_and_replace(char **my_env, char *line);
int		ft_valid_first_letter(char c);
int		ft_valid_name_char(char c);
int		check_var_rules(char *var, int mode);

//pwd.c
int		pwd(void);

//unset.c
int		unset(char **argv, char ***my_env);

#endif