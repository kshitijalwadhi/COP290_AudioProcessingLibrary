#ifndef audio_h
#define audio_h
#include "matrices.h"
#include "activationFns.h"
#include "subsampling.h"
#include "utils.h"
#include "dnn.cpp"
#include "dnn_weights.h"
struct pred_t
{
    int label;
    float prob;
};

extern pred_t* libaudioAPI(const char* audiofeatures, pred_t* pred);

#endif