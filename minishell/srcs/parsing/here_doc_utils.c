/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   here_doc_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/03/08 15:27:12 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 12:03:11 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

void	sigint_catched(int sig)
{
	g_signal = sig;
	sigint_received(42);
	close(STDIN_FILENO);
}

void	err_msg_heredoc(char *text)
{
	if (!text)
		return ;
	write(2, RED"Minishell: HEREDOC ERROR -> ", 35);
	write(2, text, ft_strlen(text));
	write(2, RESET, 4);
}

char	*get_delimiter(char *str)
{
	char	*new;
	int		len;

	if (str == NULL)
		return (NULL);
	len = ft_strlen(str);
	if (len == -1)
		return (NULL);
	new = malloc(sizeof(char) * ((len) - 1));
	if (new == NULL)
		return (NULL);
	if (ft_strcpy(new, str + 2) == -1)
		return (NULL);
	new[len - 2] = '\0';
	return (new);
}

int	integer_length(int nb)
{
	int	count;

	count = 1;
	while (nb >= 10)
	{
		nb /= 10;
		count++;
	}
	return (count);
}

char	*create_file_name(int nb)
{
	int		length;
	char	*file;

	length = integer_length(nb) + 8;
	file = malloc(sizeof(char) * (length + 1));
	if (file == NULL)
		return (NULL);
	file[length] = '\0';
	length--;
	while (length > 0)
	{
		file[length] = nb % 10 + '0';
		nb /= 10;
		length--;
	}
	file[0] = '<';
	file[1] = '<';
	file[2] = '/';
	file[3] = 't';
	file[4] = 'm';
	file[5] = 'p';
	file[6] = '/';
	file[7] = '.';
	return (file);
}
