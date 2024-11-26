/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:23:41 by ymauk             #+#    #+#             */
/*   Updated: 2024/11/26 16:56:39 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(void *arg)
{
	t_philos	*philo;
	size_t		time;

	philo = (t_philos *)arg;
	time = get_current_time() - philo->data->start_time;
	printf("%zu Philosopher %d is thinking\n", time, philo->id_philo);
}


void	take_forks(void *arg)
{
	t_philos	*philo;
	int			left_fork;
	int			right_fork;

	philo = (t_philos *)arg;
	left_fork = philo->id_philo - 1;
	right_fork = philo->id_philo % philo->data->nbr_of_philos;
	if (philo->id_philo % 2 == 0)
	{

	}
	else
}

void	eating(void *arg)
{
	t_philos	*philo;
	size_t		time_r;
	size_t		time_l;
	// int			help;

	philo = (t_philos *)arg;
	time_r = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->forks[philo->id_philo - 1]);
	printf("%zu Philosopher %d has taken a fork\n", time_r, philo->id_philo);
	time_l = get_current_time() - philo->data->start_time;
	pthread_mutex_lock(&philo->data->forks[philo->id_philo
		% philo->data->nbr_of_philos]);
	printf("%zu Philosopher %d has taken a fork\n", time_r, philo->id_philo);
	printf("%zu Philosopher %d is eating\n", get_current_time()
		- philo->data->start_time, philo->id_philo);
	philo->last_meal = get_current_time();
	ft_usleep(philo->data->time_to_eat);
	pthread_mutex_unlock(&philo->data->forks[philo->id_philo - 1]);
	// help = philo->id_philo % philo->data->nbr_of_philos;
	pthread_mutex_unlock(&philo->data->forks[philo->id_philo % philo->data->nbr_of_philos]);
}

void	putdown_forks(void *arg)
{
	
}

void	sleep(void *arg)
{

}
