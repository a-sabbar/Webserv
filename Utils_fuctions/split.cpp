/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   split.cpp                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: asabbar <asabbar@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/12/25 18:01:04 by asabbar           #+#    #+#             */
/*   Updated: 2022/12/25 18:05:22 by asabbar          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */


#include "../includes/Webserv.hpp"

static int	words_count(std::string s, char c)
{
	int	i;
	int	words;

	i = 0;
	words = 0;
	while (s[i] == c && s[i])
		i++;
	while (s[i])
	{
		if (i == 0 || s[i - 1] == c)
		{
			if (s[i] != c && s[i] != '\0')
				words++;
		}
		i++;
	}
	return (words);
}

static void	move_word(std::string from, std::string to, int start, int j)
{
	int	a;

	a = 0;
	while (j > 0)
	{
		to[a] = from[start];
		a++;
		start++;
		j--;
	}
	to[a] = '\0';
}

static void	ft_free(std::string *p, int a)
{
	while (a >= 0)
		free(p[--a]);
	free(p);
}

static void	ft_mallocnmove(std::string *p, char const *s, char c)
{
	int		i;
	int		len;
	int		a;

	i = 0;
	len = 0;
	a = 0;
	while (s[i])
	{
		len = 0;
		while (s[i] == c)
			i++;
		while (s[i + len] != c && s[i + len] != '\0')
			len++;
		if (len != 0)
		{
			p[a] = (std::string )malloc(len + 1);
			if (p[a] == NULL)
				ft_free(p, a);
			move_word((std::string )s, p[a], i, len);
			a++;
		}
		i = i + len;
	}
}

char	**ft_split(char const *s, char c)
{
	int		i;
	int		len;
	char	**p;

	i = 0;
	if (!s)
		return (NULL);
	len = words_count((std::string )s, c);
	p = (std::string *)malloc(sizeof(std::string ) * (len + 1));
	if (p == NULL)
		return (NULL);
	ft_mallocnmove(p, s, c);
	p[len] = NULL;
	return (p);
}