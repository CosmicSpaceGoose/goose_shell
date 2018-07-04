/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_core.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/21 14:47:11 by dlinkin           #+#    #+#             */
/*   Updated: 2018/06/03 12:47:37 by dlinkin          ###   ########.fr       */
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

void		gsh_pre_launch(t_ok **lines)
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

int			main(void)
{
	char			*line;
	int				i;
	int				rat;
	extern uint32_t	g_opt_n;

	rat = 0;
	if (!isatty(0) || (rat = gsh_init(0)))
		return (rat);
	(g_opt_n & GRAPHICS) ? gsh_write_head() : 0;
	while (gsh_reader(&line, gsh_prompt(1)))
	{
		if (!line)
			continue ;
		(g_opt_n & USE_HIST) ? gsh_r_history_bucket(ADD, line) : 0;
		while ((i = gsh_chaek_extr(line)))
			gsh_extraction(&line, i);
		*line ? gsh_pre_launch(gsh_pc_lines(line)) : 0;
		free(line);
		if ((rat = ft_atoi(gsh_get_env("?"))) > 255)
			break ;
	}
	gsh_end();
	system("leaks -quiet 21sh");
	return (rat);
}
