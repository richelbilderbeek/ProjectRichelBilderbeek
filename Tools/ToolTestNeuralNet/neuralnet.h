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
#ifndef NEURALNET_H
#define NEURALNET_H
//---------------------------------------------------------------------------
#include <Array/Array.h>
#include <ReClaM/FFNet.h>
//---------------------------------------------------------------------------
///NeuralNet is a derived class of FFNet
///to gain access to some protected methods of FFNet
struct NeuralNet : public FFNet
{
  NeuralNet(
    const int n_inputs,
    const int n_hidden_neurons,
    const int n_outputs);

  ///Copy constructor
  NeuralNet(const NeuralNet& n);
  ///Assignment operator
  NeuralNet& operator=(const NeuralNet& n);

  ///Propagate creates the output of a neural network for certain inputs
  std::vector<double> Propagate(const std::vector<double> &inputs) const;

  std::vector<int> GetConnections() const;
  int GetNumberOfInputs() const;
  int GetNumberOfHiddenNeurons() const;
  int GetNumberOfNeurons() const;
  int GetNumberOfOutputs() const;

  ///Read the output value from any neuron
  double GetOutputValue(const int index) const;

  std::vector<double> GetWeights() const;
  void Mutate(const double m);

  static const std::string GetVersion() { return "1.0"; }

  private:
  ///Wrapper method due to clumsy createConnectionMatrix behavior
  Array<int> CreateConnectionMatrix(
    const int n_inputs,
    const int n_hidden_neurons,
    const int n_outputs) const;
  int m_number_of_inputs;
  int m_number_of_hidden_neurons;
  int m_number_of_outputs;

  ///Activate uses default FFNet::activate method
  ///Use Propagate instead
  void Activate(const Array<double> &inputs) const;

  ///Use Propagate instead
  std::vector<double> PropagateArray(const Array<double> &inputs) const;

  ///Read the output from the output layer from this neural network
  ///Use Propagate instead
  std::vector<double> GetOutputLayerOutputValues() const;

  void Swap(NeuralNet& rhs);

  friend bool operator==(const NeuralNet& lhs, const NeuralNet& rhs);
};
//---------------------------------------------------------------------------
bool operator==(const NeuralNet& lhs, const NeuralNet& rhs);
//---------------------------------------------------------------------------
///GetRandomUniform draws a random number in range [0,1>
///From http://www.richelbilderbeek.nl/CppGetRandomUniform.htm
double GetRandomUniform();
//---------------------------------------------------------------------------
template <class T>
std::vector<T> ConvertToVector(const Array<T> a)
{
  return std::vector<T>(a.begin(),a.end());
}
//---------------------------------------------------------------------------
template <class T>
Array<T> ConvertToArray(const std::vector<T>& v)
{
  Array<T> a;
  std::vector<T> v_copy(v); //This is terrible!
  a.append_elems(v_copy);
  return a;
}
//---------------------------------------------------------------------------
#endif // NEURALNET_H
