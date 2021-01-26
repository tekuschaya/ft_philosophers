/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 12:56:51 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 21:38:01 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_two.h"

sem_t							*sem_create(char *name, int value)
{
	sem_unlink(name);
	return (sem_open(name, O_CREAT, 0666, value));
}

int								init_struct(t_param *phil, int arg)
{
	int i;

	i = 0;
	phil->sem_forks = sem_create("fork", phil->amount);
	phil->sem_write = sem_create("write", 1);
	phil->sem_end = sem_create("end", 0);
	if (!(phil->sem_protect = (sem_t**)malloc(sizeof(sem_t*) * phil->amount)))
	{
		print_error("Memory is not allocated\n");
		return (1);
	}
	while (i < phil->amount)
		phil->sem_protect[i++] = sem_create("protect", 1);
	phil->start = get_time();
	phil->check_time = 0;
	phil->end = 0;
	if (arg == 5)
		phil->time = 0;
	return (0);
}

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
