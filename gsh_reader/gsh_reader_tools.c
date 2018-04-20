/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_tools.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/27 13:40:40 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/27 13:40:41 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_reader.h"

static void	gsh_redraw_on_resize(char *save_out, t_pos *save_pos)
{
	size_t	kur;

	kur = save_pos->kur + save_pos->prompt;
	tputs(tgoto(tgetstr("LE", 0), 1, kur), 1, ft_putint);
	tputs(tgetstr("cd", 0), 1, ft_putint);
	gsh_prompt(1);
	tputs(save_out, 1, ft_putint);
	if (save_pos->len != save_pos->kur)
		tputs(tgoto(tgetstr("LE", 0), 1, save_pos->len - save_pos->kur)
			, 1, ft_putint);
}

void		gsh_r_redraw_line(char *out, t_pos *pos, size_t size, int mod)
{
	static char		*save_out;
	static t_pos	*save_pos;

	if (mod == 1)
	{
		tputs(tgetstr("cd", 0), 1, ft_putint);
		tputs(out + pos->kur - size, 1, ft_putint);
		if (pos->len != pos->kur)
			tputs(tgoto(tgetstr("LE", 0), 1, pos->len - pos->kur)
				, 1, ft_putint);
	}
	else if (mod == 2)
	{
		save_out = out;
		save_pos = pos;
		save_pos->kur = 0;
		save_pos->len = 0;
		save_pos->col = (size_t)tgetnum("co");
	}
	else if (mod == 0)
		gsh_redraw_on_resize(save_out, save_pos);
}

int			gsh_r_check_pos(t_pos *pos)
{
	size_t kur;

	tgetent(0, getenv("TERM"));
	pos->col = (size_t)tgetnum("co");
	kur = pos->kur + pos->prompt;
	if (kur % pos->col == 0)
		return (1);
	return (0);
}

void		gsh_r_shift_right(t_pos *pos)
{
	pos->kur++;
	if (gsh_r_check_pos(pos))
	{
		tputs(tgetstr("do", 0), 1, ft_putint);
		tputs(tgetstr("cr", 0), 1, ft_putint);
	}
	else
		tputs(tgetstr("nd", 0), 1, ft_putint);
}

void		gsh_r_shift_left(t_pos *pos)
{
	if (gsh_r_check_pos(pos))
	{
		tputs(tgetstr("up", 0), 1, ft_putint);
		tputs(tgoto(tgetstr("RI", 0), 1, pos->col - 1), 1, ft_putint);
	}
	else
		tputs(tgetstr("le", 0), 1, ft_putint);
	pos->kur--;
}
