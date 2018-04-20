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

typedef struct	s_arrs
{
	char	**cmd;
	char	**red;
}				t_arrs;

typedef struct	s_tok
{
	char		*str;
	int			tok;
}				t_tok;

char			*gsh_get_env(char *name);
int				gsh_split_tilde(char **cmd, int *k);
char			gsh_sp_char(char c);
int				gsh_word(char *s, int *n, int i);
int				gsh_bldzhad(char *s, int *n, int i, int c);
char			*gsh_split_word(char *ln, int k, int i);
char			*gsh_split_red(char *ln, int k, int i);

#endif
