/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 13:23:56 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 13:24:10 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int								print_error(char *s)
{
	write(1, s, ft_strlen(s));
	return (0);
}

static unsigned long long int	ft_atoi(char *s)
{
	unsigned long long int	res;
	int						i;

	i = 0;
	res = 0;
	while ((s[i] > 8 && s[i] < 14) || s[i] == 32)
		i++;
	if (s[i] == '+' || s[i] == '-')
	{
		if (s[i] == '-' || s[i + 1] < 48 || s[i + 1] > 57)
			return (print_error("Incorrect input\n"));
		i++;
	}
	while (s[i] > 47 && s[i] < 58)
	{
		if ((res * 10 + s[i] - 48) < res)
			return (print_error("llu is overflow\n"));
		res = res * 10 + s[i] - 48;
		i++;
	}
	if (s[i] == '\0' && res)
		return (res);
	else
		return (print_error("Incorrect input\n"));
}

int								parse_param(int i, char *s, t_param *phil)
{
	unsigned long long int check;

	check = ft_atoi(s);
	if (!check)
		return (1);
	if (i == 1)
	{
		phil->amount = check;
		if (phil->amount > 32767)
		{
			print_error("Amount of philos must be < 32768\n");
			return (1);
		}
	}
	else if (i == 2)
		phil->die = check;
	else if (i == 3)
		phil->eat = check;
	else if (i == 4)
		phil->sleep = check;
	else
		phil->time = check;
	return (0);
}
