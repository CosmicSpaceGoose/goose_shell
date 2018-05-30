/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_core.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/15 16:43:27 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/15 16:43:29 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSH_CORE_H
# define GSH_CORE_H

# include <dirent.h>
# include <fcntl.h>
# include <limits.h>
# include <pwd.h>
# include <termcap.h>
# include <termios.h>
# include <signal.h>
# include <sys/ioctl.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include "libftprintf.h"
# include "get_next_line.h"

# define BUFSIZE 1024
# define NAMESIZE 1024
# define TABLE_SIZE 50000
# define LINE_SIZE 4096
# define SRCH_BUF_SIZE 1024

/*
**		colors
*/
# define BLK "\e[30m"
# define RED "\e[31m"
# define GRN "\e[32m"
# define YLW "\e[33m"
# define BLU "\e[34m"
# define MGN "\e[35m"
# define CYN "\e[36m"
# define WHT "\e[37m"
# define NON "\e[0m"

/*
**	gsh_std_save_restore: mod variable
*/

# define SAVE 1
# define RESTORE 0

/*
**	pipeline
*/

# define BEGIN_PPL 1
# define MIDDLE_PPL 2
# define END_PPL 3

/*
**	gsh_bucket: mod variable
*/

# define RETURN_ENV 0
# define RETURN_SH 2
# define SAVE_ENV 4
# define SAVE_SH 6
# define FREE_ENV 3
# define FREE_SH 5
# define FREE_ALL 7

/*
**	set_add_env: mod variable, must be equal RETURN_ENV and RETURN_SH
*/

# define ENV 0
# define SH 2

/*
**	default value for g_opt_n in gsh_options.h and options flags
*/

# define DEFAULT_VALUE 255
# define APPND_HIST 1
# define COMPL_EMPTY 2
# define USE_HIST 4
# define LOAD_HIST 8
# define SAVE_HIST 16
# define GRAPHICS 32
# define UPD_HASH 64
# define USE_HASH 128

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

typedef struct		s_ok
{
	char			*str;
	int				tok;
}					t_ok;

typedef struct		s_fptr
{
	const char		*name;
	int				(*func)(char **av);
}					t_fptr;

typedef struct		s_redir
{
	char			io;
	int				old;
	int				new;
	int				amp;
	int				flgs;
	char			*ptr;
	int				fd;
}					t_redir;

typedef struct		s_orba
{
	char			tok;
	char			**cmd;
	t_redir			**red;
}					t_orba;

typedef struct		s_pos
{
	size_t			kur;
	size_t			len;
	size_t			prompt;
	size_t			col;
}					t_pos;

typedef struct		s_hist
{
	char			*str;
	char			*tmp;
	struct s_hist	*prv;
	struct s_hist	*nxt;
	unsigned		no;
}					t_hist;

typedef union		u_ych
{
	char			c[9];
	uintmax_t		d;
}					t_ych;

extern const t_fptr	g_builtin[];
extern const char	*g_help[];
extern const char	*g_sig[];
extern const char	*g_opt[];
char				***g_arr;
uint32_t			g_opt_n;
char				g_buffer[LINE_SIZE];
int					g_srch_md;
char				g_srch_buf[SRCH_BUF_SIZE];
unsigned			g_hst_sz;
int					g_pipe;

