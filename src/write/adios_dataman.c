#include <stdio.h>
#include <dlfcn.h>
#include "core/adios_transport_hooks.h"
#include "core/adios_internals.h"
#include "public/adios_types.h"

void *so = NULL;
void (*init_func)() = NULL;
int  (*open_func)() = NULL;
void (*write_func)(const void *data, const char *name, const char *var, const char *type, uint64_t *putshape, uint64_t *varshape, uint64_t *offsets) = NULL;
void (*close_func)() = NULL;
void (*term_func)() = NULL;

void adios_dataman_check_library(){
    if (!so) so=dlopen("./libdataman.so",RTLD_NOW);
    if (!so) printf("libdataman.so not found\n");

    if (!init_func) init_func=dlsym(so,"dataman_init_c");
    if (!init_func) printf("dataman_init_c not found in libdataman.so\n");

    if (!open_func) open_func=dlsym(so,"dataman_prepare_c");
    if (!open_func) printf("dataman_prepare_c not found in libdataman.so\n");

    if (!write_func) write_func=dlsym(so,"dataman_write_c");
    if (!write_func) printf("dataman_write_c not found in libdataman.so\n");

    if (!close_func) close_func=dlsym(so,"dataman_flush_c");
    if (!close_func) printf("dataman_flush_c not found in libdataman.so\n");

    if (!term_func) term_func=dlsym(so,"dataman_terminate_c");
    if (!term_func) printf("dataman_terminate_c not found in libdataman.so\n");
}


void adios_dataman_init (const PairStruct * parameters
                      ,struct adios_method_struct * method
                      )
{
    printf("adios_dataman.c: adios_dataman_init \n");
    adios_dataman_check_library();
    init_func();
}

int adios_dataman_open (
        struct adios_file_struct * fd,
        struct adios_method_struct * method,
        MPI_Comm comm)
{
    printf("adios_dataman.c: adios_dataman_open \n");
    adios_dataman_check_library();
    return open_func();
}

enum BUFFERING_STRATEGY adios_dataman_should_buffer (struct adios_file_struct * fd
                                                  ,struct adios_method_struct * method
                                                  )
{
    return no_buffering;
}

void adios_dataman_write(
    struct adios_file_struct *f,
    struct adios_var_struct *v,
    const void *data,
    struct adios_method_struct *method)
{
    printf("adios_dataman.c: adios_dataman_write \n");
    adios_dataman_check_library();

    // data type
    char type[20]="unknown";
    switch (v->type){
        case adios_real:
            sprintf(type, "float");
            break;
        case adios_integer:
            sprintf(type, "int");
            break;
        default:
            break;
    }

    // dimensions
    struct adios_dimension_struct * d = v->dimensions;
    int ndims=count_dimensions(v->dimensions);
    uint64_t putshape[ndims+1], offsets[ndims+1], varshape[ndims+1];
    uint8_t dims_count = 0;

    putshape[0]=ndims;
    varshape[0]=ndims;
    offsets[0]=ndims;
    if(ndims){
        while(d){
            dims_count++;
            uint64_t dim;
            //local dimension
            dim = adios_get_dim_value (&d->dimension);
            putshape[dims_count]=dim;
            //global dimension
            dim = adios_get_dim_value (&d->global_dimension);
            varshape[dims_count]=dim;
            //local offsets
            dim = adios_get_dim_value (&d->local_offset);
            offsets[dims_count]=dim;
            d=d->next;
        }
    }

    /*
    int i;
    printf("ndims=%d\n", ndims);
    for(i=0; i<ndims+1; i++)
        printf("varshape[%d]=%d, putshape[%d]=%d, offset[%d]=%d\n", i, varshape[i], i, putshape[i], i, offsets[i] );
    */

    write_func(data, f->name, v->name, type, putshape, varshape, offsets);
}

void adios_dataman_close (struct adios_file_struct * fd
                       ,struct adios_method_struct * method
                       )
{
    printf("adios_dataman_flush \n");
    close_func();
}

void adios_dataman_finalize (int mype, struct adios_method_struct * method)
{
    printf("adios_dataman_finalize \n");
    term_func();
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

