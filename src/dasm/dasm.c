/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   dasm.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: astripeb <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/13 21:53:36 by vmormont          #+#    #+#             */
/*   Updated: 2020/01/04 16:18:37 by astripeb         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "dasm.h"

extern t_op g_op_tab[];

void			read_cor_head(int fd, t_header *head)
{
	if ((unsigned long)read(fd, (void *)head, sizeof(int) + PROG_NAME_LENGTH)\
				< (sizeof(int) + PROG_NAME_LENGTH))
		ft_exit_dasm(READ_ERROR);
	if ((head->magic = reverse_bits(head->magic, 1)) != COREWAR_EXEC_MAGIC)
		ft_exit_dasm(MAGIC_ERROR);
	lseek(fd, sizeof(int), SEEK_CUR);
	if ((unsigned long)read(fd, &head->prog_size, sizeof(int) +\
	COMMENT_LENGTH) < (sizeof(int) + COMMENT_LENGTH))
		ft_exit_dasm(ERROR_COMMENT_SIZE);
	lseek(fd, sizeof(int), SEEK_CUR);
	if ((head->prog_size = reverse_bits(head->prog_size, 1)) >\
				CHAMP_MAX_SIZE)
		ft_exit_dasm(ERROR_PROG_SIZE);
}

void			disassemble(char *filename)
{
	t_header	head;
	char		*name;
	int			fd_in;
	int			fd_out;

	if (!(name = get_s_filename(filename)))
		ft_exit_dasm(MALLOC_FAILURE);
	if ((fd_in = open(filename, O_RDONLY)) <= 0)
		ft_exit_dasm(UNDEFINED);
	if ((fd_out = open(name, O_RDWR | O_CREAT | O_TRUNC, S_IRWXU)) <= 0)
		ft_exit_dasm(UNDEFINED);
	read_cor_head(fd_in, &head);
	print_name_comment_to_fd(head.prog_name, head.comment, fd_out);
	print_code(fd_in, fd_out);
	ft_printf("{green}SUCCESS: writing output to file: %s\n{eoc}", name);
	free(name);
	close(fd_in);
	close(fd_out);
}
