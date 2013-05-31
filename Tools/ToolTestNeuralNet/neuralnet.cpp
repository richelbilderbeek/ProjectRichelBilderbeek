//---------------------------------------------------------------------------
/*
NeuralNet, a three-layered perceptron class
Copyright (C) 2010 Richel Bilderbeek

This program is free software: you can redistribute it and/or modify
it under the terms of the GNU General Public License as published by
the Free Software Foundation, either version 3 of the License, or
(at your option) any later version.

This program is distributed in the hope that it will be useful,
but WITHOUT ANY WARRANTY; without even the implied warranty of
MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.See the
GNU General Public License for more details.
You should have received a copy of the GNU General Public License
along with this program.If not, see <http://www.gnu.org/licenses/>.
*/
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppNeuralNet.htm
//---------------------------------------------------------------------------
#include <cassert>
#include <cstdlib>
//---------------------------------------------------------------------------
#include <boost/numeric/conversion/cast.hpp>
#include <boost/foreach.hpp>
//---------------------------------------------------------------------------
#include <ReClaM/createConnectionMatrix.h>
//---------------------------------------------------------------------------
#include "neuralnet.h"
//---------------------------------------------------------------------------
NeuralNet::NeuralNet(
  const int n_inputs,
  const int n_hidden_neurons,
  const int n_outputs)
  : FFNet(
    n_inputs,
    n_outputs,
    CreateConnectionMatrix(n_inputs,n_hidden_neurons,n_outputs)),
    m_number_of_inputs(n_inputs),
    m_number_of_hidden_neurons(n_hidden_neurons),
    m_number_of_outputs(n_outputs)
{
  assert(boost::numeric_cast<int>(this->numberOfNeurons)
    == m_number_of_inputs
     + m_number_of_hidden_neurons
     + m_number_of_outputs
    && "Assume no neurons are lost in translation");
  assert(boost::numeric_cast<int>(this->numberOfNeurons)
    == this->GetNumberOfNeurons()
      && "Assume GetNumberOfNeurons() works fine");
}
//---------------------------------------------------------------------------
///Calls FFNet's copy constructor
NeuralNet::NeuralNet(const NeuralNet& n)
  : FFNet(n),
    m_number_of_inputs(n.m_number_of_inputs),
    m_number_of_hidden_neurons(n.m_number_of_hidden_neurons),
    m_number_of_outputs(n.m_number_of_outputs)
{
  //Cannot assert this internally, because it causes
  //an infinite function call stack
  //assert(n == *this);
}
//---------------------------------------------------------------------------
  ///Assignment operator
