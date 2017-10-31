/*
 This function was automatically generated by the Matlab script generate_mavlink_sfun.m on 23-Oct-2017 11:50:04

 S-Function to encode a MAVLink message from Simulink bus to uint8 vector.

 (c) Aditya Joshi, Oct 2017
 */

#define S_FUNCTION_NAME  sfun_decode_mavlink
#define S_FUNCTION_LEVEL 2

#include "simstruc.h"

// MAVLINK SPECIFIC CODE =======================================================

// System and Component IDs for MAVLink communication
#define SYS_ID 100
#define COMP_ID 200

#include "D:/simulink_mavlink/include/mavlink/v1.0/common/mavlink.h"

// Output message 1
#include "D:/simulink_mavlink/include/sfun_mavlink_msg_attitude.h"
#define OUTPUT_BUS_NAME_1 BUS_NAME_ATTITUDE
#define NFIELDS_OUTPUT_BUS_1 NFIELDS_BUS_ATTITUDE
#define encode_output_businfo_1(x, y) encode_businfo_attitude(x, y)
#define decode_output_msg1(x, y, z) decode_msg_attitude(x, y, z)

// END MAVLINK SPECIFIC CODE ===================================================


/* Function: mdlInitializeSizes ================================================
 * REQUIRED METHOD
 * Abstract:
 *    The sizes information is used by Simulink to determine the S-function
 *    block's characteristics (number of inputs, outputs, states, etc.).
 */
static void mdlInitializeSizes(SimStruct *S)
{

    DECL_AND_INIT_DIMSINFO(inputDimsInfo);
    DECL_AND_INIT_DIMSINFO(outputDimsInfo);

    ssSetNumSFcnParams(S, 0);
    if (ssGetNumSFcnParams(S) != ssGetSFcnParamsCount(S)) {
        return; /* Parameter mismatch will be reported by Simulink */
    }

    if (!ssSetNumInputPorts(S, 1)) return;

    ssSetInputPortDirectFeedThrough(S, 0, 1);
    ssSetInputPortRequiredContiguous(S, 0, 1);
    ssSetInputPortDataType(S, 0, SS_UINT8);
    ssSetInputPortVectorDimension(S, 0, MAVLINK_MAX_PACKET_LEN);

    if (!ssSetNumOutputPorts(S, 1)) return;

    /* Register bus datatypes for Output ports */
    #if defined(MATLAB_MEX_FILE)
    if (ssGetSimMode(S) != SS_SIMMODE_SIZES_CALL_ONLY)
    {
      DTypeId dataTypeIdReg;
      ssRegisterTypeFromNamedObject(S, OUTPUT_BUS_NAME_1, &dataTypeIdReg);
      if(dataTypeIdReg == INVALID_DTYPE_ID) return;
        ssSetOutputPortDataType(S, 0, dataTypeIdReg);
    }
    #endif

    ssSetBusOutputObjectName(S, 0, (void *) OUTPUT_BUS_NAME_1);
    ssSetOutputPortWidth(S, 0, 1);
    ssSetBusOutputAsStruct(S, 0, 1);
    ssSetOutputPortBusMode(S, 0, SL_BUS_MODE);

    ssSetNumSampleTimes(S, 1);

    /* specify the sim state compliance to be same as a built-in block */
    ssSetSimStateCompliance(S, USE_DEFAULT_SIM_STATE);

    ssSetOptions(S, 0);   /* general options (SS_OPTION_xx) */

} /* end mdlInitializeSizes */


/* Function: mdlInitializeSampleTimes ==========================================
 * REQUIRED METHOD
 * Abstract:
 *    This function is used to specify the sample time(s) for your
 *    S-function. You must register the same number of sample times as
 *    specified in ssSetNumSampleTimes.
 */
static void mdlInitializeSampleTimes(SimStruct *S)
{
    /* Register one pair for each sample time */
    ssSetSampleTime(S, 0, INHERITED_SAMPLE_TIME);
    ssSetOffsetTime(S, 0, 0.0);
    ssSetModelReferenceSampleTimeDefaultInheritance(S);

} /* end mdlInitializeSampleTimes */

/* Function: mdlStart ==========================================================
 * Abstract:
 *    This function is called once at start of model execution. If you
 *    have states that should be initialized once, this is the place
 *    to do it.
 */
#define MDL_START
static void mdlStart(SimStruct *S)
{
    int_T *busInfo = (int_T *) malloc(2*NFIELDS_OUTPUT_BUS_1*sizeof(int_T));
    if(busInfo == NULL) {
      ssSetErrorStatus(S, "Memory allocation failure");
      return;
    }

    encode_output_businfo_1(S, busInfo);
    ssSetUserData(S, busInfo);
} /* end mdlStart */


/* Function: mdlOutputs ========================================================
 * REQUIRED METHOD
 * Abstract:
 *    In this function, you compute the outputs of your S-function
 *    block.
 */
static void mdlOutputs(SimStruct *S, int_T tid)
{

    int_T len_uvec = ssGetInputPortWidth(S, 0);
    const uint8_T* uvec = (uint8_T*) ssGetInputPortSignal(S, 0);
    char *yvec = (char *) ssGetOutputPortSignal(S, 0);
    int_T* busInfo = (int_T *) ssGetUserData(S);

    mavlink_message_t msg;
    mavlink_status_t status;

    for (int uidx = 0; uidx < len_uvec; uidx++) {
      if(mavlink_parse_char(MAVLINK_COMM_0, uvec[uidx], &msg, &status)) {
        decode_output_msg1(&msg, busInfo, yvec);
      }
    }

}

/* Function: mdlTerminate ======================================================
 * REQUIRED METHOD
 * Abstract:
 *    In this function, you should perform any actions that are necessary
 *    at the termination of a simulation.  For example, if memory was
 *    allocated in mdlStart, this is the place to free it.
 */
 static void mdlTerminate(SimStruct *S)
 {
     /* Free stored bus information */
     int_T *busInfo = (int_T *) ssGetUserData(S);
     if(busInfo != NULL) {
         free(busInfo);
     }
 }

/*=============================*
 * Required S-function trailer *
 *=============================*/

#ifdef  MATLAB_MEX_FILE    /* Is this file being compiled as a MEX-file? */
#include "simulink.c"      /* MEX-file interface mechanism */
#else
#include "cg_sfun.h"       /* Code generation registration function */
#endif
