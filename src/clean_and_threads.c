/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean_and_threads.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/30 18:53:57 by ohaker            #+#    #+#             */
/*   Updated: 2025/08/25 17:38:15 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int clean_up(t_philo *philo)
{
    int x = 0;
    while (x < philo->rules->philo_count)
        pthread_mutex_destroy(&philo->rules->forks[x++]);
    pthread_mutex_destroy(&philo->rules->alive_lock);
    pthread_mutex_destroy(&philo->rules->meal_lock);
    pthread_mutex_destroy(&philo->rules->print_lock);
    pthread_mutex_destroy(&philo->rules->simulation_lock);
    free(philo->rules->forks);
    free(philo->rules->philos);
    free(philo->rules);
    return (0);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	// if (philo->id % 2 == 0)
	// 	usleep(1000);
	while(check_alive(philo->rules))
	{
		if (get_stop_sim(philo->rules))
			break;
		if (philo_fork(philo))
		{
			philo_eat(philo);
			philo_sleep(philo);
			philo_think(philo);
		}
		else
			pthread_exit(NULL);
	}
	return (NULL);
}

int thread_create(t_rules *rules)
{
	int x;

	x = 0;
	if (rules->philo_count == 1)
	{
		pthread_create(&rules->philos[x].thread_id, NULL, one_philo, &rules->philos[x]);
		return (0);
	}
	while (x < rules->philo_count)
	{
		pthread_create(&rules->philos[x].thread_id, NULL, philo_routine, &rules->philos[x]);
		x++;
	}
	return (0);
}

int thread_join(t_rules *rules)
{
	int x;

	x = 0;
	while (x < rules->philo_count)
	{
		pthread_join(rules->philos[x].thread_id, NULL);
		x++;
	}
	return (0);
}
