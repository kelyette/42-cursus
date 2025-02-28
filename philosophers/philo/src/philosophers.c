/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philosophers.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/28 14:54:57 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/28 16:27:59 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philosophers.h"

void	*threadfunc(void *arg)
{
	sleep(1);
	printf("arg: %s\n", (char *)arg);
	return (NULL);
}

int	main(void)
{
	pthread_t	thread;

	printf("before\n");
	pthread_create(&thread, NULL, threadfunc, "hello hi");
	pthread_join(thread, NULL);
	printf("after\n");
	return (0);
}
