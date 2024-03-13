/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   access.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/31 13:48:08 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:36:24 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	check_file(char *pathname)
{
	if (pathname == NULL)
		return (-1);
	if (access(pathname, F_OK) != 0)
		return (0);
	return (1);
}

int	check_read(char *pathname)
{
	if (pathname == NULL)
		return (-1);
	if (access(pathname, R_OK) != 0)
		return (0);
	return (1);
}

int	check_write(char *pathname)
{
	if (pathname == NULL)
		return (-1);
	if (access(pathname, W_OK) != 0)
		return (0);
	return (1);
}

int	check_execute(char *pathname)
{
	if (pathname == NULL)
		return (-1);
	if (*pathname == '.' || *pathname == '/')
	{
		if (access(pathname, X_OK) == 0)
			return (1);
	}
	return (0);
}
