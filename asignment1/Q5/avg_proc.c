#include <rpc/rpc.h>
#include "avg.h"
#include <math.h>
#include <stdio.h>

static double sum, sum_avg, stddev;

int compare(const void *a, const void *b) {
    double diff = *(double *)a - *(double *)b;
    if (diff > 0) return 1;
    if (diff < 0) return -1;
    return 0;
}
input_data *average_1(input_data *input, CLIENT *client) {
    double *dp = input->input_data.input_data_val;
    u_int i;
    sum = 0;
    sum_avg = 0;
   /* for (i = 0; i < input->input_data.input_data_len; i++) {
        sum += *dp;
        sum_avg += (*dp) * (*dp);
        dp++;
    }*/    
   // int compare = 0;
qsort(input->input_data.input_data_val, input->input_data.input_data_len, sizeof(double), compare);
    return input;
}
   input_data * average_1_svc(input_data *input, struct svc_req *svc)
  {
  CLIENT *client;
  return( average_1( input, client) );
  }
