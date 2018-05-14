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
# include <signal.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <sys/types.h>
# include <unistd.h>
# include "libftprintf.h"
# include "get_next_line.h"
# include "gsh_reader.h"

# define BUFSIZE 1024
# define NAMESIZE 1024
# define TIME 50000

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

typedef struct	s_ok
{
	char		*str;
	int			tok;
}				t_ok;

typedef struct	s_fptr
{
	const char	*name;
	int			(*func)(char **av);
}				t_fptr;

typedef struct	s_redir
{
	char		io;
	int			old;
	int			new;
	int			amp;
	int			flgs;
	char		*ptr;
	int			fd;
}				t_redir;

typedef struct	s_orba
{
	char		tok;
	char		**cmd;
	t_redir		**red;
}				t_orba;

char			**gsh_bucket(int mod, char **in);
void			gsh_end(void);
int				gsh_execute(char *cmd, char **av);
int				gsh_exit_status(int status, char *name);
char			*gsh_get_env(char *name);
int				gsh_get_path_name(char *out, char *path, char *name);
void			gsh_h_init_history(char *str);
int				gsh_init(void);
int				gsh_launch_cmnd(char *cmd, char **av);
int				gsh_os_cmd(char **cmd, char *path);
t_orba			**gsh_parcer(t_ok **lines);
int				gsh_reader(char **line, size_t prompt);
int				gsh_seek(t_orba *zee, int *pipes, int *fds);
t_ok			**gsh_pc_lines(char *line);
int				gsh_pc_validate(t_ok **in);
void			gsh_pre_launch(t_ok **lines);
void			gsh_std_save_restore(int mod);
//void			gsh_readmoar_atzero(char **line);
void			gsh_cycle(t_orba **z, int *pps, int *fds, int *cp);
int				gsh_make_sum_redir(t_redir **red);
void			gsh_open_close_pipes(int **fds, int **cp, int i, int mod);
void			gsh_open_files(t_orba **z);
void			gsh_close_files(t_orba *z, int *pps);

/*
**		builtins
*/

int				env_read_flags(char ***av, char *c, char *path);
void			exit_draw(void);
int				gsh_builtin_cmd(char **cmd);
int				gsh_cd(char **av);
int				gsh_echo(char **av);
int				gsh_env(char **av);
int				gsh_exit(char **av);
int				gsh_help(char **av);
int				gsh_history(char **av);
void			gsh_h_add_record(void);
int				gsh_h_erase_elem(char *str);
void			gsh_h_read_history(char *str);
void			gsh_h_show_without_add(char **av);
int				gsh_h_usage(int err);
int				gsh_list_env(void);
size_t			gsh_prompt(int mod);
int				gsh_set(char **av);
int				gsh_setenv(char **av);
int				gsh_unset(char **av);
int				gsh_unsetenv(char **av);
void			gsh_write_head(void);
void			set_add_env(char *name, char *value, int mod);
int				set_brwse_env(char *name, int mod);

//////////////////////////////////
# define P(X) write(2, #X, 1);
//////////////////////////////////

#endif
