#include <iostream>
#include "montant_lettres.hpp"

int main() {
    std::cout << "=== TEST DU MODULE EIS ===" << std::endl;

    std::cout << "1000 : "
              << montant_en_lettres(1000) << std::endl;

    std::cout << "5000 : "
              << montant_en_lettres(5000) << std::endl;

    std::cout << "25000 : "
              << montant_en_lettres(25000) << std::endl;

    std::cout << "100000 : "
              << montant_en_lettres(100000) << std::endl;

    return 0;
}










