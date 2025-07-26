/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ohaker <ohaker@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/03 20:51:15 by ohaker            #+#    #+#             */
/*   Updated: 2025/07/26 20:12:36 by ohaker           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int init_input(int argc, char **argv, t_philo *philo)
{
	int x;
	int y;

	x = 0;
	y = 0;
	philo->rules->philo_count = ft_atoi(argv[1]);
	philo->rules->time_to_die = ft_atoi(argv[2]);
	philo->rules->time_to_eat = ft_atoi(argv[3]);
	philo->rules->time_to_sleep = ft_atoi(argv[4]);
	if (argc == 6)
		philo->rules->must_eat_count = ft_atoi(argv[5]);
	else if (argc == 5)
		philo->rules->must_eat_count = -1;
	philo->rules->forks = malloc(sizeof(pthread_mutex_t)
		* philo->rules->philo_count); //fix this ho
	if (!philo->rules->forks)
		error_msg("Memory allocation for forks failed.\n");
	while (x < ft_atoi(argv[1]))
		pthread_mutex_init(&philo->rules->forks[x++], NULL);
	pthread_mutex_init(&philo->rules->print_lock, NULL);
	pthread_mutex_init(&philo->rules->simulation_lock, NULL);
	pthread_mutex_init(&philo->rules->write_lock, NULL);
	return (0);
}

int init_philos(t_philo *philo)
{
	int x;

	x = 0;
	philo->rules->philos = malloc(sizeof(t_philo) * philo->rules->philo_count);
	if (!philo->rules->philos)
		error_msg("Memory allocation of philos failes.\n");
	while (x < philo->rules->philo_count)
	{
		philo->rules->philos[x].rules = philo->rules;
		philo->rules->philos[x].alive = 1;
		philo->rules->philos[x].id = x;
		philo->rules->philos[x].meals_eaten = 0;
		philo->rules->philos[x].last_meal = philo->rules->start_time;
		philo->rules->philos[x].left_fork = &philo->rules->forks[x];
		philo->rules->philos[x].right_fork = &philo->rules->forks[(x + 1) % philo->rules->philo_count];
		x++;
	}
	gettimeofday(&philo->rules->start_time, NULL);
	return (0);
}

void *philo_routine(void *arg)
{
	t_philo *philo = (t_philo *)arg;

	if (philo->id % 2 == 0)
		usleep(1000);
	while(check_alive(philo->rules))
	{
		philo_think(philo);
		if (philo_fork(philo))
		{
			philo_eat(philo);
			philo_sleep(philo);
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

int main(int argc, char **argv)
{
	t_philo philo;

	philo.rules = malloc(sizeof(t_rules));
	if (!philo.rules)
		error_msg("Memory allocation failed.\n");
	check_input(argc, argv);
	init_input(argc, argv, &philo);
	init_philos(&philo);
	thread_create(philo.rules);
	// printf("philos: %d\ndie: %d\neat: %d\nsleep: %d\ncount: %d\n", philo.rules->philo_count, philo.rules->time_to_die, philo.rules->time_to_eat, philo.rules->time_to_sleep, philo.rules->must_eat_count);
	return (0);
}
