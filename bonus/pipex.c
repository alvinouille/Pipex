/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/19 14:10:53 by ale-sain          #+#    #+#             */
/*   Updated: 2023/01/09 18:51:56 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"
#include "pipex.h"

void	first(t_list *cmd, int pipefd[2], void (*cleanator)(char **),
	t_list *head)
{
	int	infile;

	cmd->pid = (long)fork();
	if (cmd->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (cmd->pid == 0)
	{
		infile = open_file(0, cmd, head, cleanator);
		dup2(infile, 0);
		dup2(pipefd[1], 1);
		close_all(head);
		close(infile);
		if (cmd->path == NULL)
			exit_error(cmd, NULL, cleanator, head);
		if (execve(cmd->path, cmd->cmd, cmd->env) == -1)
			exit_error(cmd, NULL, cleanator, head);
	}
}

void	last(t_list *cmd, int pipefd[2], t_list *head,
	void (*cleanator)(char **))
{
	int		outfile;
	t_list	*curr;

	curr = cmd->next;
	outfile = open_file(1, cmd, head, cleanator);
	curr->pid = (long)fork();
	if (curr->pid == -1)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	if (curr->pid == 0)
	{
		dup2(pipefd[0], 0);
		dup2(outfile, 1);
		close_all(head);
		close(outfile);
		if (curr->path == NULL)
			exit_error(curr, NULL, cleanator, head);
		if (execve(curr->path, curr->cmd, curr->env) == -1)
			exit_error(curr, NULL, cleanator, head);
	}
	close(outfile);
	close_all(head);
}

int	open_file(int flag, t_list *cmd, t_list *head, void (*cleanator)(char**))
{
	int	file;

	if (flag == 1)
	{
		if (cmd->option)
			file = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		else
			file = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (file == -1)
			wait(NULL);
		if (file == -1)
			exit_error(cmd, cmd->outfile, cleanator, head);
	}
	else
	{
		if (cmd->option)
			file = open("tmp", O_RDONLY);
		else
			file = open(cmd->infile, O_RDONLY);
		if (file == 0 || file == -1)
			exit_error(cmd, cmd->infile, cleanator, head);
	}
	return (file);
}

int	ft_out(int *status)
{
	if (WIFEXITED(*status))
		return (WEXITSTATUS(*status));
	else
		return (0);
}

int	pipex(t_list *cmd, void (*cleanator)(char **))
{
	int		status;
	t_list	*head;

	head = cmd;
	while (cmd->next)
	{
		if (pipe(cmd->pipefd) == -1)
		{
			perror("pipe");
			exit(EXIT_FAILURE);
		}
		cmd = cmd->next;
	}
	cmd = head;
	if (cmd->option)
		option(cmd);
	first(cmd, cmd->pipefd, cleanator, head);
	while (cmd->next->next)
	{
		mid(cmd, cleanator, head);
		cmd = cmd->next;
	}
	last(cmd, cmd->pipefd, head, cleanator);
	waiting_childs(head, &status);
	return (ft_out(&status));
}
