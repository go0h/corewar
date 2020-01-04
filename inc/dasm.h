/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/09 00:37:08 by vmormont          #+#    #+#             */
/*   Updated: 2020/01/04 16:15:50 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef DASM_H
# define DASM_H

# include "op.h"
# include "op_struct.h"
# include "libft.h"
# include "libftprintf.h"
# include <stdio.h>

/*
** Error managment
*/

# define READ_ERROR			301
# define ERROR_PROG_SIZE	302
# define ERROR_COMMENT_SIZE	303
# define MAGIC_ERROR		304

/*
** Additional constants for operation of the disassembler
*/

# define BYTE_SIZE	8
# define NUM_ARG	3
# define REG_DASM	1
# define IND_DASM	3

# define START		0
# define EXTENSION	4

/*
**	Disassemble
*/

void					disassemble(char *filename);

/*
**	Read functions
*/

void					read_cor_head(int fd, t_header *head);

/*
**	Print functions
*/

void					print_name_comment_to_fd(char *name, char *comment,\
												int fd_out);

void					print_code(int fd, int fd_out);

/*
**	Utilits
*/

void					print_usage(void);

void					ft_exit_dasm(int error);

t_bool					is_filename_extension(char *filename, char *extension);

char					*get_s_filename(char *arg);

int						reverse_bits(int num, char full_bit);

char					get_num_type(char num, int num_arg);

int						get_num(int fd, size_t t_size, char type);

#endif
