/* 
 * ADIOS is freely available under the terms of the BSD license described
 * in the COPYING file in the top level directory of this source distribution.
 *
 * Copyright (c) 2008 - 2009.  UT-BATTELLE, LLC. All rights reserved.
 */

#include "config.h"

#ifdef _NOMPI
    /* Sequential processes can use the library compiled with -D_NOMPI */
#   define ADIOS_EMPTY_TRANSPORTS
#else
    /* Parallel applications should use MPI to communicate file info and slices of data */
#endif

#include "adios.h"
#include "adios_transport_hooks.h"
#include "adios_bp_v1.h"
#include "adios_internals.h"

#define MATCH_STRING_TO_METHOD(b,d,r) \
if (!strcasecmp (buf,b)) \
{*method=d;*requires_group_comm=r;return 1;}

#define ASSIGN_FNS(a,b) \
(*t) [b].adios_init_fn = adios_##a##_init; \
(*t) [b].adios_open_fn = adios_##a##_open; \
(*t) [b].adios_should_buffer_fn = adios_##a##_should_buffer; \
(*t) [b].adios_write_fn = adios_##a##_write; \
(*t) [b].adios_get_write_buffer_fn = adios_##a##_get_write_buffer; \
(*t) [b].adios_read_fn = adios_##a##_read; \
(*t) [b].adios_close_fn = adios_##a##_close; \
(*t) [b].adios_finalize_fn = adios_##a##_finalize; \
(*t) [b].adios_end_iteration_fn = adios_##a##_end_iteration; \
(*t) [b].adios_start_calculation_fn = adios_##a##_start_calculation; \
(*t) [b].adios_stop_calculation_fn = adios_##a##_stop_calculation;

void adios_init_transports (struct adios_transport_struct ** t)
{
    *t = (struct adios_transport_struct *)
           calloc (ADIOS_METHOD_COUNT, sizeof (struct adios_transport_struct));

#ifndef NO_RESEARCH_TRANSPORTS
    ASSIGN_FNS(adaptive,ADIOS_METHOD_ADAPTIVE)
#endif

#if HAVE_MPI
    ASSIGN_FNS(mpi,ADIOS_METHOD_MPI)
    ASSIGN_FNS(mpi_stripe,ADIOS_METHOD_MPI_STRIPE)
    ASSIGN_FNS(mpi_stripe2,ADIOS_METHOD_MPI_STRIPE2)
    ASSIGN_FNS(mpi_cio,ADIOS_METHOD_MPI_CIO)
#ifndef NO_RESEARCH_TRANSPORTS
    ASSIGN_FNS(mpi_stagger,ADIOS_METHOD_MPI_STAGGER)
    ASSIGN_FNS(mpi_aggregate,ADIOS_METHOD_MPI_AGG)
#endif
#endif

#ifndef NO_RESEARCH_TRANSPORTS
#if NO_DATATAP == 0
    ASSIGN_FNS(datatap,ADIOS_METHOD_DATATAP)
#endif
#endif

    ASSIGN_FNS(posix,ADIOS_METHOD_POSIX)

#ifndef NO_RESEARCH_TRANSPORTS
#if USE_PORTALS
    ASSIGN_FNS(dart,ADIOS_METHOD_DART)
#endif
#endif

#if HAVE_PHDF5
    ASSIGN_FNS(phdf5,ADIOS_METHOD_PHDF5)
#endif

#ifndef NO_RESEARCH_TRANSPORTS
    ASSIGN_FNS(provenance,ADIOS_METHOD_PROVENANCE)
#endif
}

int adios_parse_method (const char * buf, enum ADIOS_IO_METHOD * method
                       ,int * requires_group_comm
                       )
{
    // add the string<->ID mapping here (also add ID in adios_internals.h)
    // use a '1' for requires a communicator or '0' if not as the last param
#ifndef NO_RESEARCH_TRANSPORTS
    MATCH_STRING_TO_METHOD("ADAPTIVE",ADIOS_METHOD_ADAPTIVE,1)
#endif

#if HAVE_MPI
    MATCH_STRING_TO_METHOD("MPI",ADIOS_METHOD_MPI,1)
    MATCH_STRING_TO_METHOD("MPI_STRIPE",ADIOS_METHOD_MPI_STRIPE,1)
    MATCH_STRING_TO_METHOD("MPI_STRIPE2",ADIOS_METHOD_MPI_STRIPE2,1)
    MATCH_STRING_TO_METHOD("MPI_CIO",ADIOS_METHOD_MPI_CIO,1)
#ifndef NO_RESEARCH_TRANSPORTS
    MATCH_STRING_TO_METHOD("MPI_STAGGER",ADIOS_METHOD_MPI_STAGGER,1)
    MATCH_STRING_TO_METHOD("MPI_AGGREGATE",ADIOS_METHOD_MPI_AGG,1)
#endif
#endif

#ifndef NO_RESEARCH_TRANSPORTS
#if NO_DATATAP == 0
    MATCH_STRING_TO_METHOD("DATATAP",ADIOS_METHOD_DATATAP,0)
    MATCH_STRING_TO_METHOD("PBIO",ADIOS_METHOD_DATATAP,0)
#endif
#endif

    MATCH_STRING_TO_METHOD("POSIX",ADIOS_METHOD_POSIX,0)
    MATCH_STRING_TO_METHOD("FB",ADIOS_METHOD_POSIX,0)

#ifndef NO_RESEARCH_TRANSPORTS
#if USE_PORTALS
    MATCH_STRING_TO_METHOD("DART",ADIOS_METHOD_DART,0)
#endif
#endif

#if HAVE_PHDF5
    MATCH_STRING_TO_METHOD("PHDF5",ADIOS_METHOD_PHDF5,1)
#endif

#ifndef NO_RESEARCH_TRANSPORTS
    MATCH_STRING_TO_METHOD("PROVENANCE",ADIOS_METHOD_PROVENANCE,1)
#endif

    MATCH_STRING_TO_METHOD("NULL",ADIOS_METHOD_NULL,0)

    *method = ADIOS_METHOD_UNKNOWN;
    *requires_group_comm = 0;

    return 0;
}
