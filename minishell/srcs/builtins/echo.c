/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 11:06:58 by agranjon          #+#    #+#             */
/*   Updated: 2024/03/11 18:08:43 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	check_has_option_n(char **argv)
{
	int	i;

	i = 1;
	if (!argv)
		return (-1);
	if (ft_strcmp("-n", argv[1]) == 0)
		return (1);
	if (!argv[1] || !argv[1][0] || !argv[1][1])
		return (0);
	while (argv[1][i])
	{
		if (argv[1][0] != '-')
			return (0);
		if (argv[1][i] != 'n')
			return (0);
		i++;
	}
	return (1);
}

int	echo_signals(void)
{
	if (g_signal == SIGINT)
		return (130);
	if (g_signal == SIGQUIT)
		return (131);
	return (0);
}

int	echo(char **argv)
{
	int	i;
	int	option;

	i = 1;
	if (!argv)
		return (-1);
	option = check_has_option_n(argv);
	if (option)
		i = 2;
	if (g_signal != 0)
		return (echo_signals());
	while (argv[i])
	{
		if (g_signal != 0)
			return (echo_signals());
		printf("%s", argv[i]);
		if (argv[i + 1])
			printf(" ");
		i++;
	}
	if (!option)
		printf("\n");
	return (0);
}
