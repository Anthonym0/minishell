/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/12 12:56:54 by agranjon          #+#    #+#             */
/*   Updated: 2024/03/11 18:05:49 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

void	ft_error_export(char *identifier)
{
	if (identifier == NULL)
		return ;
	write(2, RED"Minishell: export: `", 27);
	write(2, identifier, ft_strlen(identifier));
	write(2, "': not a valid identifier\n"RESET, 30);
}

int	check_var_exist_and_replace(char **my_env, char *line)
{
	int		i;
	char	*tmp;

	i = 0;
	if (!my_env || !line)
		return (-1);
	while (my_env[i])
	{
		if (ft_strcmp_sep(my_env[i], line, '=') == 0)
		{
			tmp = my_env[i];
			my_env[i] = ft_strdup(line);
			return (free(tmp), 1);
		}
		i++;
	}
	return (0);
}

int	ft_valid_first_letter(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '_')
		return (1);
	return (0);
}

int	ft_valid_name_char(char c)
{
	if (c >= 'a' && c <= 'z')
		return (1);
	if (c >= 'A' && c <= 'Z')
		return (1);
	if (c == '_')
		return (1);
	if (c >= '0' && c <= '9')
		return (1);
	return (0);
}

int	check_var_rules(char *var, int mode)
{
	int		i;

	i = 1;
	if (!var)
		return (-1);
	if (ft_valid_first_letter(var[0]) < 1)
	{
		if (mode == 0)
			ft_error_export(var);
		return (0);
	}
	while (var[i] != '\0' && var[i] != '=')
	{
		if (ft_valid_name_char(var[i]) < 1)
		{
			if (mode == 0)
				ft_error_export(var);
			return (0);
		}
		i++;
	}
	return (1);
}
