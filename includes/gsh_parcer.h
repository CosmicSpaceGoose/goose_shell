/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_parcer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/30 14:34:59 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/30 14:35:01 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSH_PARCER_H
# define GSH_PARCER_H

# include "libftprintf.h"

# define NAMESIZE 1024

typedef struct	s_ok
{
	char		*str;
	int			tok;
}				t_ok;

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
	int			tok;
	char		**cmd;
	t_redir		**red;
}				t_orba;

char			*gsh_get_env(char *name);
int				gsh_split_tilde(char **cmd, int *k);
char			gsh_sp_char(char c);
char			*gsh_split_word(char *ln, int k, int i);
char			*gsh_split_red(char *ln, int k, int i);
void			gsh_parcer_part(char *ln, char **cmd, char **red, int *c);
t_redir			**gsh_parce_redir(char **red);
t_orba			*gsh_parce_apozh(char *line);

#endif
