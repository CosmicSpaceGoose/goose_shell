/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_parcer.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 12:59:19 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/30 12:59:21 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**	SPLIT ARGUMETS 'ERE
*/

static void		gsh_skip_redir(char **s)
{
	if (*(*s + 1) == '<' || *(*s + 1) == '>')
		(*s)++;
	if (*(*s + 1) == '&')
		(*s)++;
	while (*(*s + 1) == ' ' || *(*s + 1) == '\t')
		(*s)++;
	while (*(*s + 1) && *(*s + 1) != ' ' && *(*s + 1) != '\t')
		(*s)++;
}

static int		gsh_count_argv(char *s, int c)
{
	int ac;

	ac = 0;
	while (*s)
	{
		if (*s && *s != ' ' && *s != '\t')
			ac++;
		while (*s && *s != ' ' && *s != '\t')
		{
			if (*s == '<' || *s == '>')
				gsh_skip_redir(&s);
			else if (*s == '\\')
				s++;
			else if ((c = *s) == '\"' || c == '\'')
			{
				s++;
				while (*s != c && *s)
					s++;
			}
			s++;
		}
		while (*s == ' ' || *s == '\t')
			s++;
	}
	return (ac);
}

static int		gsh_count_red(char *s, int red)
{
	int	c;

	while (*s)
	{
		if (*s == '<' || *s == '>')
		{
			s++;
			if (*s == '<' || *s == '>')
				s++;
			red++;
		}
		else
		{
			if (*s == ';')
				s++;
			else if ((c = *s) == '\"' || c == '\'')
			{
				s++;
				while (*s != c && *s)
					s++;
			}
			s++;
		}
	}
	return (red);
}

/*
**	c[0] - number of arguments, c[1] - number of redirections,
**	c[2] - line shift, c[3] - size of argument/redirection
*/

static t_orba	*gsh_parce_elements(char *line)
{
	char	**cmd;
	char	**red;
	t_orba	*t;
	int		c[4];

	t = (t_orba *)malloc(sizeof(t_orba));
	while (*line == ' ' || *line == '\t')
		line++;
	c[0] = gsh_count_argv(line, 0);
	c[1] = gsh_count_red(line, 0);
	cmd = NULL;
	red = NULL;
	c[0] ? cmd = (char **)malloc(sizeof(char *) * (c[0] + 1)) : 0;
	c[1] ? red = (char **)malloc(sizeof(char *) * (c[1] + 1)) : 0;
	c[0] = 0;
	c[1] = 0;
	gsh_parcer_part(line, cmd, red, c);
	cmd ? cmd[c[0]] = NULL : 0;
	red ? red[c[1]] = NULL : 0;
	t->cmd = cmd;
	t->red = gsh_parce_redir(red);
	ft_free_arr((void **)red);
	return (t);
}

t_orba			**gsh_parcer(t_ok **lines)
{
	t_orba	**out;
	int		i;

	i = 0;
	while (lines[i])
		i++;
	out = (t_orba **)malloc(sizeof(t_orba *) * (i + 1));
	out[i] = NULL;
	while (i)
	{
		i--;
		if ((lines[i])->tok == 'p' || (lines[i])->tok == 'e')
			out[i] = gsh_parce_apozh((lines[i])->str);
		else
			out[i] = gsh_parce_elements((lines[i])->str);
		(out[i])->tok = (lines[i])->tok;
	}
	return (out);
}
