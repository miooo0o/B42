/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   philo.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: minakim <minakim@student.42berlin.de>      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/10/09 14:58:56 by minakim           #+#    #+#             */
/*   Updated: 2023/10/09 15:58:54 by minakim          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "philo.h"

FILE *log_file;
int incidents = 0;

int main ()
{
	int input = 0;

	do
	{
		printf("enter -1 to quit.\n");
		printf("new incidents: ");
		scanf("%d", &input);

		if (input != -1) incidents += input;
	} while (input != -1);
	return (0);
}