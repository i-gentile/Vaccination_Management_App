#include <string.h>
#include <assert.h>
#include <stdlib.h>
#include "appointment.h"

// Initializes a vaccination appointment data list
void appointmentData_init(tAppointmentData* list) {
    //////////////////////////////////
    // Ex PR3 1a
    /////////////////////////////////
    assert(list != NULL);
    list->count = 0;
    list->elems = NULL;
}

// Insert a new vaccination appointment
void appointmentData_insert(tAppointmentData* list, tDateTime timestamp, tVaccine* vaccine, tPerson* person) {
    //////////////////////////////////
    // Ex PR3 1b
    /////////////////////////////////
    int insert_pos = -1;
    int i;
    
    // Check input data
    assert(list != NULL);
    assert(vaccine != NULL);
    assert(person != NULL);
    
    // Allocate memory for new element
    if (list->count == 0) {
        // Request new memory space
        list->elems = (tAppointment*) malloc(sizeof(tAppointment));
    } else {
        // Modify currently allocated memory
        list->elems = (tAppointment*) realloc(list->elems, (list->count + 1) * sizeof(tAppointment));
    }
    assert(list->elems != NULL);
    
    // Search insertion point
    for(i=0; i < list->count && insert_pos < 0; i++) {        
        // Check the date and time
        if(dateTime_cmp(timestamp, list->elems[i].timestamp) < 0 || 
            (dateTime_cmp(timestamp, list->elems[i].timestamp) == 0 && strcmp(person->document, list->elems[i].person->document) < 0)) {
            // This is the insertion position
            insert_pos = i;
        }
    }
    
    // In case insertion point is not found, set as last element
    if(insert_pos < 0) { 
        insert_pos = list->count;
    }
    
    // Increase the size of the list
    list->count += 1;
            
    // Displace all elements from end to the insertion position    
    for(i=list->count - 1; i>insert_pos; i--) {
        list->elems[i] = list->elems[i-1];
    }            
    
    // Finally add the new element
    list->elems[insert_pos].timestamp = timestamp;
    list->elems[insert_pos].person = person;
    list->elems[insert_pos].vaccine = vaccine;
}

// Remove a vaccination appointment
void appointmentData_remove(tAppointmentData* list, tDateTime timestamp, tPerson* person) {
    //////////////////////////////////
    // Ex PR3 1c
    /////////////////////////////////
    bool found = false;
    int i;
    
    // Check input data
    assert(list != NULL);
    assert(person != NULL);
    
    // Transverse the list of appointments and displace in case element is found
    for(i=0; i < list->count; i++) {
        // Check if current element is the element we are looking for
        if ( dateTime_equals(list->elems[i].timestamp, timestamp) && strcmp(list->elems[i].person->document, person->document) == 0) {
            found = true;
        }
        // If the element is found, make a displacement
        if (found && i < (list->count - 1) ) {
            list->elems[i] = list->elems[i+1];
        }
    }
    
    // In case the element was found, resize the elements
    if (found) {
        list->count--;
        if (list->count == 0) {
            // Empty list
            free(list->elems);
            list->elems = NULL;
        } else {
            // Modify currently allocated memory
            list->elems = (tAppointment*) realloc(list->elems, list->count * sizeof(tAppointment));
            assert(list->elems != NULL);
        }        
    }
}

// Find the first instance of a vaccination appointment for given person
int appointmentData_find(tAppointmentData list, tPerson* person, int start_pos) {
    //////////////////////////////////
    // Ex PR3 1d
    /////////////////////////////////
    int pos;
    
    // Check input data
    assert(person != NULL);
    
    // Trivial cases
    if (start_pos >= list.count) {
        // Trivial case 1: Start position larger than number of elements
        pos = -1;
    } else if(strcmp(list.elems[start_pos].person->document, person->document) == 0) {
        // Trivial case 2: Current position is the element we are looking for
        pos = start_pos;
    } else {
        // Recursive call
        pos = appointmentData_find(list, person, start_pos + 1);
    }
    
    return pos;
}

// Release a vaccination appointment data list
void appointmentData_free(tAppointmentData* list) {
    //////////////////////////////////
    // Ex PR3 1e
    /////////////////////////////////
    assert(list != NULL);
    if (list->elems != NULL) {
        // Release memory
        free(list->elems);        
    }
    list->elems = NULL;
    list->count = 0;
}
