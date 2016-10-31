#include <stdio.h>
#include <dlfcn.h>
#include "core/adios_transport_hooks.h"
#include "public/adios_types.h"

void *so = 0;
void (*write_func)(const void *data) = 0;
void (*init_func)() = 0;
int (*open_func)() = 0;

void check_library(){
    if (!so) so=dlopen("./libdataman.so",RTLD_NOW);
    if (!so) printf("libdataman.so not found\n");

    if (!init_func) init_func=dlsym(so,"dataman_init_c");
    if (!init_func) printf("dataman_init_c not found in libdataman.so\n");
    if (!open_func) open_func=dlsym(so,"dataman_open_c");
    if (!open_func) printf("dataman_open_c not found in libdataman.so\n");
    if (!write_func) write_func=dlsym(so,"dataman_write_c");
    if (!write_func) printf("dataman_write_c not found in libdataman.so\n");
}


void adios_dataman_init (const PairStruct * parameters
                      ,struct adios_method_struct * method
                      )
{
    printf("adios_dataman.c: adios_dataman_init \n");
    check_library();
    init_func();
}

int adios_dataman_open (
        struct adios_file_struct * fd,
        struct adios_method_struct * method,
        MPI_Comm comm)
{
    printf("adios_dataman.c: adios_dataman_open \n");
    check_library();
    return open_func();
}

enum BUFFERING_STRATEGY adios_dataman_should_buffer (struct adios_file_struct * fd
                                                  ,struct adios_method_struct * method
                                                  )
{
    return no_buffering;
}

void adios_dataman_write(
    struct adios_file_struct *fd,
    struct adios_var_struct *f,
    const void *data,
    struct adios_method_struct *method)
{
    printf("adios_dataman.c: adios_dataman_write \n");
    check_library();
    write_func(data);
}

void adios_dataman_close (struct adios_file_struct * fd
                       ,struct adios_method_struct * method
                       )
{
}

void adios_dataman_finalize (int mype, struct adios_method_struct * method)
{
    printf("adios_dataman_finalize \n");
    if (so) dlclose(so);
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

void adios_dataman_start_calculation (struct adios_method_struct * method)
{
    printf("adios_dataman_start_calculation \n");
}

void adios_dataman_stop_calculation (struct adios_method_struct * method)
{
    printf("adios_dataman_stop_calculation \n");
}

