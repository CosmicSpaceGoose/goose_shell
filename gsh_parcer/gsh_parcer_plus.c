/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_parcer_plus.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/21 13:44:49 by dlinkin           #+#    #+#             */
/*   Updated: 2018/02/21 13:44:51 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_parcer.h"

/*
**	LENTH OF WORD/REDIR
*/

int		gsh_split_tilde(char **cmd, int *k)
{
	char	*ptr;
	int		old;

	ptr = gsh_get_env("HOME");
	old = *k;
	*k -= 1 - ft_strlen(ptr);
	*cmd = (char *)ft_realloc(*k, old, (void *)*cmd);
	if (ptr)
		ft_strcat(*cmd, ptr);
	return (ft_strlen(*cmd));
}

int		gsh_word(char *s, int *n, int i)
{
	char	c;

	while (s[*n] && s[*n] != 59 && s[*n] != 32 && s[*n] != 9)
	{
		if ((s[*n] >= 0 && s[*n] <= 9 && (s[*n + 1] == 60 ||
			s[*n + 1] == 62) && ((s[*n - 1] == 32 || s[*n - 1] == 9) ||
			(s[*n] == 60 || s[*n] == 62))))
			break ;
		if (s[*n] == 92)
			(*n)++;
		else if ((c = s[*n]) == '\"' || c == '\'')
		{
			(*n)++;
			while (s[*n] && s[*n] != c)
			{
				(*n)++;
				i++;
			}
			i--;
		}
		(*n)++;
		i++;
	}
	return (i);
}

int		gsh_bldzhad(char *s, int *n, int i, int c)
{
	(s[*n] > 47 && s[*n] < 58 && ((*n)++)) ? i++ : 0;
	(s[*n] == 60 || s[*n] == 62) ? (*n)++ : 0;
	((s[*n] == 60 || s[*n] == 62) && ((*n)++)) ? i++ : 0;
	(s[*n] == '&' && ((*n)++)) ? i++ : 0;
	while (s[*n] == 32 || s[*n] == 9)
		(*n)++;
	while (s[*n] && s[*n] != 32 && s[*n] != 9)
	{
		if (s[*n] == 92)
			(*n)++;
		else if ((c = s[*n]) == '\"' || c == '\'')
		{
			(*n)++;
			while (s[*n] != c)
			{
				(*n)++;
				i++;
			}
			i--;
		}
		(*n)++;
		i++;
	}
	return (i);
}