NeuralNet& NeuralNet::operator=(const NeuralNet& other)
{
  NeuralNet temp(other);
  Swap(temp);
  return *this;
}
//---------------------------------------------------------------------------
void NeuralNet::Swap(NeuralNet& other)
{
  std::swap(m_number_of_inputs,other.m_number_of_inputs);
  std::swap(m_number_of_hidden_neurons,other.m_number_of_hidden_neurons);
  std::swap(m_number_of_outputs,other.m_number_of_outputs);
  //Pray this works
  std::swap(connectionMatrix,other.connectionMatrix);
  std::swap(weightMatrix,other.weightMatrix);
}
//---------------------------------------------------------------------------
Array<int> NeuralNet::CreateConnectionMatrix(
  const int n_inputs,
  const int n_hidden,
  const int n_outputs) const
{
  Array<int> m;
  createConnectionMatrix(m,n_inputs, n_hidden, n_outputs);
  return m;
}
//---------------------------------------------------------------------------
///Activate uses default FFNet::activate method
///FFNet::activate is not a const method
///The code below proofs that the FFNet is not
///changed, so this method could have been a const-method.
///Prefer to use the const-correct Propagate method
void NeuralNet::Activate(const Array<double> &inputs) const
{
  //I promise not to change anything
  NeuralNet * const n = const_cast<NeuralNet*>(this);

  #define CHECK_ARCHITECTURE_762347632476
  #ifdef  CHECK_ARCHITECTURE_762347632476
  const NeuralNet before(*this);
  #endif

  n->activate(inputs);

  #ifdef  CHECK_ARCHITECTURE_762347632476
  const NeuralNet after(*this);
  assert(before == after
    && "Proof that neural net does not change");
  #endif
}
//---------------------------------------------------------------------------
std::vector<int> NeuralNet::GetConnections() const
{
  #define CHECK_ARCHITECTURE_165254
  #ifdef  CHECK_ARCHITECTURE_165254
  {
    //Read the original connection matrix
    const Array<int> a_copy = this->connectionMatrix;
    //I promise not to change this NeuralNet
    NeuralNet * n = const_cast<NeuralNet*>(this);
    const Array<int> a = n->getConnections();
    assert(a == a_copy);
  }
  #endif

  const std::vector<int> v = ConvertToVector(this->connectionMatrix);
  return v;
}
//---------------------------------------------------------------------------
int NeuralNet::GetNumberOfInputs() const
{
  return m_number_of_inputs;
}
//---------------------------------------------------------------------------
int NeuralNet::GetNumberOfHiddenNeurons() const
{
  return m_number_of_hidden_neurons;
}
//---------------------------------------------------------------------------
int NeuralNet::GetNumberOfNeurons() const
{
  return boost::numeric_cast<int>(this->numberOfNeurons);
}
//---------------------------------------------------------------------------
int NeuralNet::GetNumberOfOutputs() const
{
  return m_number_of_outputs;
}
//---------------------------------------------------------------------------
std::vector<double> NeuralNet::GetWeights() const
{
  const std::vector<double> v = ConvertToVector(this->weightMatrix);
  return v;
}
//---------------------------------------------------------------------------
double NeuralNet::GetOutputValue(const int index) const
{
  assert(index >= 0 && index < this->GetNumberOfNeurons());
  //I promise not to change anything
  NeuralNet * const n = const_cast<NeuralNet*>(this);
  const double output = n->outputValue(index);
  return output;
}
//---------------------------------------------------------------------------
std::vector<double> NeuralNet::GetOutputLayerOutputValues() const
{
  std::vector<double> v;

  int i = GetNumberOfInputs() + GetNumberOfHiddenNeurons();
  assert(i == m_number_of_inputs + m_number_of_hidden_neurons);
  const int j = this->GetNumberOfNeurons();
  assert(i<=j);

  v.reserve(j-i);

  for ( ; i!=j; ++i)
  {
    const double x = this->GetOutputValue(i);
    v.push_back(x);
  }

  assert(boost::numeric_cast<int>(v.size())
    == this->GetNumberOfOutputs());

  return v;
}
//---------------------------------------------------------------------------
///Due to funny Array behavior, it is needed
///to implement Mutate a bit clumsily
void NeuralNet::Mutate(const double m)
{
  Array<double> weights = this->getWeights();
  BOOST_FOREACH(double& x,weights)
  {
    x+= (GetRandomUniform() * (2.0 * m)) - m;
  }
  this->weightMatrix = weights;
}
//---------------------------------------------------------------------------
///Propagate creates the output of a neural network for certain inputs
std::vector<double> NeuralNet::PropagateArray(const Array<double> &inputs) const
{
  //I promise not to change anything
  NeuralNet * const n = const_cast<NeuralNet*>(this);
  //Activate the neural network
  this->Activate(inputs);
  //Obtain the output layer's output
  std::vector<double> v = n->GetOutputLayerOutputValues();
  assert(boost::numeric_cast<int>(v.size())
    == this->GetNumberOfOutputs());
  return v;
}
//---------------------------------------------------------------------------
std::vector<double> NeuralNet::Propagate(const std::vector<double> &inputs) const
{
  const Array<double> a = ConvertToArray(inputs);
  return this->PropagateArray(a);
}
//---------------------------------------------------------------------------
//Cannot call methods, because it causes
//an infinite function call stack:
bool operator==(const NeuralNet& lhs, const NeuralNet& rhs)
{
  return (
     lhs.m_number_of_inputs == rhs.m_number_of_inputs
  && lhs.m_number_of_hidden_neurons == rhs.m_number_of_hidden_neurons
  && lhs.m_number_of_outputs == rhs.m_number_of_outputs
  && lhs.connectionMatrix == rhs.connectionMatrix
  && lhs.weightMatrix == rhs.weightMatrix);
}
//---------------------------------------------------------------------------
//From http://www.richelbilderbeek.nl/CppGetRandomUniform.htm
double GetRandomUniform()
{
  return static_cast<double>(std::rand())/static_cast<double>(RAND_MAX);
}
//---------------------------------------------------------------------------
