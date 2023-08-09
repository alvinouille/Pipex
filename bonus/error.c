/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:53:32 by ale-sain          #+#    #+#             */
/*   Updated: 2023/01/16 15:08:17 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

void	cleanator(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			free(tab[i]);
			i++;
		}
		free(tab);
	}
}

void	closing(int pipefd[2], int file)
{
	close(pipefd[0]);
	close(pipefd[1]);
	if (file)
		close(file);
}

void	close_all(t_list *cmd)
{
	while (cmd->next)
	{
		closing(cmd->pipefd, 0);
		cmd = cmd->next;
	}
}

void	exit_error(t_list *cmd, char *file, void (*cleanator)(char **),
	t_list *head)
{
	if (file)
	{
		ft_putstr_fd(file, 2);
		perror(" ");
		close_all(head);
		ft_lstclear(&cmd->head, cleanator);
		exit(1);
	}
	else
	{
		ft_putstr_fd("pipex: command not found: ", 2);
		if (cmd->cmd)
			ft_putendl_fd(cmd->cmd[0], 2);
		ft_lstclear(&cmd->head, cleanator);
		exit (127);
	}
}

void	waiting_childs(t_list *cmd, int *status)
{
	while (cmd)
	{
		waitpid(cmd->pid, status, 0);
		cmd = cmd->next;
	}
}
