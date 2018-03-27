/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_parcer_plus_plus.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/21 18:04:00 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/21 18:04:02 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "gsh_parcer.h"

static int	gsh_read_var(char **cmd, char **ln, int *k)
{
	static char	env[NAMESIZE];
	char		*ptr;
	int			old;
	int			i;

	i = 0;
	while (**ln && **ln != 32 && **ln != 9 && **ln != 92 && **ln != 47
		&& **ln != 59 && **ln != 34)
	{
		env[i++] = **ln;
		if (*(*ln + 1) != '$')
			(*ln)++;
		else
			break ;
	}
	env[i] = '\0';
	ptr = gsh_get_env(env);
	old = *k;
	*k -= ft_strlen(env) + 1 - ft_strlen(ptr);
	*cmd = (char *)ft_realloc(*k, old, (void *)*cmd);
	if (ptr)
		ft_strcat(*cmd, ptr);
	return (ft_strlen(*cmd));
}

static char	gsh_pa_ctrl_char(char c)
{
	char r;

	r = c;
	c == 'a' ? (r = '\a') : 0;
	c == 'b' ? (r = '\b') : 0;
	c == 't' ? (r = '\t') : 0;
	c == 'n' ? (r = '\n') : 0;
	c == 'v' ? (r = '\v') : 0;
	c == 'f' ? (r = '\f') : 0;
	c == 'r' ? (r = '\r') : 0;
	c == 'e' ? (r = '\e') : 0;
	return (r);
}

static void	gsh_split_nrm_char(char *out, char **ln, char *c, int *i)
{
	if (**ln == 92)
	{
		(*ln)++;
		if (*c == '\"' || *c == '\'')
			out[*i] = gsh_pa_ctrl_char(**ln);
		else
			out[*i] = **ln;
	}
	else if (**ln == '\"' || **ln == '\'')
	{
		if (*c)
		{
			if (**ln != *c)
				out[*i] = **ln;
			else
				*c = 0;
		}
		else
		{
			*c = **ln;
			(*i)--;
		}
	}
	else
		out[*i] = **ln;
}

char		*gsh_split_red(char *ln, int k, int i)
{
	char c;
	char *out;

	out = (char *)malloc(sizeof(char) * (k + 1));
	c = 0;
	while (i < k)
	{
		while (c != '\'' && c != '\"' && (*ln == 32 || *ln == 9))
			ln++;
		if (c != '\'' && *ln == 36 && *(ln + 1) != 32 && *(ln + 1) != 9
			&& *(ln + 1) != 0 && (ln++))
		{
			out[i] = '\0';
			i = gsh_read_var(&out, &ln, &k) - 1;
		}
		else if (!c && *ln == '~' && (*(ln - 1) == 32 || *(ln - 1) == 9 ||
			*(ln - 1) == 60 || *(ln - 1) == 62 || *(ln - 1) == '&'))
			i = gsh_split_tilde(&out, &k) - 1;
		else
			gsh_split_nrm_char(out, &ln, &c, &i);
		ln++;
		i++;
	}
	out[i] = '\0';
	return (out);
}

char		*gsh_split_word(char *ln, int k, int i)
{
	char c;
	char *out;

	out = (char *)malloc(sizeof(char) * (k + 1));
	c = 0;
	while (i < k)
	{
		if (c != '\'' && *ln == 36 && *(ln + 1) != 32 && *(ln + 1) != 9
			&& *(ln + 1) != 0 && (ln++))
		{
			out[i] = '\0';
			i = gsh_read_var(&out, &ln, &k) - 1;
		}
		else if (!i && !c && *ln == '~')
			i = gsh_split_tilde(&out, &k) - 1;
		else
			gsh_split_nrm_char(out, &ln, &c, &i);
		ln++;
		i++;
	}
	out[i] = '\0';
	return (out);
}
