/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/02/02 15:32:03 by agranjon          #+#    #+#             */
/*   Updated: 2024/03/11 17:59:36 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../headers/minishell.h"

extern int	g_signal;

int	ft_cat(void)
{
	if (g_signal != 0)
		return (-1);
	printf(HIGH_GREEN" /\\_/\\                         /\\_/\\\n");
	printf("( o.o )   Do you love cats ?  ( o.o )\n");
	printf(" > ^ <    Me, I love cats.     > ^ <\n"RESET);
	return (0);
}

int	copy_my_env_line_to_new(char **my_env, char **new, int *i_ptr)
{
	int	i;

	if (my_env == NULL || new == NULL || i_ptr == NULL || g_signal != 0)
		return (-1);
	i = 0;
	while (my_env[i])
	{
		new[i] = ft_strdup(my_env[i]);
		if (!new[i])
			return (-1);
		i++;
	}
	*i_ptr = i;
	if (g_signal != 0)
		return (-1);
	return (0);
}

int	copy_my_env_vars_into_new_tab(char **my_env, char **vars, char **new)
{
	int	i;
	int	j;

	i = 0;
	j = 1;
	if (my_env == NULL || vars == NULL || new == NULL || g_signal != 0
		|| copy_my_env_line_to_new(my_env, new, &i) != 0)
		return (-1);
	while (vars[j])
	{
		new[i] = NULL;
		if (check_var_rules(vars[j], 0))
		{
			if (check_var_exist_and_replace(new, vars[j]) == 0)
			{
				new[i] = ft_strdup(vars[j]);
				if (!new[i])
					return (-1);
				i++;
			}
		}
		j++;
	}
	new[i] = NULL;
	return (0);
}

char	**add_vars_into_tab(char **my_env, char **vars)
{
	int		i;
	char	**new;

	if (!my_env || !vars)
		return (NULL);
	i = 0;
	while (vars[i])
		i++;
	new = malloc(sizeof(char *) * (get_double_tab_size(my_env) + i + 1));
	if (new == NULL)
		return (NULL);
	if (copy_my_env_vars_into_new_tab(my_env, vars, new) != 0)
		return (ft_free_tab(new), NULL);
	return (new);
}

int	export(char **vars, char ***my_env)
{
	char	**new;
	int		status;
	int		i;

	if (!my_env || !*my_env || !vars)
		return (-1);
	if (*(vars + 1) == NULL)
		return (ft_cat());
	i = 0;
	status = 0;
	while (vars[++i] != NULL && status == 0)
	{
		if (check_var_rules(vars[i], 1) == 0)
			status = 1;
	}
	new = add_vars_into_tab(*my_env, vars);
	if (new == NULL)
		return (-1);
	if (g_signal == SIGINT)
		return (ft_free_tab(new), 130);
	if (g_signal == SIGQUIT)
		return (ft_free_tab(new), 131);
	ft_free_tab(*my_env);
	*my_env = new;
	return (status);
}
