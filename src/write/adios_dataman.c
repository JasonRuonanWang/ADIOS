#include <stdio.h>
#include <dlfcn.h>
#include "core/adios_transport_hooks.h"
#include "public/adios_types.h"

void adios_dataman_write(
    struct adios_file_struct *fd,
    struct adios_var_struct *f,
    const void *data,
    struct adios_method_struct *method)
{
    void *myso = dlopen("./libdataman.so", RTLD_NOW);
    void (*func)(struct adios_file_struct*, struct adios_var_struct*, const void*, struct adios_method_struct*)
        = dlsym(myso, "adios_dataman_write");
    func(fd, f, data, method);
    dlclose(myso);
}

int adios_dataman_open (struct adios_file_struct * fd
                     ,struct adios_method_struct * method, MPI_Comm comm
                     )
{
    printf("adios_dataman_open \n");
    return 0;
}

void adios_dataman_init (const PairStruct * parameters
                      ,struct adios_method_struct * method
                      )
{
    printf("adios_dataman_init \n");
}

void adios_dataman_read (struct adios_file_struct * fd
                      ,struct adios_var_struct * v
                      ,void * buffer
                      ,uint64_t buffer_size
                      ,struct adios_method_struct * method
                      )
{
    printf("adios_dataman_read \n");
}

void adios_dataman_buffer_overflow (struct adios_file_struct * fd,
                                  struct adios_method_struct * method)
{
    printf("adios_dataman_buffer_overflow \n");
}

void adios_dataman_close (struct adios_file_struct * fd
                       ,struct adios_method_struct * method
                       )
{
    printf("adios_dataman_close \n");
}

void adios_dataman_finalize (int mype, struct adios_method_struct * method)
{
    printf("adios_dataman_finalize \n");
}

void adios_dataman_end_iteration (struct adios_method_struct * method)
{
    printf("adios_dataman_end_iteration \n");
}

void adios_dataman_get_write_buffer (struct adios_file_struct * fd
                                  ,struct adios_var_struct * v
                                  ,uint64_t * size
                                  ,void ** buffer
                                  ,struct adios_method_struct * method
                                  )
{
    printf("adios_dataman_get_write_buffer \n");
}


enum BUFFERING_STRATEGY adios_dataman_should_buffer (struct adios_file_struct * fd
                                                  ,struct adios_method_struct * method
                                                  )
{
    printf("adios_dataman_should_buffer \n");
    return no_buffering;
}

void adios_dataman_start_calculation (struct adios_method_struct * method)
{
    printf("adios_dataman_start_calculation \n");
}

void adios_dataman_stop_calculation (struct adios_method_struct * method)
{
    printf("adios_dataman_stop_calculation \n");
}

