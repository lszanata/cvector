#include <stdlib.h>

#include "svector.h"

// Allocate and zero initialize vector
int svector_set(svector *cvector, size_t initial_length)
{
    /*
     * Other possible methods to allocate and clear the array:
     * 
     * Using malloc (requires manually clearing the array after allocation):
     * 
     * cvector->data = (char *)malloc(initial_length * sizeof(char));
     * for (cvector->index = 0; cvector->index < initial_length; cvector->index++)
     * {
     *     cvector->data[cvector->index] = '\0';
     * }
     * 
     * Using memset (requires string.h):
     * 
     * memset(cvector->data, 0, initial_length * (sizeof(cvector->data[cvector->index])));
     */

    // Allocates the array and initializes all bits to zero
    cvector->data = (char *)calloc(initial_length, sizeof(char));

    //if ((cvector->data = (char *)calloc(initial_length, sizeof(char))) == NULL)
    if (cvector->data == NULL)
    {
        return SV_ALLOC_ERROR;
    }
    else
    {
        cvector->length = initial_length;
        cvector->index = 0;

        switch (initial_length)
        {
        case SV_INITIAL_LENGTH_ONE:
            cvector->resize_rate = SV_RESIZE_RATE_ONE;
            cvector->max_length = SV_MAX_LENGTH_ONE;
            break;
        case SV_INITIAL_LENGTH_TWO:
            cvector->resize_rate = SV_RESIZE_RATE_TWO;
            cvector->max_length = SV_MAX_LENGTH_TWO;
            break;
        }
    }

    return 0;
}

// Append data into vector and resize it if necessary
int svector_add(svector *cvector, char *element)
{
    if (cvector->index == (cvector->length - 1))
    {
        // if (cvector->length < SV_MAX_LENGTH_ONE)
        if (cvector->length < cvector->max_length)
        {
            // cvector->length += SV_RESIZE_RATE_ONE;
            cvector->length += cvector->resize_rate;
            cvector->data = (char *)realloc(cvector->data, cvector->length * sizeof(char));

            for (unsigned int i = cvector->index; i < cvector->length; i++)
            {
                cvector->data[i] = '\0';
            }
        }
        else
        {
            return SV_CAP_ERROR;
        }
    }

    cvector->data[cvector->index++] = *element;

    return 0;
}

// Concatenate string with vector and resize it if necessary
// void concatStrVector(svector *destination, char *source)
//{
//	while (*source != '\0')
//	{
//		appendStrVector(destination, source);
//		source++;
//	}
//}

// Clear and reset vector
void svector_clear(svector *cvector)
{
    for (cvector->index = 0; cvector->index < cvector->length; cvector->index++)
    {
        cvector->data[cvector->index] = '\0';
    }
    cvector->index = 0;
}

// Deallocate vector
void svector_free(svector *cvector)
{
    // cvector->data = NULL;
    free(cvector->data);
    cvector->length = 0;
    cvector->index = 0;
    cvector->max_length = 0;
    cvector->resize_rate = 0;
}
