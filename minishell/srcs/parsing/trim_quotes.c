/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   trim_quotes.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/09 12:03:24 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:32:34 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

int	has_quotes(char *str)
{
	if (str == NULL)
		return (-1);
	while (*str != '\0')
	{
		if (*str == '"' || *str == '\'')
			return (1);
		str++;
	}
	return (0);
}

int	check_quotes(char *str, int *tab)
{
	int	i;
	int	quote;
	int	dquote;

	if (str == NULL || tab == NULL)
		return (-1);
	i = 0;
	quote = 0;
	dquote = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '"' && quote % 2 == 0)
		{
			dquote++;
			tab[i] = 0;
		}
		if (str[i] == '\'' && dquote % 2 == 0)
		{
			quote++;
			tab[i] = 0;
		}
		i++;
	}
	return (0);
}

char	*create_unquoted_str(char *str, int *tab, int len)
{
	char	*new;
	int		i;
	int		j;

	if (str == NULL || tab == NULL || len < 0)
		return (NULL);
	new = malloc(sizeof(char) * (sum_int_array(tab, len) + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	j = 0;
	while (str[i] != '\0')
	{
		if (tab[i] == 1)
		{
			new[j] = str[i];
			j++;
		}
		i++;
	}
	new[j] = '\0';
	return (new);
}

char	*trim_quotes(char *str, int len)
{
	char	*new;
	int		*tab;
	int		status;

	if (str == NULL || len == -1)
		return (NULL);
	status = has_quotes(str);
	if (status == -1)
		return (NULL);
	if (status == 0)
		return (str);
	tab = create_and_init_tab(len);
	if (tab == NULL)
		return (NULL);
	if (check_quotes(str, tab) == -1)
		return (free(tab), NULL);
	new = create_unquoted_str(str, tab, len);
	free(tab);
	return (new);
}
