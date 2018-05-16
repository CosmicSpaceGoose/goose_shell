/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gsh_options.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dlinkin <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/16 13:20:16 by dlinkin           #+#    #+#             */
/*   Updated: 2018/05/16 13:20:17 by dlinkin          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GSH_OPTIONS_H
# define GSH_OPTIONS_H

# include "libftprintf.h"

# define OPT_NUM 33

uint32_t	g_opt_n;
const char	*g_opt[OPT_NUM] = {
	"appnd_hist_file",
	"comp_empty_line",
	"history_use",
	"history_load",
	"history_save",
	"output_graphics",
	"upd_hash_table",
	"use_hash_table",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	"",
	0
};

#endif
