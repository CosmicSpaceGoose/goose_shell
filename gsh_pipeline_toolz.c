/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_pipeline_toolz.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/04/27 14:20:25 by dlinkin           #+#    #+#             */
/*   Updated: 2018/04/27 14:20:26 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

static int	gsh_heredoc(char *str)
{
	int		fd[2];
	char	*buf;

	pipe(fd);
	buf = NULL;
	while (gsh_reader(&buf, write(0, "heredoc> ", 9)))
	{
		if (!ft_strcmp(str, buf))
			break ;
		ft_putstr_fd(buf, fd[1]);
		ft_putchar_fd('\n', fd[1]);
		free(buf);
		buf = NULL;
		gsh_r_history_bucket(1, NULL);
	}
	free(buf);
	close(fd[1]);
	return (fd[0]);
}

/*
**		MAKE PIPES
*/

void		gsh_open_close_pipes(int **fds, int **cp, int i, int mod)
{
	int k;

	if (!mod)
	{
		while (i > 0)
		{
			i--;
			close((*cp)[i]);
		}
		*fds = NULL;
		free(*cp);
	}
	else
	{
		k = 0;
		*fds = (int *)malloc(sizeof(int) * i);
		*cp = *fds;
		while (k < i)
		{
			pipe(*fds + k);
			k += 2;
		}
	}
}

void		gsh_open_files(t_orba **z)
{
	int		k;

	while (*z && ((*z)->tok != 'e' && (*z)->tok != 'a' && (*z)->tok != 'o'))
	{
		if ((*z)->red)
		{
			k = 0;
			while ((*z)->red[k])
			{
				if (((*z)->red[k])->io != 'I' && ((*z)->red[k])->ptr)
					((*z)->red[k])->fd = open(((*z)->red[k])->ptr,
						((*z)->red[k])->flgs, 0666);
				else if (((*z)->red[k])->io == 'I')
					((*z)->red[k])->fd = gsh_heredoc(((*z)->red[k])->ptr);
				k++;
			}
		}
		z++;
	}
}

void		gsh_close_files(t_orba *z, int *pps)
{
	int k;

	if (z->red)
	{
		k = 0;
		while (z->red[k])
		{
			if ((z->red[k])->fd != -1)
				close((z->red[k])->fd);
			k++;
		}
		pps[2] = 0;
	}
}
