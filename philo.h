/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:46:51 by ohaker            #+#    #+#             */
/*   Updated: 2025/07/26 19:55:12 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef PHILO_H
# define PHILO_H

# include <sys/time.h>
# include <stdio.h>
# include <stdint.h>
# include <unistd.h>
# include <stdlib.h>
# include <string.h>
# include <pthread.h>

typedef struct s_rules
{
	int				philo_count;
	int				time_to_die;
	int				time_to_eat;
	int				time_to_sleep;
	int				must_eat_count;
	int				stop_simulation;
	pthread_mutex_t	*forks;
	pthread_mutex_t	print_lock;
	pthread_mutex_t write_lock;
	pthread_mutex_t meal_lock;
	pthread_mutex_t alive_lock;
	pthread_mutex_t	simulation_lock;
	struct timeval	start_time;
	struct s_philo	*philos;
}	t_rules;

typedef struct s_philo
{
	int				alive;
	int				id;
	int				meals_eaten;
	struct timeval	last_meal;
	pthread_t		thread_id;
	pthread_mutex_t	*left_fork;
	pthread_mutex_t	*right_fork;
	t_rules			*rules;
}	t_philo;

//utils.c
int	ft_atoi(const char *str);
void error_msg(char *err_str);
int ft_isdigit(char c);
long get_time_diff(struct timeval start);
void ft_usleep(long sleep, t_philo *philo);
void printf_safe(t_philo *philo, char *msg);

//checks.c
int check_input(int argc, char **argv);
int check_alive(t_rules *rules);
int check_end(t_rules *rules);

//routines.c
void philo_think(t_philo *philo);
int philo_fork(t_philo *philo);
void philo_eat(t_philo *philo);
void philo_sleep(t_philo *philo);
void *one_philo(void *arg);

#endif