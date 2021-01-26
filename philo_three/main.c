/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/16 13:05:29 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/20 08:57:06 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo_three.h"

void	*check_state(void *arg)
{
	t_param	*phil;

	phil = (t_param*)arg;
	while (1)
	{
		sem_wait(phil->sem_protect[phil->id]);
		if (get_time() > phil->last_eat + phil->die)
		{
			sem_wait(phil->sem_write);
			ft_putnbr(get_time() - phil->start);
			ft_putchar('\t');
			ft_putnbr(phil->id + 1);
			ft_putstr(" died\n");
			phil->end = 1;
			sem_post(phil->sem_check_die);
			break ;
		}
		sem_post(phil->sem_protect[phil->id]);
	}
	return (NULL);
}

void	*check_eat(void *arg)
{
	t_param	*phil;
	int		i;

	phil = (t_param*)arg;
	i = 0;
	while (i < phil->amount)
	{
		sem_wait(phil->sem_eat[i]);
		i++;
	}
	sem_wait(phil->sem_write);
	ft_putstr("All the philosophers have eaten\n");
	sem_post(phil->sem_check_die);
	return (NULL);
}

void	doing_things(t_param *phil)
{
	pthread_t	thread;

	phil->last_eat = phil->start;
	if (pthread_create(&thread, NULL, check_state, phil) != 0)
		print_error("Error. Can't create thread\n");
	pthread_detach(thread);
	while (1)
	{
		if (take_fork(phil))
			break ;
		if (to_eat(phil))
			break ;
		if (to_sleep_and_think(phil))
			break ;
	}
}

void	create_process(t_param *phil)
{
	int	i;

	i = 0;
	phil->start = get_time();
	while (i < phil->amount)
	{
		phil->id = i;
		phil->pid[i] = fork();
		if (phil->pid[i] < 0)
			print_error("Fork error\n");
		else if (phil->pid[i] == 0)
		{
			doing_things(phil);
			exit(0);
		}
		usleep(100);
		i++;
	}
}

int		main(int argc, char **argv)
{
	int			i;
	t_param		phil;
	pthread_t	thread;

	i = 1;
	if (argc < 5 || argc > 6)
		return (print_error("Incorrect number of arguments\n"));
	while (i < argc)
	{
		if (parse_param(i, argv[i], &phil))
			return (0);
		i++;
	}
	if (init_struct(&phil, argc))
		return (1);
	if (phil.time)
	{
		if (pthread_create(&thread, NULL, check_eat, &phil) != 0)
			print_error("Error. Can't create thread\n");
		pthread_detach(thread);
	}
	create_process(&phil);
	sem_wait(phil.sem_check_die);
	clear_struct(&phil);
	return (0);
}
