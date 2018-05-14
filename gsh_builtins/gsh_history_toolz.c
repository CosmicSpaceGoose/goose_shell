/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_history_toolz.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/10 18:11:08 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/10 18:11:09 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static int	gsh_h_search_elem(char *line)
{
	t_hist	*hist;

	if (!(hist = gsh_r_history_bucket(RETURN, 0)))
		return (0);
	while (hist->prv)
		hist = hist->prv;
	while (hist)
	{
		if (!ft_strcmp(line, hist->str))
			return (1);
		hist = hist->nxt;
	}
	return (0);
}

void		gsh_h_read_history(char *str)
{
	int		fd;
	char	*line;

	if (!str)
		str = gsh_get_env("HISTFILE");
	if ((fd = open(str, O_RDONLY)) != -1)
	{
		while (get_next_line(fd, &line) > 0)
		{
			if (!gsh_h_search_elem(line))
			{
				gsh_r_history_bucket(CREATE, 0);
				gsh_r_history_bucket(ADD, line);
			}
			free(line);
		}
	}
}

int			gsh_h_erase_elem(char *str)
{
	if (!str)
		return (gsh_h_usage(1));
	if (!ft_isnumber(str))
		return (gsh_h_usage(2));
	gsh_r_history_bucket(DELONE, str);
	return (0);
}

void		gsh_h_add_record(void)
{
	t_hist	*hist;
	char	*str;
	char	*ptr;
	char	*line;

	hist = gsh_r_history_bucket(RETURN, 0);
	str = ft_itoa((int)hist->no);
	ptr = ft_strchr(hist->str, ' ');
	while (*ptr == ' ')
		ptr++;
	while (*ptr != ' ')
		ptr++;
	while (*ptr == ' ')
		ptr++;
	line = ft_strdup(ptr);
	gsh_r_history_bucket(DELONE, str);
	free(str);
	gsh_r_history_bucket(CREATE, 0);
	gsh_r_history_bucket(ADD, line);
	free(line);
}

void		gsh_h_show_without_add(char **av)
{
	t_hist	*hist;
	char	*str;

	hist = gsh_r_history_bucket(RETURN, 0);
	str = ft_itoa((int)hist->no);
	gsh_r_history_bucket(DELONE, str);
	free(str);
	while (*av)
	{
		ft_putendl(*av);
		av++;
	}
}
