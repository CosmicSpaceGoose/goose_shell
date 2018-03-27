/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 14:58:32 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/05 14:59:08 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_reader.h"

static int	gsh_reader_bell_chaek(char *c, t_pos *pos, char *out)
{
	if (c[0] == 27)
	{
		if (!c[1] && !out[0])
			return (1);
		else if (c[1] == '[' && (((c[2] == 'C' || c[2] == 'F' || c[2] == '3')
			&& pos->kur == pos->len) || ((c[2] == 'D' || c[2] == 'H') &&
			!(pos->kur)) || (c[2] == 'A' && !((pos->kur + pos->prompt) /
			pos->col)) || (c[2] == 'B' && !(((pos->len + pos->prompt) /
			pos->col) - ((pos->kur + pos->prompt) / pos->col)))))
			return (1);
		else if (c[1] == '\e' && c[2] == '[' && ((c[3] == 'C' && pos->kur ==
			pos->len) || (c[3] == 'D' && !(pos->kur))))
			return (1);
	}
	else if ((c[0] == 127 && !(pos->kur)) || ((c[0] != 127 &&
		(int)(ft_strlen(out) + ft_strlen(c)) > LINE_SIZE)))
		return (1);
	return (0);
}

static int	gsh_reader_cycle(int i, char *out, size_t prompt)
{
	char	c[9];
	t_pos	*pos;

	pos = (t_pos *)malloc(sizeof(t_pos));
	pos->kur = 0;
	pos->len = 0;
	pos->prompt = prompt;
	pos->col = (size_t)tgetnum("co");
	while ((i = read(0, c, 8)))
	{
		c[i] = '\0';
		if (gsh_reader_bell_chaek(c, pos, out))
			write(0, "\a", 1);
		else if (c[0] > 31 || c[0] == 127)
			gsh_r_normal_sym(c, out, pos, ft_strlen(c));
		else if (c[0] < 32 && c[0] > -1 && c[0] != 27)
		{
			if ((i = gsh_r_ctrl_char(c, out, pos)) < 2)
				break ;
		}
		else if (c[0] == 27)
			gsh_r_esc_seq(c, out, pos);
		ft_dprintf(2, "%zu:%zu\n", pos->kur, pos->len);
	}
	free(pos);
	return (i);
}

int			gsh_reader(char **line, size_t prompt)
{
	struct termios	tstr;
	struct termios	copy;
	char			out[LINE_SIZE];
	int				i;

	tcgetattr(0, &tstr);
	tgetent(0, getenv("TERM"));
	copy = tstr;
	tstr.c_lflag ^= ICANON;
	tstr.c_lflag ^= ECHO;
	tstr.c_lflag ^= ISIG;
	ft_bzero((void *)out, LINE_SIZE);
	tcsetattr(0, TCSAFLUSH, &tstr);
	gsh_r_history_bucket(0, 0);
	if ((i = gsh_reader_cycle(0, out, prompt)))
		*line = ft_strdup(out);
	gsh_r_history_bucket(1, *line);
	tcsetattr(0, TCSANOW, &copy);
	return (i);
}
