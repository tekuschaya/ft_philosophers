/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo_two.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: odhazzar <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2020/11/18 23:37:13 by odhazzar          #+#    #+#             */
/*   Updated: 2020/11/19 21:38:59 by odhazzar         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_TWO_H
# define PHILO_TWO_H

# include <unistd.h>
# include <sys/time.h>
# include <pthread.h>
# include <semaphore.h>
# include <stdlib.h>

typedef struct	s_param
{
	uint64_t	die;
	uint64_t	eat;
	uint64_t	sleep;
	uint64_t	start;
	int			amount;
	int			time;
	int			number;
	int			check_time;
	int			end;
	sem_t		*sem_forks;
	sem_t		*sem_write;
	sem_t		*sem_end;
	sem_t		**sem_protect;
}				t_param;

typedef struct	s_phil
{
	int			id;
	int			count_eat;
	int			flag;
	uint64_t	last_eat;
	uint64_t	start;
	t_param		*phil;
}				t_phil;

int				parse_param(int i, char *s, t_param *phil);
int				print_error(char *s);
int				take_fork(t_phil *state);
int				to_eat(t_phil *state);
int				to_sleep_and_think(t_phil *state);
int				write_message(t_phil *state, char *s);
int				ft_strlen(char *s);
int				init_struct(t_param *phil, int arg);
void			ft_putstr(char *s);
void			ft_putnbr(int n);
void			ft_putchar(char c);
uint64_t		get_time(void);
sem_t			*sem_create(char *name, int value);

#endif
