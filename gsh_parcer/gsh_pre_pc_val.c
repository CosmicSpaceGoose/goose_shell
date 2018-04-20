/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_pre_pc_val.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:29:56 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/14 14:29:58 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_parcer.h"

/*
**		PRE_PARCER_2
*/

static int	gsh_pc_val_redir(char *line, int flg)
{
	int c;

	c = *line;
	if (!(flg == -1 && c == ';') && (flg == 1 || (flg == 2 && c != ';')))
		return (-1);
	if (c != ';')
		flg = 1;
	else
		flg = 2;
	line++;
	if (*line == c)
		line++;
	else if (*line)
		return (-1);
	if (*line)
		return (-1);
	return (flg);
}

static int	gsh_pc_val_wrds(char *line, int flg)
{
	while (*line && (*line == 32 || *line == 9))
		(line)++;
	if (!*line && flg == 1)
		return (-1);
	while (*line && *line != '|' && *line != ';')
	{
		if (*line == 60 || *line == 62)
		{
			line++;
			if ((*line == 60 || *line == 62) && (line++))
				if (*line == 60 && *(line + 1) == 38)
					return (-1);
			*line == 38 ? line++ : 0;
			while (*line == 32 || *line == 9)
				line++;
			if (*line == 38 || !*line || *line == 59 || *line == '|')
				return (-1);
		}
		else
			*line == '\\' ? line++ : 0;
		line++;
	}
	flg = 0;
	return (flg);
}

static int	gsh_pc_get_token(char *str, int c)
{
	int rat;

	rat = 0;
	while (*str)
	{
		if (*str == '\'' || *str == '\"')
		{
			if (!c)
				c = *str;
			else if (c == *str)
				c = 0;
		}
		else if (*str == '\\')
			str++;
		else if (!c && (*str == 60 || *str == 62))
		{
			if (*str == 60)
				rat |= 1;
			else
				rat |= 2;
		}
		str++;
	}
	return (rat);
}

int			gsh_pc_validate(t_tok **in)
{
	int		flg;
	char	*str;

	flg = -1;
	while (*in)
	{
		str = (*in)->str;
		if (*str && (*str == ';' || *str == '|'))
		{
			if ((flg = gsh_pc_val_redir(str, flg)) < 0)
				return (1);
			*str == ';' ? (*in)->tok = 'e' : 0;
			*str == '|' ? (*in)->tok = 'p' : 0;
		}
		else
		{
			if ((flg = gsh_pc_val_wrds(str, flg)) < 0)
				return (1);
			(*in)->tok = gsh_pc_get_token(str, 0);
		}
		in++;
	}
	if (flg == 1)
		return (1);
	return (0);
}
