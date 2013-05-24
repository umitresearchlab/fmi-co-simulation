#ifndef SIMULATE_H
#define SIMULATE_H

#include <fmilib.h>
#include <stdio.h>

#include "main.h"

/// @brief Sets the initial values for the given FMU. It simply reads from XML and does setXXX() in the FMU.
void setInitialValues1(fmi1_import_t* fmu, fmi1_import_variable_list_t* vl);
void setInitialValues2(fmi2_import_t* fmu, fmi2_import_variable_list_t* vl);

/// @brief Set initial values from the command line, overrides the XML init values
void setParams1(int numFMUs, int numParams, fmi1_import_t ** fmus, param params[MAX_PARAMS]);
void setParams2(int numFMUs, int numParams, fmi2_import_t ** fmus, param params[MAX_PARAMS]);

/**
 * @brief Simulate the given FMUs.
 * @param fmus The FMUs to simulate
 * @param fmuPaths Filenames of the FMUs
 * @param numFMUs The number of FMUs
 * @param connections
 * @param numConnections
 * @param params
 * @param numParams
 * @param tEnd
 * @param timeStep
 * @param loggingEnabled
 * @param csvSeparator
 * @param callbacks
 * @param quietModeEnabled If nonzero, no extra output to stdout is made
 * @param stepfunc Stepping algorithm to use
 * @param outFileFormat Which output file format to use
 * @param outFilePath Out file path
 * @param realTimeModeEnabled If the execution of a system step was faster than the timeStep, a sleep will be made the remaining time.
 * @param numSteps The resulting number of steps
 * @param numStepOrder Number of elements in stepOrder
 * @param stepOrder Array of FMU indices, indicating which order to step and transfer values from.
 * @returns Zero on success, else an error code.
 */
int fmi1simulate(   fmi1_import_t** fmus,
                    char fmuPaths[MAX_FMUS][PATH_MAX],
                    int numFMUs,
                    fmi1_import_variable_list_t** variables,
                    connection connections[MAX_CONNECTIONS],
                    int numParams,
                    param params[MAX_PARAMS],
                    int numConnections,
                    double tEnd,
                    double timeStep,
                    int loggingEnabled,
                    char csvSeparator,
                    jm_callbacks callbacks,
                    int quietModeEnabled,
                    fmi1stepfunction stepfunc,
                    int printToFile,
                    enum FILEFORMAT outFileFormat,
                    char outFilePath[PATH_MAX],
                    int realTimeModeEnabled,
                    int * numSteps,
                    int numStepOrder,
                    int stepOrder[MAX_STEP_ORDER]);

/**
 * @todo
 */
int fmi2simulate(   fmi2_import_t** fmus,
                    char fmuPaths[MAX_FMUS][PATH_MAX],
                    int numFMUs,
                    fmi2_import_variable_list_t** variables,
                    connection connections[MAX_CONNECTIONS],
                    int numParameters,
                    param params[MAX_PARAMS],
                    int numConnections,
                    double tEnd,
                    double timeStep,
                    int loggingOn,
                    char separator,
                    jm_callbacks callbacks,
                    int quiet,
                    fmi2stepfunction stepfunc,
                    int printToFile,
                    enum FILEFORMAT outFileFormat,
                    char outFilePath[PATH_MAX],
                    int realTimeMode,
                    int * numSteps,
                    int numStepOrder,
                    int stepOrder[MAX_STEP_ORDER]);

#endif /* SIMULATE_H */