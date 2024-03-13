/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 12:47:37 by agranjon          #+#    #+#             */
/*   Updated: 2024/03/11 17:55:51 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	pwd(void)
{
	char	*buff;

	if (g_signal != 0)
		return (return_signals());
	buff = getcwd(NULL, 0);
	if (buff == NULL)
		return (-1);
	if (g_signal != 0)
		return (free(buff), return_signals());
	if (printf("%s", buff) != ft_strlen(buff))
		return (free(buff), -1);
	free(buff);
	if (printf("\n") != 1)
		return (-1);
	return (0);
}
