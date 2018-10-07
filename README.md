# NeuralC
A simple c++ implementation of Neural Networks and optimization algorithms.

## How to compile and run
In linux:
1. Build with `make all`.
2. To run the program use `./bin/release/neuralc`.
3. To install use `sudo cp ./bin/release/neuralc /bin/`
   
In windows: Well, i still don't know :(

## Console interface

```
neuralc [COMMANDS] [OPTIONS]

COMMANDS:
    -N    --new: creates a new neural network.
    -T    --train: Uses gradient descent to train a network.
    -I    --input: gets a vector from the user as input and prints the output.

OPTIONS:
    -n    --name: The name of the network (can be a path).
    -l    --layers: The number of neurons in each layer, separated by "/", i.e.: (2, 8, 1)=2/8/1.
    -d    --data: The name/path to the file with the data to train the network.
    -t    --threads: Number of threads to use.
    -i    --iterations: Number of iterations for the gradient descent.

EXAMPLE
    (1) Create the neural network: neuralc -N -n MyNet -l 2/8/1
    (2) Train it with the data in data.txt: neuralc -T -n MyNet -d data.txt -t 4 -i 1000000
    (3) Try the now trained network: neuralc -I 0.9/-0.45 -n MyNet
```

## API Reference
Just include `include/NeuralC.h` in your project. To create a new network type `Network n = Network(vector <int> layers)`.