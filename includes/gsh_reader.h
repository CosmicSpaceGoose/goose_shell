/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_reader.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/23 13:11:37 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/21 12:13:41 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSH_READER_H
# define GSH_READER_H

# include "libftprintf.h"
# include <signal.h>
# include <sys/ioctl.h>
# include <termcap.h>
# include <termios.h>

# define LINE_SIZE 4096
# define SRCH_BUF_SIZE 1024

/*
**	gsh_r_history_bucket mod:
*/

# define PGDWN 3
# define PGUP 2
# define ADD 1
# define CREATE 0
# define ERASE -1
# define RETURN -2
# define DELONE -3

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
	unsigned		no;
}				t_hist;

typedef union	u_ych
{
	char		c[9];
	uintmax_t	d;
}				t_ych;

char			g_buffer[LINE_SIZE];
int				g_srch_md;
char			g_srch_buf[SRCH_BUF_SIZE];
unsigned		g_hst_sz;

/*
**	KEYCODES
*/

# define K_ARRW_LFT 4479771
# define K_ARRW_RGHT 4414235
# define K_ARRW_UP 4283163
# define K_ARRW_DWN 4348699
# define K_PG_UP 2117425947
# define K_PG_DWN 2117491483
# define K_DEL 2117294875
# define K_ALT_LFT 1146821403
# define K_ALT_RGHT 1130044187
# define K_HOME 4741915
# define K_END 4610843
# define K_SHFT_TAB 5921563
# define K_SHFT_UP 71683997260571
# define K_SHFT_DWN 72783508888347
# define K_SHFT_RGHT 73883020516123
# define K_SHFT_LFT 74982532143899
# define K_SHFT_ALT_UP 18348861490813723
# define K_SHFT_ALT_DWN 18630336467524379
# define K_SHFT_ALT_RGHT 18911811444235035
# define K_SHFT_ALT_LFT 19193286420945691

int				ft_putint(int c);
int				get_max_name(t_list *lst);
char			*gsh_get_env(char *name);
size_t			gsh_prompt(int mod);
void			gsh_r_autocomplete(char *out, t_pos *pos);
t_hist			*gsh_r_browse_history(int mod, t_hist **hist, char *str);
int				gsh_r_ctrl_char(char c, char *out, t_pos *pos);
t_hist			*gsh_r_erase_elem(t_hist *hist, unsigned num);
void			gsh_r_esc_seq(t_ych u, char *out, t_pos *pos);
t_hist			*gsh_r_history_bucket(int mod, char *str);
void			gsh_r_home_end_tab(char c, char *out, t_pos *pos);
void			gsh_r_prnt_char(t_ych u, char *out, t_pos *pos, size_t size);
void			gsh_r_redraw_line(char *out, t_pos *pos, size_t size, int mod);
t_hist			*gsh_r_remove_history(t_hist *hist);
char			*gsh_r_history_replace_mark(char *line, int k);
void			gsh_r_search(t_ych u, char *out, t_pos *pos);
void			gsh_r_shift_left(t_pos *pos);
void			gsh_r_shift_right(t_pos *pos);
void			gsh_r_signal(int signo);
void			gsh_r_cut_copy_paste(t_ych u, char *out, t_pos *pos);
void			gogo_filename(char *str, size_t len, t_pos *pos, char *out);
void			reprint(t_list *lst, char *out, t_pos *pos, size_t len);
void			rewind_cursor(size_t len, t_pos *pos);
void			sum_save_function_for_winsize(int mod, t_pos *pos);

#endif
