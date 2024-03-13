/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranjon <agranjon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:21:06 by agranjon          #+#    #+#             */
/*   Updated: 2024/03/13 09:13:53 by agranjon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

void	ft_error_cd(char *func_name, char *path)
{
	char	*message;

	if (func_name && path)
	{
		write(2, RED"Minishell: ", 18);
		message = ft_strjoin(func_name, path);
		perror(message);
		write(2, RESET, 4);
	}
}

char	*ft_get_var_home(char **my_env)
{
	int		i;
	char	*home_path;

	if (my_env == NULL)
		return (NULL);
	i = 0;
	while (my_env[i] != NULL)
	{
		if (ft_strcmp_sep("HOME", my_env[i], '=') == 0)
		{
			home_path = get_var_value(my_env[i]);
			return (home_path);
		}
		i++;
	}
	return (NULL);
}

int	ft_go_to_home(char **my_env)
{
	char	*new_path;

	if (!my_env)
		return (-1);
	new_path = ft_get_var_home(my_env);
	if (!new_path)
	{
		write(2, RED"Minishell: cd: HOME not set\n"RESET, 39);
		return (-1);
	}
	if (access(new_path, R_OK) != 0)
		return (free(new_path), ft_error_cd("cd: ", new_path), -1);
	if (chdir(new_path) != 0)
		return (free(new_path), -1);
	free(new_path);
	return (0);
}

int	change_var_pwd(char **my_env, char *new_pwd)
{
	int		i;
	char	*tmp;

	if (!my_env || !new_pwd)
		return (-1);
	i = 0;
	while (my_env[i] && ft_strcmp_sep("PWD", my_env[i], '=') != 0)
		i++;
	tmp = my_env[i];
	my_env[i] = ft_strjoin("PWD=", new_pwd);
	free(tmp);
	return (0);
}

int	cd(char **argv, char **my_env)
{
	if (!argv || !my_env)
		return (-1);
	if (g_signal != 0)
		return (return_signals());
	if (get_double_tab_size(argv) > 2)
	{
		write(2, RED"Minishell: cd: too many arguments\n"RESET, 45);
		return (1);
	}
	if (!argv[1] || ft_strlen(argv[1]) <= 0)
	{
		if (ft_go_to_home(my_env) != 0)
			return (1);
	}
	else
	{
		if (access(argv[1], R_OK) != 0)
			return (ft_error_cd("cd: ", argv[1]), 1);
		if (chdir(argv[1]) != 0)
		{
			ft_error_cd("cd: ", argv[1]);
			return (1);
		}
		change_var_pwd(my_env, argv[1]);
	}
	return (0);
}
