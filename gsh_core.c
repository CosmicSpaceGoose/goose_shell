/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:32:53 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/15 16:32:55 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_core.h"

/*
**		YEAP, ITS A MAIN  ###  GOOSE_SHELL V2.08.03.18
*/

static void	gsh_count_pipes(char **lines, int *pipes)
{
	int total;

	total = 0;
	while (*lines)
	{
		if (**lines == '|' || **lines == '>' || **lines == '<')
			total++;
		else if (**lines == ';')
			break ;
		lines++;
	}
	if (!pipes[0] && total)
	{
		pipes[0] = total;
		pipes[1] = 1;
	}
	else if (pipes[0])
	{
		if (!total)
			pipes[1] = 3;
		else
			pipes[1] = 2;
	}
}

static void	gsh_ppppowa(char *line, int *pipes, int **cp, int **fds)
{
	if (pipes[0])
	{
		if (!*fds)
		{
			*fds = (int *)malloc(sizeof(int) * pipes[0] * 2);
			*cp = *fds;
		}
		pipes[1] != 3 ? pipe(*fds) : 0;
	}
	if ((gsh_seek(line, pipes, *fds)) > 255)
	{
		pipes[0] ? free(*cp) : 0;
		return ;
	}
	if (pipes[0] && pipes[1] == 3)
	{
		free(*cp);
		pipes[0] = 0;
		*fds = NULL;
	}
	else if (pipes[0])
		(*fds) += 2;
}

void		gsh_cycle(char **lines)
{
	int		i;
	int		pipes[2];
	int		*cp;
	int		*fds;

	if (gsh_pc_validate(lines))
		ft_putendl_fd("gsh: parcing/syntax error", 2);
	else
	{
		i = 0;
		pipes[0] = 0;
		fds = 0;
		while (lines[i])
		{
			if (lines[i][0] == ';' || lines[i][0] == '|')
			{
				i++;
				continue ;
			}
			gsh_count_pipes(lines + i, pipes);
			gsh_ppppowa(lines[i], pipes, &cp, &fds);
			i++;
		}
	}
	ft_free_arr((void **)lines);
}

static void	gsh_readmoar_atzero(char **line)
{
	char *ptr;
	char *tmp;

	write(1, "> ", 2);
	gsh_reader(&tmp, 0);
	ptr = ft_strsub(*line, 0, ft_strlen(*line) - 1);
	free(*line);
	*line = ft_strjoin(ptr, tmp);
	free(tmp);
	free(ptr);
}

int			main(void)
{
	char	*line;
	char	*ptr;
	int		rat;

	gsh_init(0);
	rat = 0;
	// gsh_write_head();
	while (gsh_reader(&line, gsh_prompt(1)))
	{
		ft_dprintf(2, "[%s]\n", line);
		while ((ptr = ft_strrchr(line, 92)) && *(ptr + 1) == '\0'
			&& *(ptr - 1) != 92)
			gsh_readmoar_atzero(&line);
		line[0] ? gsh_cycle(gsh_pc_lines(line)) : 0;
		free(line);
		if ((rat = ft_atoi(gsh_get_env("?"))) > 255)
			break ;
	}
	// exit_draw();
	gsh_r_history_bucket(-1, NULL);
	gsh_bucket(3, 0);
	// system("leaks 21sh");
	return (rat);
}
