/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 13:11:37 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/23 13:11:38 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSH_READER_H
# define GSH_READER_H

# include "libftprintf.h"
# include <termcap.h>
# include <termios.h>

# define LINE_SIZE 4096

typedef struct	s_pos
{
	size_t		kur;
	size_t		len;
	size_t		prompt;
	size_t		col;
}				t_pos;

typedef struct	s_hist
{
	char			*str;
	char			*tmp;
	struct s_hist	*prv;
	struct s_hist	*nxt;
}				t_hist;

void			gsh_r_esc_seq(char *c, char *out, t_pos *pos);
int				ft_putint(int c);
void			gsh_r_redraw_line(char *out, t_pos *pos, size_t size);
int				gsh_r_check_pos(t_pos *pos);
int				gsh_r_ctrl_char(char *c, char *out, t_pos *pos);
void			gsh_r_normal_sym(char *c, char *out, t_pos *pos, size_t size);
void			gsh_r_home_end(char c, t_pos *pos);
size_t			gsh_prompt(int mod);
void			gsh_r_shift_left(t_pos *pos);
void			gsh_r_shift_right(t_pos *pos);
char	*gsh_r_history_bucket(int mod, char *str);

#endif
