/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   routines.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/17 16:31:32 by ohaker            #+#    #+#             */
/*   Updated: 2025/11/29 15:45:55 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	philo_think(t_philo *philo)
{
	printf_safe(philo, "is thinking");
}

int	philo_fork(t_philo *philo)
{
	if (philo->id % 2 == 0)
	{
		pthread_mutex_lock(philo->left_fork);
		printf_safe(philo, "has taken a fork");
		pthread_mutex_lock(philo->right_fork);
		printf_safe(philo, "has taken a fork");
	}
	else
	{
		pthread_mutex_lock(philo->right_fork);
		printf_safe(philo, "has taken a fork");
		pthread_mutex_lock(philo->left_fork);
		printf_safe(philo, "has taken a fork");
	}
	if (!check_alive_one(philo))
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return (0);
	}
	return (1);
}

void	philo_eat(t_philo *philo)
{
	if (philo->rules->must_eat_count == philo->meals_eaten)
	{
		pthread_mutex_unlock(philo->left_fork);
		pthread_mutex_unlock(philo->right_fork);
		return ;
	}
	pthread_mutex_lock(&philo->philo_lock);
	gettimeofday(&philo->last_meal, NULL);
	pthread_mutex_unlock(&philo->philo_lock);
	printf_safe(philo, "is eating");
	ft_usleep(philo->rules->time_to_eat, philo);
	pthread_mutex_unlock(philo->left_fork);
	pthread_mutex_unlock(philo->right_fork);
	pthread_mutex_lock(&philo->philo_lock);
	if (!get_stop_sim(philo->rules)
		&& philo->meals_eaten < philo->rules->must_eat_count)
		philo->meals_eaten += 1;
	pthread_mutex_unlock(&philo->philo_lock);
}

void	philo_sleep(t_philo *philo)
{
	printf_safe(philo, "is sleeping");
	ft_usleep(philo->rules->time_to_sleep, philo);
}

void	*one_philo(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	pthread_mutex_lock(philo->left_fork);
	printf_safe(philo, "has taken a fork");
	ft_usleep(philo->rules->time_to_die, philo);
	pthread_mutex_unlock(philo->left_fork);
	printf_safe(philo, "died");
	set_stop_sim(philo->rules);
	pthread_exit(NULL);
}
