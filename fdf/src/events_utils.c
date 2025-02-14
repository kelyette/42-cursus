/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   events_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: kcsajka <kcsajka@student.42.fr>            +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/12/17 20:04:10 by kcsajka           #+#    #+#             */
/*   Updated: 2025/02/11 18:55:46 by kcsajka          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "events.h"

t_kbind	*get_key(t_kbind *keybinds, int key)
{
	while (keybinds->code != -1 && keybinds->code != key)
		keybinds++;
	if (keybinds->code == -1)
		return (0);
	return (keybinds);
}

inline int	get_complkey(t_kbind *kbds, int k1, int k2)
{
	return (get_key(kbds, k1)->state * -1 + get_key(kbds, k2)->state);
}
