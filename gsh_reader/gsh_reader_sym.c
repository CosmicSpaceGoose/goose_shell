/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader_sym.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/25 14:09:25 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/25 14:09:26 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_reader.h"

/*
**	PRINTABLE CHARACTERS & CONTROL CHARACTERS
*/

static void	gsh_r_backspace(char *out, t_pos *pos)
{
	if (pos->kur == pos->len)
		out[pos->len - 1] = 0;
	else
		ft_memmove(out + pos->kur - 1, out + pos->kur, ft_strlen(out)
			- pos->kur + 1);
	if (gsh_r_check_pos(pos))
	{
		tputs(tgetstr("up", 0), 1, ft_putint);
		tputs(tgoto(tgetstr("RI", 0), 1, pos->col - 1), 1, ft_putint);
	}
	else
		tputs(tgetstr("le", 0), 1, ft_putint);
	gsh_r_redraw_line(out, pos, 1, 1);
	pos->len--;
	pos->kur--;
}

void		gsh_r_prnt_char(t_ych u, char *out, t_pos *pos, size_t size)
{
	if (u.d != 127)
	{
		if (pos->kur < pos->len)
			ft_memmove(out + pos->kur + size, out + pos->kur, ft_strlen(out)
				- pos->kur);
		ft_memcpy(out + pos->kur, u.c, size);
		pos->kur += size;
		pos->len += size;
		out[0] ? gsh_r_redraw_line(out, pos, size, 1) : 0;
		if (gsh_r_check_pos(pos))
		{
			if (pos->kur == pos->len)
				tputs(tgetstr("do", 0), 1, ft_putint);
			tputs(tgetstr("cr", 0), 1, ft_putint);
		}
	}
	else if (u.d == 127)
		gsh_r_backspace(out, pos);
}

int			gsh_r_ctrl_char(char c, char *out, t_pos *pos)
{
	if (c == 10 || (c == 4 && *out) || c == 3)
	{
		gsh_r_home_end('F', pos);
		c == 3 ? ft_bzero(out, LINE_SIZE) : 0;
		write(0, "\n", 1);
		return (1);
	}
	else if (c == 4 && !*out)
	{
		gsh_r_home_end('F', pos);
		write(0, "\n", 1);
		return (0);
	}
	else if (c == 12)
	{
		tputs(tgetstr("cl", 0), 1, ft_putint);
		gsh_prompt(1);
		tputs(out, 1, ft_putint);
		pos->kur = pos->len;
	}
	else if (c == 9)
		gsh_r_autocomplete(out, pos);
	return (2);
}
