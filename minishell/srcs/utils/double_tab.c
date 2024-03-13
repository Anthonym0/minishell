/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   double_tab.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:15:26 by aherve            #+#    #+#             */
/*   Updated: 2024/03/08 15:02:41 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	get_double_tab_size(char **tab)
{
	int	i;

	i = 0;
	if (tab == NULL)
		return (-1);
	while (tab[i])
		i++;
	return (i);
}

int	ft_free_tab(char **tab)
{
	int	i;

	i = 0;
	if (!tab)
		return (-1);
	while (tab[i])
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (0);
}

int	ft_reverse_free_tab(char **tab, int index)
{
	if (!tab)
		return (-1);
	while (index >= 0)
	{
		free(tab[index]);
		index--;
	}
	free(tab);
	return (0);
}
