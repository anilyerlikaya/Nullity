/***********************************
 * Single Layer Perceptron
 * Params: 
    ** Input Size  
    ** Activation Function Type
    ** 
 * 
 * 
*/

#include "data/data.h"

// debug - remove later!!!
#include <iostream>

namespace nl::ml {

class SLP {
private:
   Matrix2d<float> data;                                                // data features
   Array<int> labels;                                                   // data labels

   Array<float> weights;                                                // network weights

   int epochs = 10;                                                     // other network hyperparams
   
   void initialize();                                                   // initialize general 
   void initialize_weights();                                           // initialize weights
protected:
public: 
   SLP();                                                               // default constructor
   SLP(Matrix2d<float> dataset, Array<int> labels);                     // main constructor

   void forward();                                                      // forward throughout network

   ~SLP() { printf("SLP destructor\n"); }                               // destructor
};



}