/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bonus.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/21 01:14:05 by ale-sain          #+#    #+#             */
/*   Updated: 2023/01/09 19:53:32 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"
#include "get_next_line.h"

void	option(t_list *cmd)
{
	char	*str;
	int		infile;
	size_t	size;

	infile = open("tmp", O_WRONLY | O_CREAT | O_TRUNC, 0644);
	size = ft_strlen(cmd->infile);
	if (cmd->option)
	{
		ft_putstr_fd("heredoc> ", 0);
		str = get_next_line(0, 0);
		while (str && (ft_strnstr(str, cmd->infile, size) == 0
				|| size != ft_strlen(str) - 1))
		{
			ft_putstr_fd(str, infile);
			free(str);
			ft_putstr_fd("heredoc> ", 0);
			str = get_next_line(0, 0);
		}
		free(str);
		get_next_line(0, 1);
		close(infile);
	}
}

void	mid(t_list *cmd, void (*cleanator)(char **), t_list *head)
{
	t_list	*curr;

	curr = cmd->next;
	curr->pid = (long)fork();
	if (curr->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (curr->pid == 0)
	{
		dup2(cmd->pipefd[0], 0);
		dup2(curr->pipefd[1], 1);
		close_all(head);
		if (curr->path == NULL)
			exit_error(curr, NULL, cleanator, head);
		if (execve(curr->path, curr->cmd, curr->env) == -1)
			exit_error(curr, NULL, cleanator, head);
	}
}
