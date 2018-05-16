/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_graphics.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/17 14:25:01 by dlinkin           #+#    #+#             */
/*   Updated: 2018/01/17 14:25:03 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSH_GRAPHICS_H
# define GSH_GRAPHICS_H

/*
**	must be equal with BLTN_NUM in gsh_builtins.h
*/

# define BLTN_NUM 12

const char			*g_help[11] = {
	" - print some text in terminal",
	" - change working directory",
	" - env managment / run program",
	" - set environment variable",
	" - delete environment variable",
	" - exit goose_shell",
	" - print this help page",
	" - modificate shell history",
	" - set local variable",
	" - delete local variable",
	0
};

#endif
