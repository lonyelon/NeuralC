#compilar todo el programa
cd NeuralCore
g++ --std=c++17 Network.cpp Network.h ../Main.cpp Image.h Image.cpp -o ../program
echo BUILD DONE!
cd ..

#ejecutar
./program