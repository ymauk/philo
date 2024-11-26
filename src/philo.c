/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ymauk <ymauk@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/09/13 13:03:25 by ymauk             #+#    #+#             */
/*   Updated: 2024/11/27 18:01:25 by ymauk            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../philo.h"

int	main(int argc, char **argv)
{
	t_data		data;
	// pthread_t	monitoring;

	if (argc > 1)
	{
		parsing(argc, argv, &data);
		data.start_simulation = 0;
		pthread_mutex_init(&data.start, NULL);
		// print_philos(data.philos, data.nbr_of_philos);
		create_threads(&data);
		pthread_mutex_lock(&data.start);
		data.start_simulation = 1;
		pthread_mutex_unlock(&data.start);
		data.start_time = get_current_time();
		// pthread_create(&monitoring, NULL, monitoring_routine, &data);
		join_threads(&data);
		// pthread_join(monitoring, NULL);
	}
	return (0);
}

// void print_philos(t_philos *head, int nbr_of_philos)
// {
//     t_philos *current = head;
//     int count = 0;

//     // Debug-Maßnahme 1: Überprüfe, ob die Liste existiert
//     if (!current)
//     {
//         printf("Die Liste ist leer oder ungültig (head: %p).\n", (void *)head);
//         return;
//     }

//     printf("Philosophenliste (Anzahl: %d):\n", nbr_of_philos);

//     // Debug-Maßnahme 2: Werte in der Schleife überprüfen
//     do
//     {
//         if (!current)
//         {
//             printf("Error: Ungültiger Knoten gefunden (current: NULL).\n");
//             return;
//         }

//         printf("Philosoph ID: %d, Last Meal: %zu, Current: %p, Next: %p\n",
//                current->id_philo,
//                current->last_meal,
//                (void *)current,
//                (void *)current->next);

//         current = current->next;
//         count++;
//     } while (current != head && count < nbr_of_philos);

//     // Hinweis auf Zirkularität
//     if (current == head)
//         printf("Die Liste ist zirkulär.\n");
//     else
//         printf("Die Liste ist nicht vollständig zirkulär.\n");
// }
