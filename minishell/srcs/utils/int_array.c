/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   int_array.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 12:25:24 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:36:36 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	sum_int_array(int *tab, int len)
{
	int	i;
	int	sum;

	if (tab == NULL || len <= 0)
		return (-1);
	i = 0;
	sum = 0;
	while (i < len)
	{
		sum += tab[i];
		i++;
	}
	return (sum);
}

int	*create_and_init_tab(int len)
{
	int	*tab;
	int	i;

	if (len <= 0)
		return (NULL);
	tab = malloc(sizeof(int) * len);
	if (tab == NULL)
		return (NULL);
	i = 0;
	while (i < len)
	{
		tab[i] = 1;
		i++;
	}
	return (tab);
}
