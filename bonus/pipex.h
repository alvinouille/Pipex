/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pipex.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 12:01:33 by ale-sain          #+#    #+#             */
/*   Updated: 2023/01/09 18:52:32 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PIPEX_H
# define PIPEX_H

# include <sys/types.h>
# include <sys/stat.h>
# include <fcntl.h>
# include <unistd.h>
# include <sys/wait.h>
# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include "get_next_line.h"

typedef struct s_list
{
	char			**env;
	char			**e;
	char			**cmd;
	char			*path;
	char			*infile;
	char			*outfile;
	long			pid;
	int				pipefd[2];
	char			*option;
	struct s_list	*head;
	struct s_list	*next;
}	t_list;

//		TRASHING
void	cleanator(char **tab);
void	closing(int pipefd[2], int file);
void	close_all(t_list *cmd);
void	exit_error(t_list *cmd, char *file, void (*cleanator)(char **),
			t_list *head);
int		ft_out(int *status);

//		UTILS
void	ft_putchar_fd(char c, int fd);
void	ft_putendl_fd(char *s, int fd);
void	ft_putstr_fd(char *s, int fd);
size_t	ft_strlen(const char *s);
char	*ft_strnstr(const char *big, const char *little, size_t len);
void	ft_bzero(void *s, size_t n);
void	*ft_calloc(size_t nmemb, size_t size);
char	*ft_strchr(const char *s, int c);
int		ft_strncmp(const char *s1, const char *s2, size_t n);
char	*ft_strjoin(char const *s1, char const *s2);
char	**ft_split(char const *s, char c);
char	*ft_strdup(const char *s);
t_list	*ft_lstnew(int ac, char **av, char **env, int i);
t_list	*ft_lstlast(t_list *lst);
t_list	*ft_lstadd_back(t_list **lst, t_list *new);
void	ft_lstdelone(t_list *list, void (*cleanator)(char **));
void	ft_lstclear(t_list **list, void (*cleanator)(char **));
char	*building_path(char *cmd, char **e);

//		BONUS
void	option(t_list *cmd);
// void	middle(t_list *cmd, void (*cleanator)(char **), t_list *head);
void	mid(t_list *cmd, void (*cleanator)(char **), t_list *head);

//		CMD
char	**split_env(char **env);
char	*ft_whereis(char *cmd, char **e);
void	*generator_cmd(t_list **lst, int ac, char **av, char **env);
int		verif_arg(char **av, int ac);

//		PIPEX
void	first(t_list *cmd, int pipefd[2], void (*cleanator)(char **),
			t_list *head);
void	last(t_list *cmd, int pipefd[2], t_list *head,
			void (*cleanator)(char **));
int		open_file(int flag, t_list *cmd, t_list *head,
			void (*cleanator)(char**));
void	waiting_childs(t_list *cmd, int *status);
int		pipex(t_list *cmd, void (*cleanator)(char **));

#endif