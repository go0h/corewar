/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/14 01:56:19 by vmormont          #+#    #+#             */
/*   Updated: 2020/01/04 17:28:49 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

extern t_op g_op_tab[];

void				print_name_comment_to_fd(char *name, char *comment,\
										int fd_out)
{
	ft_fprintf(fd_out, ".name \"%s\"\n", name);
	ft_fprintf(fd_out, ".comment \"%s\"\n\n", comment);
}

static void			print_ops_with_code_args(int fd, int fd_out, short op,\
					char code_args)
{
	int			i;
	int			num;

	i = 6;
	while (i >= 8 - (2 * g_op_tab[op].num_args))
	{
		if (((code_args >> i) & 3) == REG_CODE)
		{
			num = get_num(fd, T_REG, REG_CODE);
			ft_fprintf(fd_out, "r%d", num);
		}
		else if (((code_args >> i) & 3) == IND_CODE)
		{
			num = get_num(fd, IND_SIZE, IND_CODE);
			ft_fprintf(fd_out, "%hd", num);
		}
		else if (((code_args >> i) & 3) == DIR_CODE)
		{
			num = get_num(fd, g_op_tab[op].tdir_size, DIR_CODE);
			ft_fprintf(fd_out, "%%%d", num);
		}
		i != 8 - (2 * g_op_tab[op].num_args) ? ft_fprintf(fd_out, ", ") : 0;
		i -= 2;
	}
}

void				print_code(int fd, int fd_out)
{
	uint8_t			op_code;
	int				num;
	char			code_args;

	while (read(fd, (void*)&op_code, 1) > 0)
	{
		if (!op_code)
			continue;
		ft_fprintf(fd_out, "%s ", g_op_tab[op_code].name);
		if (g_op_tab[op_code].code_args)
		{
			if (read(fd, (void*)&code_args, 1) < 0)
				exit(EXIT_FAILURE);
			print_ops_with_code_args(fd, fd_out, op_code, code_args);
		}
		else
		{
			num = get_num(fd, g_op_tab[op_code].tdir_size, DIR_CODE);
			ft_fprintf(fd_out, "%%%d", num);
		}
		ft_fprintf(fd_out, "\n");
	}
}
