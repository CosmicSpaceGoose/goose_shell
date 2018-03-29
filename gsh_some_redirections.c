/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_some_redirections.c                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/22 16:43:35 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/22 16:43:36 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static void	redir_input(int fdin, char *red)
{
	char *line;

	if (*red == 60)
	{
		red++;
		while (1)
		{
			gsh_reader(&line, write(1, "heredoc> ", 9));
			if (ft_strcmp(line, red))
			{
				write(fdin, line, ft_strlen(line));
				free(line);
			}
			else
			{
				free(line);
				break ;
			}
		}
	}
	else
	{
		if (!ft_strcmp(red, "-"))
			close(fdin);
		else
			;
	}
}

static void	redir_output(int fdout, char *red)
{
	fdout = 1;
	red++;
}

void		gsh_make_some_redirections(char **red)
{
	int fd;

	fd = -1; //	??
	while (*red)
	{
		if (**red > 47 && **red < 58)
		{
			fd = **red - 48;
			(*red)++;
		}
		if (**red == 60)
		{
			fd == -1 ? fd = 0 : 0;
			redir_input(fd, *red + 1);
		}
		else
		{
			fd == -1 ? fd = 1 : 0;
			redir_output(fd, *red + 1);
		}
		red++;
	}
}
