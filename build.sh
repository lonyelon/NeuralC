#compilar todo el programa
cd NeuralCore
g++ --std=c++17 -pthread Network.cpp Network.h ../Main.cpp Image.h Image.cpp NeuralMath.h NeuralMath.cpp Save.h Save.cpp Optimization.h Optimization.cpp -o ../program
echo BUILD DONE!
cd ..

#ejecutar
./program