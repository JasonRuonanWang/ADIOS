#include <stdio.h>
#include "core/adios_transport_hooks.h"

void adios_uniman_write(
    struct adios_file_struct *fd,
    struct adios_var_struct *f,
    const void *data,
    struct adios_method_struct *method)
{
    printf("adios_uniman_write \n");

}

int adios_uniman_open (struct adios_file_struct * fd
                     ,struct adios_method_struct * method, MPI_Comm comm
                     )
{
    printf("adios_uniman_open \n");
    return 0;
}

void adios_uniman_init (const PairStruct * parameters
                      ,struct adios_method_struct * method
                      )
{
    printf("adios_uniman_init \n");
}

void adios_uniman_read (struct adios_file_struct * fd
                      ,struct adios_var_struct * v
                      ,void * buffer
                      ,uint64_t buffer_size
                      ,struct adios_method_struct * method
                      )
{
    printf("adios_uniman_read \n");
}


void adios_uniman_buffer_overflow (struct adios_file_struct * fd,
                                  struct adios_method_struct * method)
{
    printf("adios_uniman_buffer_overflow \n");
}

void adios_uniman_close (struct adios_file_struct * fd
                       ,struct adios_method_struct * method
                       )
{
    printf("adios_uniman_close \n");
}

void adios_uniman_finalize (int mype, struct adios_method_struct * method)
{
    printf("adios_uniman_finalize \n");
}

void adios_uniman_end_iteration (struct adios_method_struct * method)
{
    printf("adios_uniman_end_iteration \n");
}

void adios_uniman_get_write_buffer (struct adios_file_struct * fd
                                  ,struct adios_var_struct * v
                                  ,uint64_t * size
                                  ,void ** buffer
                                  ,struct adios_method_struct * method
                                  )
{
    printf("adios_uniman_get_write_buffer \n");
}


enum BUFFERING_STRATEGY adios_uniman_should_buffer (struct adios_file_struct * fd
                                                  ,struct adios_method_struct * method
                                                  )
{
    printf("adios_uniman_should_buffer \n");
    return no_buffering;
}

void adios_uniman_start_calculation (struct adios_method_struct * method)
{
    printf("adios_uniman_start_calculation \n");
}

void adios_uniman_stop_calculation (struct adios_method_struct * method)
{
    printf("adios_uniman_stop_calculation \n");
}

