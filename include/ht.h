/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ht.h                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: c4v3d <c4v3d@student.42.fr>                +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/07 19:57:20 by c4v3d             #+#    #+#             */
/*   Updated: 2025/05/07 20:09:32 by c4v3d            ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef HT_H
# define HT_H

typedef struct s_ht t_ht;

// Create hash table and return pointer to it or NULL if out of mem.
t_ht	*ht_create(void);

// Free memory allocated for hash table, including allocated key
void	*ht_destroy(t_ht *table);

// Get item with given key (NULL-terminated) from hash table. Return
// value (which was set with ht_set) or NULL if key not found.
void	*ht_get(t_ht *table, const char *key);

// Set item with given key to value (whih must not be NULL). If not already present in table,
// key is copied to newly allocated memory (keys are freed automatically when ht_destroy is called).
// Return address of copied key, or NULL if out of mem.
const char	*ht_set(t_ht *table, const char *key, void *value);

// Return number of items in hash table.
size_t	ht_lenght(t_ht *table);

#endif