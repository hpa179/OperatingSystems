#include <rpc/rpc.h>
#include "avg.h"
#include <math.h>
#include <stdio.h>

static double sum, sum_avg, stddev;

double *average_1(input_data *input, CLIENT *client) {
    double *dp = input->input_data.input_data_val;
    u_int i;
    sum = 0;
    sum_avg = 0;
    for (i = 0; i < input->input_data.input_data_len; i++) {
        sum += *dp;
        sum_avg += (*dp) * (*dp);
        dp++;
    }
    double mean = sum / input->input_data.input_data_len;
    double sum1 = 0;
    for(int i = 0; i < input->input_data.input_data_len; i++) {
    sum1 += pow(mean - input->input_data.input_data_val [i], 2);
    }
    double variance = (sum1/ input->input_data.input_data_len);
    stddev = sqrt(variance);
    return(&stddev);
}
   double * average_1_svc(input_data *input, struct svc_req *svc)
  {
  CLIENT *client;
  return( average_1( input, client) );
  }
