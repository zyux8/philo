/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:53:57 by ohaker            #+#    #+#             */
/*   Updated: 2025/11/29 15:41:06 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	clean_up(t_rules *rules)
{
	int	x;

	x = 0;
	while (x < rules->philo_count)
		pthread_mutex_destroy(&rules->forks[x++]);
	pthread_mutex_destroy(&rules->alive_lock);
	pthread_mutex_destroy(&rules->meal_lock);
	pthread_mutex_destroy(&rules->print_lock);
	pthread_mutex_destroy(&rules->simulation_lock);
	free(rules->forks);
	free(rules->philos);
	free(rules);
	return (0);
}

void	*philo_routine(void *arg)
{
	t_philo	*philo;

	philo = (t_philo *)arg;
	if (philo->id % 2 == 0)
		usleep(1000);
	while (check_alive_one(philo) && (philo->rules->must_eat_count <= 0
			|| philo->meals_eaten != philo->rules->must_eat_count))
	{
		usleep(400);
		if (get_stop_sim(philo->rules) || philo_full(philo))
			break ;
		if (philo_fork(philo))
		{
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
		}
		else
			break ;
	}
	return (NULL);
}

int	thread_create(t_rules *rules)
{
	int	x;

	x = 0;
	if (rules->philo_count == 1)
	{
		pthread_create(&rules->philos[x].thread_id, NULL, one_philo,
			&rules->philos[x]);
		return (0);
	}
	else
	{
		while (x < rules->philo_count)
		{
			pthread_create(&rules->philos[x].thread_id, NULL, philo_routine,
				&rules->philos[x]);
			x++;
		}
	}
	return (0);
}

int	thread_join(t_rules *rules)
{
	int	x;

	x = 0;
	while (x < rules->philo_count)
	{
		pthread_join(rules->philos[x].thread_id, NULL);
		x++;
	}
	return (0);
}
