/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_expansion.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/07 17:04:50 by aherve            #+#    #+#             */
/*   Updated: 2024/03/12 11:14:58 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

char	*env_var_value(char *var_name, char **envp)
{
	int		i;
	int		status;
	char	*value;

	if (var_name == NULL || envp == NULL)
		return (NULL);
	i = 0;
	while (envp[i] != NULL)
	{
		status = ft_strcmp_sep(var_name, envp[i], '=');
		if (status == -1)
			break ;
		if (status == 0)
		{
			value = get_var_value(envp[i]);
			return (value);
		}
		i++;
	}
	value = malloc(sizeof(char));
	if (value == NULL)
		return (NULL);
	value[0] = '\0';
	return (value);
}

char	*expand_token(t_token *token, int pos, int diff, char *value)
{
	char	*expanded;
	int		value_len;

	if (token == NULL || pos < 0 || value == NULL)
		return (NULL);
	expanded = malloc(sizeof(char) * ((token->len + 1) + (diff - 1)));
	if (expanded == NULL)
		return (NULL);
	if (ft_strncpy(expanded, token->str, pos) == -1)
		return (free(expanded), NULL);
	value_len = ft_strlen(value);
	if (value_len == -1)
		return (free(expanded), NULL);
	token->str += pos + value_len - diff + 1;
	if (ft_strcpy(expanded + pos, value) == -1)
		return (free(expanded), NULL);
	if (ft_strcpy(expanded + pos + value_len, token->str) == -1)
		return (free(expanded), NULL);
	token->len = ft_strlen(expanded);
	return (expanded);
}

int	get_env_var(t_token *token, int pos, char **envp)
{
	char	*var_name;
	char	*var_value;
	int		name_len;
	int		value_len;
	char	*temp;

	if (token == NULL || envp == NULL || pos < 0)
		return (-1);
	name_len = var_len(&token->str[pos]);
	if (name_len == -1)
		return (-1);
	var_name = ft_strndup(&token->str[pos], name_len);
	if (var_name == NULL)
		return (-1);
	var_value = env_var_value(var_name, envp);
	free(var_name);
	if (var_value == NULL)
		return (0);
	value_len = ft_strlen(var_value);
	temp = token->str;
	token->str = expand_token(token, pos - 1, value_len - name_len, var_value);
	if (token->str == NULL)
		return (free(temp), free(var_value), -1);
	return (free(temp), free(var_value), 0);
}

int	find_env_vars(t_token *token, char **envp)
{
	int	quote;
	int	dquote;
	int	i;

	if (token == NULL || envp == NULL)
		return (-1);
	quote = 0;
	dquote = 0;
	i = 0;
	while (token->str[i] != '\0')
	{
		if (token->str[i] == '"' && quote % 2 == 0)
			dquote++;
		if (token->str[i] == '\'' && dquote % 2 == 0)
			quote++;
		if (token->str[i] == '$' && quote % 2 == 0)
		{
			if (get_env_var(token, i + 1, envp) == -1)
				return (-1);
			i = -1;
		}
		i++;
	}
	return (0);
}

int	expand_env_vars(t_token *list, char **envp)
{
	t_token	*cur;

	if (list == NULL || envp == NULL)
		return (-1);
	cur = list;
	while (cur != NULL)
	{
		if (find_env_vars(cur, envp) == -1)
			return (-1);
		cur = cur->next;
	}
	return (0);
}
