/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils4.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:56:43 by ale-sain          #+#    #+#             */
/*   Updated: 2022/12/21 02:13:34 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

t_list	*ft_lstnew(int ac, char **av, char **env, int i)
{
	t_list	*list;

	list = malloc(sizeof(t_list));
	if (!list)
		return (NULL);
	if (list)
	{
		list->env = env;
		list->e = split_env(env);
		list->cmd = ft_split(av[i], ' ');
		if (list->cmd)
			list->path = ft_whereis(list->cmd[0], list->e);
		else
			list->path = NULL;
		list->option = ft_strnstr(av[1], "here_doc", 9);
		if (list->option)
			list->infile = av[2];
		else
			list->infile = av[1];
		list->outfile = av[ac - 1];
		list->pid = 0;
		list->next = NULL;
	}
	return (list);
}

t_list	*ft_lstlast(t_list *lst)
{
	while (lst && lst->next)
		lst = lst->next;
	return (lst);
}

t_list	*ft_lstadd_back(t_list **lst, t_list *new)
{
	t_list	*last;

	if (*lst == NULL)
		*lst = new;
	else
	{
		if (lst && new)
		{
			last = ft_lstlast(*lst);
			last->next = new;
		}
	}
	return (*lst);
}

void	ft_lstdelone(t_list *list, void (*cleanator)(char **))
{
	static int	i;

	i = 0;
	if (list && cleanator)
	{
		list->env = NULL;
		cleanator(list->e);
		cleanator(list->cmd);
		if (list->path)
			free(list->path);
		list->infile = NULL;
		list->outfile = NULL;
		list->pid = 0;
		free(list);
	}
	i++;
}

void	ft_lstclear(t_list **list, void (*cleanator)(char **))
{
	t_list	*head;
	t_list	*body;

	if (!list || !cleanator || !(*list))
		return ;
	head = *list;
	while (head)
	{
		body = head->next;
		ft_lstdelone(head, cleanator);
		head = body;
	}
}
