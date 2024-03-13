/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prompt.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: aherve <aherve@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/01/26 11:54:14 by aherve            #+#    #+#             */
/*   Updated: 2024/01/26 15:20:40 by aherve           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PROMPT_H
# define PROMPT_H

//prompt_utils.c
int		find_lastdir(char *str);
int		is_empty(char *str);
char	*add_color(char *str, char *color);
int		count_slashes(char *ap_name, int cwd_index);

//prompt.c
char	*prompt(void);

#endif