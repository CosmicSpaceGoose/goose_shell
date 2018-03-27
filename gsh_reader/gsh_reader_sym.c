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

void		gsh_r_normal_sym(char *c, char *out, t_pos *pos, size_t size)
{
	if (c[0] != 127)
	{
		if (pos->kur < pos->len)
			ft_memmove(out + pos->kur + size, out + pos->kur, ft_strlen(out)
				- pos->kur);
		ft_memcpy(out + pos->kur, c, size);
		pos->kur += size;
		pos->len += size;
		out[0] ? gsh_r_redraw_line(out, pos, size) : 0;
		if (gsh_r_check_pos(pos))
		{
			if (pos->kur == pos->len)
				tputs(tgetstr("do", 0), 1, ft_putint);
			tputs(tgetstr("cr", 0), 1, ft_putint);
		}
	}
	else if (c[0] == 127)
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
		gsh_r_redraw_line(out, pos, 1);
		pos->len--;
		pos->kur--;
	}
}

int			gsh_r_ctrl_char(char *c, char *out, t_pos *pos)
{
	if (c[0] == 10 || (c[0] == 4 && *out))
	{
		gsh_r_home_end('F', pos);
		write(0, "\n", 1);
	}
	else if (c[0] == 4 && !*out)
	{
		gsh_r_home_end('F', pos);
		write(0, "\n", 1);
		return (0);
	}
	else if (c[0] == 3)
	{
		gsh_r_home_end('F', pos);
		ft_bzero(out, LINE_SIZE);
		write(0, "\n", 1);
	}
	else if (c[0] == 12)
	{
		tputs(tgetstr("cl", 0), 1, ft_putint);
		gsh_prompt(1);
		tputs(out, 1, ft_putint);
		pos->kur = pos->len;
		return (2);
	}
	else
		return (2);
	return (1);
}
