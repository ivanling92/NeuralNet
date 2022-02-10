// NeuralNet1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//Source: https://stackoverflow.com/questions/2019056/getting-a-simple-neural-network-to-work-from-scratch-in-c
//By https://stackoverflow.com/users/24039/simon

#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <vector>

using namespace std;

class perceptron
{
public:
	perceptron(float eta, int epochs)
	{
		m_epochs = epochs; // We set the private variable m_epochs to the user selected value
		m_eta = eta;
		
	}
	float netInput(vector<float> X)
	{
		// Sum(Vector of weights * Input vector) + bias
		float probabilities = m_w[0]; // In this example I am adding the perceptron first
		for (int i = 0; i < X.size(); i++)
		{
			probabilities += X[i] * m_w[i + 1]; // Notice that for the weights I am counting
			// from the 2nd element since w0 is the bias and I already added it first.
		}
		return probabilities;
	}
	int predict(vector<float> X)
	{
		return netInput(X) > 0 ? 1 : -1; //Step Function
	}
	void fit(vector< vector<float> > X, vector<float> y)
	{
		for (int i = 0; i < X[0].size() + 1; i++) // X[0].size() + 1 -> I am using +1 to add the bias term
		{
			m_w.push_back(0); // Setting each weight to 0 and making the size of the vector
			// The same as the number of features (X[0].size()) + 1 for the bias term
		}
		for (int i = 0; i < m_epochs; i++) // Iterating through each epoch
		{
			int errors = 0;
			for (int j = 0; j < X.size(); j++) // Iterating though each vector in our training Matrix
			{
				float update = m_eta * (y[j] - predict(X[j])); //we calculate the change for the weights
				for (int w = 1; w < m_w.size(); w++) { 
					m_w[w] += update * X[j][w - 1];  // we update each weight by the update * the training sample
					}
				m_w[0] = update; // We update the Bias term and setting it equal to the update
				errors += update != 0 ? 1 : 0;
				cout << "Training: " << update << endl;
			}
			m_errors.push_back(errors);
			cout << "Epoch " << i << endl;
		}
	}

	void printErrors()
	{
		for (float e : m_errors)
		{
			cout << e << endl;
		}
	}


private:
	float m_eta;
	int m_epochs;
	vector <float> m_w;
	vector <float> m_errors;

};


vector<string> split(const string &s, char delim) {
	vector<string> result;
	stringstream ss(s);
	string item;

	while (getline(ss, item, delim)) {
		result.push_back(item);
	}

	return result;
}


int main()
{
    
	vector<vector<float>> X;
	vector<float> y;
	string line;
	vector<string> data;
	ifstream myfile("test1.csv");
	if (myfile.is_open())
	{
		vector<int> dataarr;
		while (getline(myfile, line))
		{
			data = split(line, ',');
			for (int i = 0; i < 4; i++)
			{
				dataarr.push_back(data[i]);
				//cout << stof(data[i]);
				cout << data[i] << " | ";
			}
			cout << data[5];
			//X.push_back(dataarr);
			//y.push_back(stof(data[5]));
			cout << "X-" << endl;
		}
		myfile.close();
	}
	else
	{
		cout << "File not found";
	}

	cout << "Hello World!\n";
	perceptron clf(0.1, 1000);
	clf.fit(X, y);
	clf.printErrors();

}


