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
**		YEAP, ITS A MAIN  ###  GOOSE_SHELL V2.09.05.18
*/

static void	gsh_free_tok(t_ok **tok)
{
	t_ok **cp;

	cp = tok;
	while (*tok)
	{
		free((*tok)->str);
		free(*tok);
		*tok = NULL;
		tok++;
	}
	free(cp);
	tok = NULL;
}

static void	free_sum_fkn_shit(t_orba **z)
{
	t_orba	**cp;
	t_redir	**red;

	cp = z;
	while (*z)
	{
		ft_free_arr((void **)(*z)->cmd);
		if ((*z)->red)
		{
			red = (*z)->red;
			while (*red)
			{
				free((*red)->ptr);
				free(*red);
				red++;
			}
			free((*z)->red);
		}
		free(*z);
		z++;
	}
	free(cp);
}

static void	gsh_pre_launch(t_ok **lines)
{
	int		pps[3];
	t_orba	**z;

	if (lines)
	{
		if (gsh_pc_validate(lines))
			write(2, "|< parcing/syntax error\n", 24);
		else
		{
			z = gsh_parcer(lines);
			pps[0] = 0;
			pps[1] = 0;
			pps[2] = 0;
			gsh_cycle(z, pps, NULL, NULL);
			free_sum_fkn_shit(z);
		}
		gsh_free_tok(lines);
	}
}

static void	gsh_readmoar_atzero(char **line)
{
	char *ptr;
	char *tmp;

	gsh_reader(&tmp, write(0, "> ", 2));
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

	if (!isatty(0))
		return (0);
	gsh_init(0);
	rat = 0;
	// gsh_write_head();
	while (gsh_reader(&line, gsh_prompt(1)))
	{
		gsh_r_history_bucket(1, line);
		while ((ptr = ft_strrchr(line, 92)) && *(ptr + 1) == '\0'
			&& *(ptr - 1) != 92)
			gsh_readmoar_atzero(&line);
		line[0] ? gsh_pre_launch(gsh_pc_lines(line)) : 0;
		free(line);
		if ((rat = ft_atoi(gsh_get_env("?"))) > 255)
			break ;
	}
	// exit_draw();
	gsh_r_history_bucket(-1, NULL);
	gsh_bucket(FREE_ALL, 0);
	system("leaks 21sh | tail -n 4");
	return (rat);
}
