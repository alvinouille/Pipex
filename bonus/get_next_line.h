/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/11/18 16:34:30 by ale-sain          #+#    #+#             */
/*   Updated: 2022/12/21 02:11:16 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 5
# endif

# include <stdlib.h>
# include <unistd.h>
# include <fcntl.h>
# include "pipex.h" 

char	*ft_line(char *keep);
char	*ft_keep_memory(char *keep);
char	*ft_strjoin_modif(char *keep, char *buff);
char	*loopin(int fd, char **keep);
char	*get_next_line(int fd, int flag);

#endif
