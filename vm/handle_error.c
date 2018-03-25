/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   handle_error.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: amichak <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/03/05 12:41:00 by amichak           #+#    #+#             */
/*   Updated: 2018/03/05 12:41:00 by amichak          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "corewar.h"

int		invalid_pl_size(t_player **pl, char *str)
{
	return (prerr_fr(pl, concat_strs("Error: File ", str, " has a code size "
			"that differ from what its header says", NULL)));
}

int		err_big_champ(t_player **pl, char *str)
{
	return (prerr_fr(pl, concat_strs("Error: File ", str, " has too large "
			"code", NULL)));
}

int		err_small_champ(t_player **pl, char *str)
{
	return (prerr_fr(pl, concat_strs("Error: File ", str, " is too small to be "
			"a champion", NULL)));
}

int		invalid_magic(t_player **pl, char *str)
{
	return (prerr_fr(pl, concat_strs("Error: ", str, " invalid magic", NULL)));
}

int		err_nameless_champ(t_player **pl, char *str)
{
	return (prerr_fr(pl, concat_strs("Error: ", str, " doesn't have name",
									NULL)));
}
