/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/20 17:58:17 by aherve            #+#    #+#             */
/*   Updated: 2024/03/07 17:05:34 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

char	*test_command_path(char *command, char *var_value)
{
	char	*command_path;
	char	*test_path;
	int		status;

	if (command == NULL || var_value == NULL)
		return (NULL);
	test_path = ft_strndup(var_value, path_len(var_value));
	if (test_path == NULL)
		return (NULL);
	command_path = ft_pathjoin(test_path, command);
	if (command_path == NULL)
		return (free(test_path), NULL);
	status = check_execute(command_path);
	if (status != 1)
		return (free(test_path), free(command_path), NULL);
	free(test_path);
	return (command_path);
}

char	*get_command_path(char *command, char *var_value)
{
	char	*command_path;
	int		len;

	if (command == NULL || var_value == NULL)
		return (NULL);
	while (*var_value != '\0')
	{
		len = path_len(var_value);
		command_path = test_command_path(command, var_value);
		if (command_path != NULL)
			break ;
		var_value += len;
		if (*var_value == ':')
			var_value++;
	}
	return (command_path);
}

char	*find_path_command(char *command, char **envp)
{
	char	*path;
	int		index;
	char	*var_value;

	if (command == NULL || envp == NULL)
		return (NULL);
	index = path_index(envp);
	if (index == -1)
		return (NULL);
	var_value = get_var_value(envp[index]);
	if (var_value == NULL)
		return (NULL);
	path = get_command_path(command, var_value);
	free(var_value);
	if (path == NULL)
		return (NULL);
	return (path);
}
