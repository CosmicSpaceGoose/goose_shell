/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_pre_parcer.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/12 12:16:22 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/12 12:16:23 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_parcer.h"

/*
**		PRE_PARCER_1
*/

static int	gsh_pc_num_lines(char *l, int i, int c)
{
	while (*l)
	{
		if (*l != '|' && *l != ';' && *l != '&')
			while (*l && *l != '|' && *l != ';' && *l != '&')
			{
				if (*l == '\\')
					l++;
				else if ((c = *l) == '\'' || c == '\"')
				{
					l++;
					while (*l && *l != c)
						l++;
					if (!*l)
					{
						write(2, "|< Parcing error\n", 17);
						return (0);
					}
				}
				l++;
			}
		else if (((c = *l) == '|' || c == ';' || c == '&') && (l++))
			(*l && c == *l) ? l++ : 0;
		i++;
	}
	return (i);
}

static int	gsh_pc_len(char *line)
{
	int c;
	int i;

	i = 0;
	if ((c = line[i]) == '|' || c == ';' || c == '&')
	{
		i++;
		(line[i] && line[i] == c) ? i++ : 0;
	}
	else
	{
		while (line[i] && line[i] != '|' && line[i] != ';' && line[i] != '&')
		{
			if (line[i] == '\\')
				i++;
			else if ((c = line[i]) == '\'' || c == '\"')
			{
				i++;
				while (line[i] != c)
					i++;
			}
			i++;
		}
	}
	return (i);
}

t_ok		**gsh_pc_lines(char *line)
{
	t_ok	**out;
	int		j;
	int		i;
	int		len;
	int		num;

	num = gsh_pc_num_lines(line, 0, 0);
	if (!num)
		return (NULL);
	out = (t_ok **)malloc(sizeof(t_ok *) * (num + 1));
	j = 0;
	i = 0;
	while (j < num)
	{
		len = gsh_pc_len(&line[i]);
		out[j] = (t_ok *)malloc(sizeof(t_ok));
		(out[j])->str = (char *)malloc(sizeof(char) * (len + 1));
		ft_strncpy((out[j])->str, &line[i], len);
		(out[j])->str[len] = 0;
		i += len;
		j++;
	}
	out[j] = NULL;
	return (out);
}
