#include <fmilib.h>
#include <stdio.h>

#include "main.h"
#include "utils.h"

int fmi2JacobiStep(     double time,
                        double communicationTimeStep,
                        int numFMUs,
                        fmi2_import_t ** fmus,
                        fmi2_import_variable_list_t** variables,
                        int numConnections,
                        connection connections[MAX_CONNECTIONS],
                        int numStepOrder,
                        int stepOrder[MAX_STEP_ORDER]){
    int ci, i;

    // Step all the FMUs
    fmi2_status_t status = fmi2_status_ok;
    for(i=0; i<numFMUs; i++){
        fmi2_status_t s = fmi2_import_do_step (fmus[i], time, communicationTimeStep, 1);
        if(s != fmi2_status_ok){
            status = s;
            printf("doStep() of FMU %d didn't return fmiOK! Exiting...\n",i);
            return 1;
        }
    }

    for(ci=0; ci<numConnections; ci++){ // Loop over connections
        fmi2TransferConnectionValues(connections[ci], fmus, variables);
    }

    return 0;
}

/**
 * Jacobi is a stepping method where we step the subsystems in parallel.
 * The order of connections will therefore not matter.
 */
int fmi1JacobiStep( double time,
                    double communicationTimeStep,
                    int numFMUs,
                    fmi1_import_t ** fmus,
                    fmi1_import_variable_list_t** variables,
                    int numConnections,
                    connection connections[MAX_CONNECTIONS],
                    int numStepOrder,
                    int stepOrder[MAX_STEP_ORDER]){
    int ci, i;

    // Step all the FMUs
    fmi1_status_t status = fmi1_status_ok;
    for(i=0; i<numFMUs; i++){
        fmi1_status_t s = fmi1_import_do_step (fmus[i], time, communicationTimeStep, 1);
        if(s != fmi1_status_ok){
            status = s;
            printf("doStep() of FMU %d didn't return fmiOK! Exiting...\n",i);
            return 1;
        }
    }

    for(ci=0; ci<numConnections; ci++){ // Loop over connections
        fmi1TransferConnectionValues(connections[ci], fmus, variables);
    }

    return 0;
}