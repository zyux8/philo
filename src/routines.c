/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:31:32 by ohaker            #+#    #+#             */
/*   Updated: 2025/08/25 18:07:41 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void philo_think(t_philo *philo)
{
	long time_diff;

	// time_diff = get_time_diff(philo->rules->start_time);
	printf_safe(philo, "is thinking");
}

int philo_fork(t_philo *philo)
{
	long time_diff;
	
    if (philo->id % 2 == 0)
    {
        pthread_mutex_lock(philo->left_fork);
        pthread_mutex_lock(philo->right_fork);
    }
    else
    {
        pthread_mutex_lock(philo->right_fork);
        pthread_mutex_lock(philo->left_fork);
    }
	if (!check_alive(philo->rules))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	// time_diff = get_time_diff(philo->rules->start_time);
	printf_safe(philo, "has taken a fork");
	printf_safe(philo, "has taken a fork");
	return (1);
}

void philo_eat(t_philo *philo)
{
	long time_diff;

	// time_diff = get_time_diff(philo->rules->start_time);
	pthread_mutex_lock(&philo->rules->meal_lock);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->rules->meal_lock);
	printf_safe(philo, "is eating");
	ft_usleep(philo->rules->time_to_eat * 1000, philo);
	// usleep(philo->rules->time_to_eat * 1000);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->rules->meal_lock);
	philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->rules->meal_lock);
}

void philo_sleep(t_philo *philo)
{
	long time_diff;

	// time_diff = get_time_diff(philo->rules->start_time);
	printf_safe(philo, "is sleeping");
	ft_usleep(philo->rules->time_to_sleep * 1000, philo);
	// usleep(philo->rules->time_to_sleep * 1000);
}

void *one_philo(void *arg)
{
	t_philo *philo = (t_philo *)arg;
	long time_diff;

	pthread_mutex_lock(philo->left_fork);
	time_diff = get_time_diff(philo->rules->start_time);
	printf_safe(philo, "has taken a fork");
	// ft_usleep(philo->rules->time_to_die * 1000, philo);
	usleep(philo->rules->time_to_die * 1000);
	pthread_mutex_unlock(philo->left_fork);
	time_diff = get_time_diff(philo->rules->start_time);
	printf_safe(philo, "died");
	pthread_exit(NULL);
}

//more alive checks