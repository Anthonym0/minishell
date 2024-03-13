/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_string_write.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/06 11:54:16 by aherve            #+#    #+#             */
/*   Updated: 2024/03/11 18:37:02 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

char	*ft_strdup(char *str)
{
	char	*new;
	int		i;

	if (str == NULL)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(str) + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (str[i] != '\0')
	{
		new[i] = str[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

char	*ft_strndup(char *input, int n)
{
	char	*new;
	int		i;

	if (input == NULL || n == -1)
		return (NULL);
	new = malloc(sizeof(char *) * (n + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (i < n)
	{
		new[i] = input[i];
		i++;
	}
	new[i] = '\0';
	return (new);
}

int	ft_strcpy(char *dest, char *src)
{
	int	i;

	if (dest == NULL || src == NULL)
		return (-1);
	i = 0;
	while (src[i] != '\0')
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = '\0';
	return (0);
}

int	ft_strncpy(char *dest, char *src, int n)
{
	int	i;

	if (dest == NULL || src == NULL)
		return (-1);
	i = 0;
	while (i < n && *src != '\0')
	{
		dest[i] = src [i];
		i++;
	}
	dest[i] = '\0';
	return (i);
}

char	*ft_strjoin(char *s1, char *s2)
{
	char	*new;
	int		i;
	int		j;

	if (s1 == NULL || s2 == NULL)
		return (NULL);
	new = malloc(sizeof(char) * (ft_strlen(s1) + ft_strlen(s2) + 1));
	if (new == NULL)
		return (NULL);
	i = 0;
	while (s1[i] != '\0')
	{
		new[i] = s1[i];
		i++;
	}
	j = 0;
	while (s2[j] != '\0')
	{
		new[i + j] = s2[j];
		j++;
	}
	new[i + j] = '\0';
	return (new);
}
