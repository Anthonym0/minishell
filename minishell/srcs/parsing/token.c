/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: agranjon <agranjon@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 11:02:32 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 10:00:20 by agranjon         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	end_of_token(char *str, int i)
{
	if (!str)
		return (-1);
	if (str[i] == ' ')
		return (1);
	if (i == 0)
		return (0);
	if (str[i] == '|' || str[i - 1] == '|')
		return (1);
	if ((str[i] == '>' || str[i] == '<') && str[i - 1] != str[i])
		return (1);
	return (0);
}

int	quotes_open(char *input)
{
	int	quote;
	int	dquote;

	if (input == NULL)
		return (-1);
	quote = 0;
	dquote = 0;
	while (*input != '\0')
	{
		if (*input == '"' && quote % 2 == 0)
			dquote++;
		if (*input == '\'' && dquote % 2 == 0)
			quote++;
		input++;
	}
	if (quote % 2 != 0)
		return (err_msg_parsing("Single quote not closed\n"), 1);
	if (dquote % 2 != 0)
		return (err_msg_parsing("Double quote not closed\n"), 1);
	return (0);
}

int	token_len(char *str)
{
	int	len;
	int	quote;
	int	dquote;

	if (str == NULL)
		return (-1);
	len = 0;
	quote = 0;
	dquote = 0;
	while (str[len] != '\0')
	{
		if (str[len] == '"' && quote % 2 == 0)
			dquote++;
		if (str[len] == '\'' && dquote % 2 == 0)
			quote++;
		if (end_of_token(str, len) == 1 && quote % 2 == 0 && dquote % 2 == 0)
			return (len);
		len++;
	}
	return (len);
}

t_token	*create_token_list(char *input)
{
	int		len;
	char	*str;
	t_token	*cur;
	t_token	*first;

	if (input == NULL)
		return (NULL);
	first = NULL;
	while (*input != '\0')
	{
		if (*input >= '!' && *input <= '~')
		{
			len = token_len(input);
			str = ft_strndup(input, len);
			cur = new_token(str, len);
			first = token_addback(first, cur);
			if (first == NULL)
				return (free_tokens(first), NULL);
			input += len - 1;
		}
		input++;
	}
	return (first);
}
