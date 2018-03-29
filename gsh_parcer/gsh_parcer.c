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

#include "gsh_parcer.h"

/*
**	SPLIT ARGUMETS 'ERE
*/

static void	gsh_skip_redir(char **s)
{
	if (*(*s + 1) == 60 || *(*s + 1) == 62)
		(*s)++;
	if (*(*s + 1) == '&')
		(*s)++;
	while (*(*s + 1) == 32 || *(*s + 1) == 9)
		(*s)++;
	while (*(*s + 1) && *(*s + 1) != 32 && *(*s + 1) != 9)
		(*s)++;
}

static int	gsh_count_argv(char *s, int c)
{
	int ac;

	ac = 0;
	while (*s)
	{
		if (*s && *s != 32 && *s != 9)
			ac++;
		while (*s && *s != 32 && *s != 9)
		{
			if (*s == 60 || *s == 62)
				gsh_skip_redir(&s);
			else if (*s == 92)
				s++;
			else if ((c = *s) == '\"' || c == '\'')
			{
				s++;
				while (*s != c && *s)
					s++;
			}
			s++;
		}
		while (*s == 32 || *s == 9)
			s++;
	}
	return (ac);
}

static int	gsh_count_red(char *s, int red)
{
	int	c;

	while (*s)
	{
		if (*s == 60 || *s == 62)
		{
			s++;
			if (*s == 60 || *s == 62)
				s++;
			red++;
		}
		else
		{
			if (*s == 59)
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

static void	gsh_parcer_part(char *ln, t_arrs o, int *c)
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
				(o.cmd)[c[0]] = gsh_split_word(ln, c[3], 0);
				c[0]++;
			}
		}
		else
		{
			if ((c[3] = gsh_bldzhad(ln, &c[2], 1, 0)))
			{
				(o.red)[c[1]] = gsh_split_red(ln, c[3], 0);
				c[1]++;
			}
		}
		ln += c[2];
	}
}

t_arrs		gsh_parcer(char *line)
{
	t_arrs	o;
	int		c[4];

	while (*line == 32 || *line == 9)
		line++;
	c[0] = gsh_count_argv(line, 0);
	c[1] = gsh_count_red(line, 0);
	o.cmd = NULL;
	o.red = NULL;
	if ((c[0] -= c[1]) > 0)
	{
		o.cmd = (char **)malloc(sizeof(char *) * (c[0] + 1));
		c[1] ? o.red = (char **)malloc(sizeof(char *) * (c[1] + 1)) : 0;
		c[0] = 0;
		c[1] = 0;
		gsh_parcer_part(line, o, c);
		(o.cmd)[c[0]] = NULL;
		if (o.red)
			(o.red)[c[1]] = NULL;
	}
	return (o);
}
