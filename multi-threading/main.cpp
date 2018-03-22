#include <thread>
#include "donnees_kalman.cpp"


int main(int argc, char* argv[]) {
    
    std::thread Kalman(initKalman);
    Kalman.join();

}
