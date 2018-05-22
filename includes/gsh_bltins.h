/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_bltins.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/14 14:23:27 by dlinkin           #+#    #+#             */
/*   Updated: 2018/03/14 14:23:29 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSH_BLTINS_H
# define GSH_BLTINS_H

/*
**	must be equal with BLTN_NUM in gsh_graphics.h
*/

# define BLTN_NUM 12

const t_fptr	g_builtin[BLTN_NUM] = {
	{"cd", gsh_cd},
	{"echo", gsh_echo},
	{"env", gsh_env},
	{"exit", gsh_exit},
	{"help", gsh_help},
	{"history", gsh_history},
	{"set", gsh_set},
	{"setenv", gsh_setenv},
	{"setopt", gsh_setopt},
	{"unset", gsh_unset},
	{"unsetenv", gsh_unsetenv},
	{NULL, NULL}
};

#endif
