/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/11 11:36:37 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 17:55:33 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	ft_atoi(char *str)
{
	long	nb;

	if (str == NULL)
		return (-1);
	nb = 0;
	while (*str != '\0')
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	return (nb);
}

int	final_value(char **env)
{
	int		i;
	char	*temp;

	if (env == NULL)
		return (-1);
	i = 0;
	while (env[i] != NULL && ft_strcmp_sep("?", env[i], '=') != 0)
		i++;
	temp = get_var_value(env[i]);
	if (temp == NULL)
		return (-1);
	i = ft_atoi(temp);
	free(temp);
	return (i);
}

int	is_nb(char *str)
{
	if (str == NULL)
		return (-1);
	if (*str == '-')
		str++;
	while (*str != '\0')
	{
		if (*str < '0' || *str > '9')
			return (-1);
		str++;
	}
	return (0);
}

int	is_valid_nb(char *str)
{
	int	nb;

	if (str == NULL || *str == '-')
		return (-1);
	nb = 0;
	while (*str != '\0' && nb <= 255)
	{
		nb *= 10;
		nb += *str - '0';
		str++;
	}
	if (nb > 255)
	{
		write(2, RED"Minishell: exit: value can't be <0 or >255\n"RESET, 54);
		return (-1);
	}
	return (nb);
}

int	ft_exit(char **argv)
{
	int	status;

	if (argv == NULL)
		return (-1);
	if (get_double_tab_size(argv) > 2)
	{
		write(2, RED"Minishell: exit: too many arguments\n"RESET, 47);
		return (1);
	}
	if (argv[1] == NULL)
		return (0);
	if (is_nb(argv[1]) == -1)
	{
		write(2, RED"Minishell: exit: numeric argument required\n"RESET, 54);
		return (2);
	}
	status = is_valid_nb(argv[1]);
	if (g_signal == SIGINT)
		return (130);
	if (g_signal == SIGQUIT)
		return (131);
	if (status == -1)
		return (2);
	return (status);
}
