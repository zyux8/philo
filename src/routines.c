/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:31:32 by ohaker            #+#    #+#             */
/*   Updated: 2025/07/23 03:47:19 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void philo_think(t_philo *philo)
{
	long time_diff;

	time_diff = get_time_diff(philo->rules->start_time);
	printf("%ld %d is thinking\n", time_diff, philo->id);
}

void philo_fork(t_philo *philo)
{
	long time_diff;
	
	pthread_mutex_lock(philo->left_fork);
	pthread_mutex_lock(philo->right_fork);
	time_diff = get_time_diff(philo->rules->start_time);
	//check alive
	printf("%ld %d has taken a fork\n", time_diff, philo->id);
	printf("%ld %d has taken a fork\n", time_diff, philo->id);
}

void philo_eat(t_philo *philo)
{
	long time_diff;

	time_diff = get_time_diff(philo->rules->start_time);
	printf("%ld %d is eating\n", time_diff, philo->id);
	usleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
}

void philo_sleep(t_philo *philo)
{
	long time_diff;

	time_diff = get_time_diff(philo->rules->start_time);
	printf("%ld %d is sleeping\n", time_diff, philo->id);
	usleep(philo->rules->time_to_sleep * 1000);
}

void *one_philo(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	long time_diff;

	pthread_mutex_lock(philo->left_fork);
	time_diff = get_time_diff(philo->rules->start_time);
	printf("%ld %d has taken a fork\n", time_diff, philo->id);
	usleep(philo->rules->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	time_diff = get_time_diff(philo->rules->start_time);
	printf("%ld %d died\n", time_diff, philo->id);
	pthread_exit(NULL);
}

//more alive checks