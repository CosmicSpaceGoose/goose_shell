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

int			gsh_split_tilde(char **cmd, int *k)
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

static int	gsh_word(char *s, int *n, int i)
{
	char	c;

	while (s[*n] && s[*n] != 59 && s[*n] != 32 && s[*n] != 9)
	{
		if ((s[*n] == 60 || s[*n] == 62)
			|| (s[*n] == 38 && (s[*n + 1] == 60 || s[*n + 1] == 62))
			|| (s[*n] >= 0 && s[*n] <= 9 && (s[*n + 1] == 60 ||
				s[*n + 1] == 62) && (s[*n - 1] == 32 || s[*n - 1] == 9)))
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

static int	gsh_bldzhad(char *s, int *n, int i, int c)
{
	(s[*n] > 47 && s[*n] < 58) ? i++ : 0;
	((s[*n + i] == 60 || s[*n + i] == 62)) ? i++ : 0;
	((s[*n + i] == 60 || s[*n + i] == 62)) ? i++ : 0;
	s[*n + i] == 38 ? i++ : 0;
	(*n) += i;
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

void		gsh_parcer_part(char *ln, char **cmd, char **red, int *c)
{
	while (*ln)
	{
		c[2] = 0;
		while (*ln == 32 || *ln == 9)
			ln++;
		if (*ln != 60 && *ln != 62 && *(ln + 1) != 60 && *(ln + 1) != 62)
		{
			if ((c[3] = gsh_word(ln, &c[2], 0)))
			{
				cmd[c[0]] = gsh_split_word(ln, c[3], 0);
				c[0]++;
			}
		}
		else
		{
			if ((c[3] = gsh_bldzhad(ln, &c[2], 1, 0)))
			{
				red[c[1]] = gsh_split_red(ln, c[3], 0);
				c[1]++;
			}
		}
		ln += c[2];
	}
}

t_orba		*gsh_parce_apozh(char *line)
{
	t_orba	*t;

	t = (t_orba *)malloc(sizeof(t_orba));
	t->cmd = (char **)malloc(sizeof(char *) * 2);
	t->cmd[0] = ft_strdup(line);
	t->cmd[1] = NULL;
	t->red = NULL;
	return (t);
}
