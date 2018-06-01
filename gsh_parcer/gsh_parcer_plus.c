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

#include "gsh_core.h"

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

	while (s[*n] && s[*n] != ';' && s[*n] != ' ' && s[*n] != '\t')
	{
		if ((s[*n] == '<' || s[*n] == '>')
			|| (s[*n] == '&' && (s[*n + 1] == '<' || s[*n + 1] == '>'))
			|| (s[*n] >= 0 && s[*n] <= '\t' && (s[*n + 1] == '<' ||
			s[*n + 1] == '>') && (s[*n - 1] == ' ' || s[*n - 1] == '\t')))
			break ;
		if (s[*n] == '\\')
			(*n)++;
		else if ((c = s[*n]) == '\"' || c == '\'')
		{
			(*n)++;
			while (s[*n] && s[*n] != c)
			{
				(s[*n] != '\\') ? i++ : 0;
				(*n)++;
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
	(s[*n + i] == '<' || s[*n + i] == '>') ? i++ : 0;
	(s[*n + i] == '<' || s[*n + i] == '>') ? i++ : 0;
	s[*n + i] == '&' ? i++ : 0;
	(*n) += i;
	while (s[*n] == ' ' || s[*n] == '\t')
		(*n)++;
	while (s[*n] && s[*n] != ' ' && s[*n] != '\t')
	{
		if (s[*n] == '\\')
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
		while (*ln == ' ' || *ln == '\t')
			ln++;
		if (*ln != '<' && *ln != '>' && !(ft_isdigit(*ln)
			&& (ln[1] == '<' || ln[1] == '>')))
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
	t->cmd = (char **)malloc(sizeof(char *) * (ft_strlen(line) + 1));
	t->cmd[0] = ft_strdup(line);
	t->cmd[1] = NULL;
	t->red = NULL;
	return (t);
}
