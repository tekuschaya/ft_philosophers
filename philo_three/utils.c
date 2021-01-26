/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   utils.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:12:47 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 22:09:20 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

int			ft_strlen(char *s)
{
	int i;

	i = 0;
	if (s)
		while (s[i])
			i++;
	return (i);
}

void		ft_putchar(char c)
{
	write(1, &c, 1);
}

void		ft_putstr(char *s)
{
	if (s)
		write(1, s, ft_strlen(s));
}

void		ft_putnbr(int n)
{
	if (n < 0)
		ft_putchar('-');
	if (n / 10 != 0)
		ft_putnbr((n < 0) ? -1 * (n / 10) : (n / 10));
	ft_putchar((n < 0) ? -1 * (n % 10) + '0' : n % 10 + '0');
}

uint64_t	get_time(void)
{
	struct timeval	tv;

	gettimeofday(&tv, NULL);
	return ((tv.tv_sec * (uint64_t)1000) + (tv.tv_usec / 1000));
}
