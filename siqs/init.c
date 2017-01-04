/*
    Copyright (C) 2006, 2011, 2016 William Hart
    Copyright (C) 2015 Nitin Kumar

    This file is part of FLINT.

    FLINT is free software: you can redistribute it and/or modify it under
    the terms of the GNU Lesser General Public License (LGPL) as published
    by the Free Software Foundation; either version 2.1 of the License, or
    (at your option) any later version.  See <http://www.gnu.org/licenses/>.
*/

#include <gmp.h>
#include "flint.h"
#include "ulong_extras.h"
#include "fmpz.h"
#include "siqs.h"

void qsieve_init(qs_t qs_inf, fmpz_t n)
{
    slong i;

    /* store n in struct */
    fmpz_init_set(qs_inf->n, n);

    /* determine the number of bits of n */
    qs_inf->bits =  fmpz_bits(n);

    /* determine which index in the tuning table n corresponds to */
    for (i = 1; i < QS_TUNE_SIZE; i++)
    {
        if (qsieve_tune[i][0] > qs_inf->bits)
            break;
    }
    i--;

    qs_inf->ks_primes  = qsieve_tune[i][1]; /* number of Knuth-Schroeppel primes */
    qs_inf->qsort_rels = qsieve_tune[i][1];
    qs_inf->num_primes  = 0;
    qs_inf->num_relations = 0;
    qs_inf->full_relation = 0;
    qs_inf->num_cycles = 0;
    qs_inf->num_unmerged = 0;
    qs_inf->columns = 0;
    qs_inf->vertices = 0;
    qs_inf->components = 0;
    qs_inf->edges = 0;

    fmpz_init(qs_inf->kn); /* initialise kn */

    qs_inf->factor_base = NULL;
    qs_inf->sqrts       = NULL;

    qs_inf->s = 0;
}