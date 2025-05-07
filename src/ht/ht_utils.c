/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 20:16:23 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/07 21:45:04 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../include/minishell.h"

t_ht	*ht_create(void)
{
	t_ht	*table;

	table = malloc(sizeof(t_ht));
	if (!table)
		return (NULL);
	table->lenght = 0;
	table->capacity = INITIAL_CAPACITY;
	table->entries = ft_calloc(table->capacity, sizeof(t_ht_entry));
	if (!table->entries)
	{
		free(table);
		return (NULL);
	}
	return (table);
}

void	ht_destroy(t_ht *table)
{
	int	i;

	i = 0;
	while (i < table->capacity)
		w_free((void **)&(table->entries[i++].key));
	w_free((void **)&(table->entries));
	w_free((void **)&(table));
}

void	*ht_get(t_ht *table, const char *key)
{
	uint64_t	hash;
	size_t		index;

	hash = hash_key(key);
	index = (size_t)(hash & (uint64_t)(table->capacity - 1));
	while (table->entries[index].key)
	{
		if (ft_strncmp(key, table->entries[index].key, ft_strlen(key)) == 0)
			return (table->entries[index].value);
		index++;
		if (index >= table->capacity)
			index = 0;
	}
	return (NULL);
}

static const char	*ht_set_entry(t_ht_entry *entries, size_t capacity,
								const char *key, void *value, size_t *plength)
{
	// AND hash with capacity-1 to ensure it's within entries array.
	uint64_t hash = hash_key(key);
	size_t index = (size_t)(hash & (uint64_t)(capacity - 1));

	// Loop till we find an empty entry.
	while (entries[index].key != NULL)
	{
		if (strcmp(key, entries[index].key) == 0)
		{
			entries[index].value = value;
			return (entries[index].key);
		}
		index++;
		if (index >= capacity)
			index = 0;}
	if (plength != NULL)
	{
		key = strdup(key);
		if (key == NULL)
			return (NULL);
		(*plength)++;
	}
	entries[index].key = (char*)key;
	entries[index].value = value;
	return (key);
}

const char	*ht_set(t_ht *table, const char *key, void *value)
{
	if (!value)
		return (NULL);
	if (table->lenght >= table->capacity / 2)
	{
		if (!ht_expand(table))
			return (NULL);
	}
	return ht_set_entry(table->entries, table->capacity, key, value, &(table->lenght));
}