/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   messages.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/22 18:23:41 by ymauk             #+#    #+#             */
/*   Updated: 2025/04/04 11:34:33 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

void	thinking(void *arg)
{
	t_philos	*philo;

	philo = arg;
	if (philo->data->check_dead != 1)
		print_message(philo, "is thinking");
}

void	take_forks(void *arg)
{
	t_philos	*philo;
	int			left_fork;
	int			right_fork;
	int			first_fork;
	int			second_fork;

	philo = arg;
	left_fork = philo->id_philo - 1;
	right_fork = philo->id_philo % philo->data->nbr_of_philos;
	if (left_fork > right_fork)
	{
		first_fork = left_fork;
		second_fork = right_fork;
	}
	else
	{
		first_fork = right_fork;
		second_fork = left_fork;
	}
	pthread_mutex_lock(&philo->data->forks[first_fork]);
	if (philo->data->check_dead != 1)
		print_message(philo, "has taken a fork");
	pthread_mutex_lock(&philo->data->forks[second_fork]);
	if (philo->data->check_dead != 1)
		print_message(philo, "has taken a fork");
}

// void	eating(void *arg)
// {
// 	t_philos	*philo;

// 	philo = arg;
// 	pthread_mutex_lock(&philo->meal);
// 	philo->last_meal = get_current_time();
// 	philo->has_eaten++;
// 	// printf("has eaten: %d\n", philo->has_eaten);
// 	pthread_mutex_unlock(&philo->meal);
// 	if (philo->data->check_dead != 1)
// 		print_message(philo, "is eating");
// 	ft_usleep(philo->data->time_to_eat);
// }

void	eating(void *arg)
{
	t_philos	*philo;
	size_t		current_time;

	philo = (t_philos *)arg;
	current_time = get_current_time(); // Zeit einmal holen
	pthread_mutex_lock(&philo->meal);
	philo->last_meal = current_time;
	philo->has_eaten++;
	// Optional: check_dead auch hier prüfen, falls Konsistenz wichtig ist
	pthread_mutex_unlock(&philo->meal);
	if (philo->data->check_dead != 1)
		print_message(philo, "is eating");
	ft_usleep(philo->data->time_to_eat);
}

void	putdown_forks(void *arg)
{
	t_philos	*philo;
	int			left_fork;
	int			right_fork;

	philo = arg;
	left_fork = philo->id_philo - 1;
	right_fork = philo->id_philo % philo->data->nbr_of_philos;
	pthread_mutex_unlock(&philo->data->forks[left_fork]);
	pthread_mutex_unlock(&philo->data->forks[right_fork]);
	usleep(500);
}

void	go_sleep(void *arg)
{
	t_philos	*philo;

	philo = arg;
	if (philo->data->check_dead != 1)
		print_message(philo, "is sleeping");
	ft_usleep(philo->data->time_to_sleep);
}

// void	take_forks(void *arg)
// {
// 	t_philos	*philo;
// 	int			left_fork;
// 	int			right_fork;

// 	philo = (t_philos *)arg;
// 	left_fork = philo->id_philo - 1;
// 	right_fork = philo->id_philo % philo->data->nbr_of_philos;
// 	if (philo->id_philo % 2 == 0)
// 	{
// 		pthread_mutex_lock(&philo->data->forks[left_fork]);
// 		print_message(philo, "has taken a fork");
// 		pthread_mutex_lock(&philo->data->forks[right_fork]);
// 		print_message(philo, "has taken a fork");
// 	}
// 	else
// 	{
// 		pthread_mutex_lock(&philo->data->forks[right_fork]);
// 		print_message(philo, "has taken a fork");
// 		pthread_mutex_lock(&philo->data->forks[left_fork]);
// 		print_message(philo, "has taken a fork");
// 	}
// }