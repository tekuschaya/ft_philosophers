/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_three.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/19 09:40:09 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 21:42:25 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_THREE_H
# define PHILO_THREE_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>
# include <signal.h>

typedef struct	s_param
{
	uint64_t	die;
	uint64_t	eat;
	uint64_t	sleep;
	uint64_t	last_eat;
	uint64_t	start;
	int			amount;
	int			time;
	int			id;
	int			end;
	int			count_eat;
	pthread_t	thread;
	sem_t		*sem_forks;
	sem_t		*sem_write;
	sem_t		*sem_check_die;
	sem_t		*sem_check_eat;
	sem_t		**sem_eat;
	sem_t		**sem_protect;
	pid_t		*pid;
}				t_param;

int				parse_param(int i, char *s, t_param *phil);
int				print_error(char *s);
int				take_fork(t_param *phil);
int				to_sleep_and_think(t_param *phil);
int				to_eat(t_param *phil);
int				write_message(t_param *phil, char *s);
int				init_struct(t_param *phil, int arg);
int				clear_struct(t_param *phil);
int				ft_strlen(char *s);
void			ft_putstr(char *s);
void			ft_putnbr(int n);
void			ft_putchar(char c);
void			*check_eat(void *arg);
uint64_t		get_time(void);
sem_t			*sem_create(char *name, int value);

#endif
