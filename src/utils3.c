/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils3.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ale-sain <ale-sain@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/16 18:55:41 by ale-sain          #+#    #+#             */
/*   Updated: 2022/12/21 00:38:45 by ale-sain         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "pipex.h"

static char	**free_tab(char **tab, int j)
{
	int	i;

	i = 0;
	while (i < j)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
	return (NULL);
}

static int	count_words(const char *str, char c)
{
	int	i;
	int	nb;
	int	trigger;

	i = 0;
	trigger = 0;
	nb = 0;
	while (str[i])
	{
		if (str[i] != c && trigger == 0)
		{
			trigger = 1;
			nb++;
		}
		else if (str[i] == c)
			trigger = 0;
		i++;
	}
	return (nb);
}

static int	length_words(const char *str, char c)
{
	int	i;

	i = 0;
	while ((str[i] != c && str[i]) || (str[i] != c && c == 0))
		i++;
	return (i);
}

static char	**splitting(char **tab, char const *s, char c)
{
	int	k;
	int	j;
	int	i;

	i = 0;
	j = 0;
	while (s[i])
	{
		if (s[i] != c)
		{
			tab[j] = malloc(sizeof(char) * (length_words(&s[i], c) + 1));
			if (!tab)
				return (free_tab(tab, j));
			k = 0;
			while (s[i] != c && s[i])
				tab[j][k++] = s[i++];
			tab[j][k] = '\0';
			j++;
		}
		else
			i++;
	}
	tab[j] = 0;
	return (tab);
}

char	**ft_split(char const *s, char c)
{
	char	**tab;

	if (count_words(s, c) == 0)
		return (0);
	if (s[0] == ' ' || s[ft_strlen(s) -1] == ' ')
		return (0);
	tab = (char **) malloc(sizeof(char *) * (count_words(s, c) + 1));
	if (!tab)
		return (NULL);
	return (splitting(tab, s, c));
}