char				**gsh_bucket(int mod, char **in);
void				gsh_end(void);
int					gsh_execute(char *cmd, char **av);
int					gsh_exit_status(int status, char *name);
char				*gsh_get_env(char *name);
int					gsh_get_path_name(char *out, char *path, char *name);
void				gsh_h_init_hist(char *str);
int					gsh_init(int i);
int					gsh_launch_cmnd(char *cmd, char **av);
int					gsh_os_cmd(char **cmd, char *path);
t_orba				**gsh_parcer(t_ok **lines);
int					gsh_reader(char **line, size_t prompt);
int					gsh_seek(t_orba *zee, int *pipes, int *fds);
t_ok				**gsh_pc_lines(char *line);
int					gsh_pc_validate(t_ok **in);
void				gsh_pre_launch(t_ok **lines);
void				gsh_std_save_restore(int mod);
void				gsh_cycle(t_orba **z, int *pps, int *fds, int *cp);
int					gsh_make_sum_redir(t_redir **red);
void				gsh_open_close_pipes(int **fds, int **cp, int i, int mod);
void				gsh_open_files(t_orba **z);
void				gsh_close_files(t_orba *z, int *pps);
int					gsh_write_some_files(t_redir **red, int i);
void				gsh_init_hash_table(void);
char				*gsh_hash_search(char *str);
void				gsh_delete_hash_table(void);
int					gsh_chaek_extr(char *line);
void				gsh_extraction(char **line, int err);

/*
**		builtins
*/

int					env_read_flags(char ***av, char *c, char *path);
void				exit_draw(void);
int					gsh_builtin_cmd(char **cmd);
int					gsh_cd(char **av);
int					gsh_echo(char **av);
int					gsh_env(char **av);
int					gsh_exit(char **av);
int					gsh_help(char **av);
int					gsh_history(char **av);
void				gsh_h_add_record(void);
int					gsh_h_erase_elem(char *str);
void				gsh_h_read_history(char *str);
void				gsh_h_show_without_add(char **av);
int					gsh_h_usage(int err);
int					gsh_list_env(void);
size_t				gsh_prompt(int mod);
int					gsh_set(char **av);
int					gsh_setenv(char **av);
int					gsh_setopt(char **av);
int					gsh_unset(char **av);
int					gsh_unsetenv(char **av);
void				gsh_write_head(void);
void				set_add_env(char *name, char *value, int mod);
int					set_brwse_env(char *name, int mod);

/*
**		parcer
*/

char				*gsh_get_env(char *name);
int					gsh_split_tilde(char **cmd, int *k);
char				gsh_sp_char(char c);
char				*gsh_split_word(char *ln, int k, int i);
char				*gsh_split_red(char *ln, int k, int i);
void				gsh_parcer_part(char *ln, char **cmd, char **red, int *c);
t_redir				**gsh_parce_redir(char **red);
t_orba				*gsh_parce_apozh(char *line);

/*
**		reader
*/

int					ft_putint(int c);
int					get_max_name(t_list *lst);
char				*gsh_get_env(char *name);
size_t				gsh_prompt(int mod);
void				gsh_r_autocomplete(char *out, t_pos *pos);
t_hist				*gsh_r_browse_history(int mod, t_hist **hist, char *str);
int					gsh_r_ctrl_char(char c, char *out, t_pos *pos);
t_hist				*gsh_r_erase_elem(t_hist *hist, unsigned num);
void				gsh_r_esc_seq(t_ych u, char *out, t_pos *pos);
t_hist				*gsh_r_history_bucket(int mod, char *str);
void				gsh_r_home_end_tab(char c, char *out, t_pos *pos);
void				gsh_r_prnt_char(t_ych u, char *out, t_pos *pos,
	size_t size);
void				gsh_r_redraw_line(char *out, t_pos *pos, size_t size,
	int mod);
t_hist				*gsh_r_remove_history(t_hist *hist);
char				*gsh_r_history_replace_mark(char *line, int k);
void				gsh_r_search(t_ych u, char *out, t_pos *pos);
void				gsh_r_shift_left(t_pos *pos);
void				gsh_r_shift_right(t_pos *pos);
void				gsh_r_signal(int signo);
void				gsh_r_cut_copy_paste(t_ych u, char *out, t_pos *pos);
void				gogo_filename(char *str, size_t len, t_pos *pos, char *out);
void				reprint(t_list *lst, char *out, t_pos *pos, size_t len);
void				rewind_cursor(size_t len, t_pos *pos);
void				sum_save_function_for_winsize(int mod, t_pos *pos);

#endif
