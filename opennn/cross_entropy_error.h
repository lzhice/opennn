//   OpenNN: Open Neural Networks Library
//   www.opennn.net
//
//   C R O S S   E N T R O P Y   E R R O R   C L A S S   H E A D E R
//
//   Artificial Intelligence Techniques SL
//   artelnics@artelnics.com

#ifndef CROSSENTROPYERROR_H
#define CROSSENTROPYERROR_H

// System includes

#include <iostream>
#include <fstream>
#include <math.h>

// OpenNN includes

#include "loss_index.h"
#include "data_set.h"



#include "tinyxml2.h"

namespace OpenNN
{

/// This class represents the cross entropy error term, used for predicting probabilities.

///
/// This functional is used in classification problems.

class CrossEntropyError : public LossIndex
{

public:

   // DEFAULT CONSTRUCTOR

   explicit CrossEntropyError();

   // NEURAL NETWORK CONSTRUCTOR

   explicit CrossEntropyError(NeuralNetwork*);

   // DATA SET CONSTRUCTOR

   explicit CrossEntropyError(DataSet*);

   explicit CrossEntropyError(NeuralNetwork*, DataSet*);

   // XML CONSTRUCTOR

   explicit CrossEntropyError(const tinyxml2::XMLDocument&);

   // COPY CONSTRUCTOR

   CrossEntropyError(const CrossEntropyError&);

   virtual ~CrossEntropyError();

   // Error methods

   double calculate_batch_error(const Vector<size_t>&) const;
   double calculate_batch_error(const Vector<size_t>&, const Vector<double>&) const;

   // Gradient methods

   FirstOrderLoss calculate_first_order_loss(const DataSet::Batch&) const;

   void calculate_first_order_loss(const DataSet::Batch& batch,
                                         const NeuralNetwork::ForwardPropagation& forward_propagation,
                                         FirstOrderLoss& first_order_loss) const
   {
    #ifdef __OPENNN_DEBUG__

    check();

    #endif

        // Data set

        const size_t batch_instances_number = batch.input_data.get_dimension(0);

        // Neural network

        const size_t layers_number = neural_network_pointer->get_trainable_layers_number();

        // Loss index

        calculate_output_gradient(forward_propagation.layers[layers_number-1].activations,
                                  batch.target_data);

        calculate_layers_delta(forward_propagation, first_order_loss);
/*
        const Vector<double> batch_error_gradient = calculate_error_gradient(batch.input_data, forward_propagation, layers_delta);

        first_order_loss.loss = cross_entropy_error(forward_propagation[layers_number-1].activations, batch.target_data);

        first_order_loss.gradient = batch_error_gradient/static_cast<double>(batch_instances_number);

        // Regularization

        if(regularization_method != RegularizationMethod::NoRegularization)
        {
            first_order_loss.loss += regularization_weight*calculate_regularization();
            first_order_loss.gradient += calculate_regularization_gradient()*regularization_weight;
        }
*/
   }

   Tensor<double> calculate_output_gradient(const Tensor<double>&, const Tensor<double>&) const;

   void calculate_output_gradient(const Tensor<double>& outputs, const Tensor<double>& targets, Tensor<double>& output_gradient) const
   {
        #ifdef __OPENNN_DEBUG__

        check();

        #endif

        output_gradient = (targets/outputs)*(-1.0) + (targets*(-1.0) + 1.0)/(outputs*(-1.0) + 1.0);
   }


   string get_error_type() const;
   string get_error_type_text() const;

   // Serialization methods

   tinyxml2::XMLDocument* to_XML() const;   
   void from_XML(const tinyxml2::XMLDocument&);

   void write_XML(tinyxml2::XMLPrinter&) const;
};

}

#endif


// OpenNN: Open Neural Networks Library.
// Copyright(C) 2005-2020 Artificial Intelligence Techniques, SL.
//
// This library is free software; you can redistribute it and/or
// modify it under the terms of the GNU Lesser General Public
// License as published by the Free Software Foundation; either
// version 2.1 of the License, or any later version.
//
// This library is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
// Lesser General Public License for more details.

// You should have received a copy of the GNU Lesser General Public
// License along with this library; if not, write to the Free Software
// Foundation, Inc., 51 Franklin St, Fifth Floor, Boston, MA  02110-1301  USA
