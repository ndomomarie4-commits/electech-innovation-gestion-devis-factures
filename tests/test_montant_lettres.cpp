#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "doctest.h"

#include <cstdint>
#include <limits>
#include <stdexcept>
#include <string>

#include "montant_lettres.hpp"

// --- CT-02 : tableau du cahier des charges, ligne par ligne -----------------

TEST_CASE("CT-02 : nombres de 21 à 91") {
    CHECK(nombre_en_lettres(21) == "vingt et un");
    CHECK(nombre_en_lettres(71) == "soixante et onze");
    CHECK(nombre_en_lettres(80) == "quatre-vingts");
    CHECK(nombre_en_lettres(81) == "quatre-vingt-un");
    CHECK(nombre_en_lettres(91) == "quatre-vingt-onze");
}

TEST_CASE("CT-02 : centaines") {
    CHECK(nombre_en_lettres(180) == "cent quatre-vingts");
    CHECK(nombre_en_lettres(200) == "deux cents");
    CHECK(nombre_en_lettres(201) == "deux cent un");
}

TEST_CASE("CT-02 : milliers") {
    CHECK(nombre_en_lettres(80000) == "quatre-vingt mille");
    CHECK(nombre_en_lettres(180000) == "cent quatre-vingt mille");
    CHECK(nombre_en_lettres(200000) == "deux cent mille");
}

TEST_CASE("CT-02 : millions") {
    CHECK(nombre_en_lettres(1988000) == "un million neuf cent quatre-vingt-huit mille");
    CHECK(nombre_en_lettres(2000000) == "deux millions");
    CHECK(nombre_en_lettres(5594500) ==
          "cinq millions cinq cent quatre-vingt-quatorze mille cinq cents");
}

// --- CT-01 : total TTC du devis de référence --------------------------------

TEST_CASE("CT-01 : montant TTC du devis de référence") {
    CHECK(montant_en_lettres(894017) ==
          "huit cent quatre-vingt-quatorze mille dix-sept francs CFA");
}

// --- Cas limites et règles d'orthographe ------------------------------------

TEST_CASE("zéro, un et petits nombres") {
    CHECK(nombre_en_lettres(0) == "zéro");
    CHECK(nombre_en_lettres(1) == "un");
    CHECK(nombre_en_lettres(10) == "dix");
    CHECK(nombre_en_lettres(16) == "seize");
    CHECK(nombre_en_lettres(17) == "dix-sept");
    CHECK(nombre_en_lettres(20) == "vingt");
    CHECK(nombre_en_lettres(22) == "vingt-deux");
    CHECK(nombre_en_lettres(31) == "trente et un");
    CHECK(nombre_en_lettres(60) == "soixante");
    CHECK(nombre_en_lettres(70) == "soixante-dix");
    CHECK(nombre_en_lettres(72) == "soixante-douze");
    CHECK(nombre_en_lettres(77) == "soixante-dix-sept");
    CHECK(nombre_en_lettres(90) == "quatre-vingt-dix");
    CHECK(nombre_en_lettres(99) == "quatre-vingt-dix-neuf");
}

TEST_CASE("cent et ses accords") {
    CHECK(nombre_en_lettres(100) == "cent");
    CHECK(nombre_en_lettres(101) == "cent un");
    CHECK(nombre_en_lettres(300) == "trois cents");
    CHECK(nombre_en_lettres(380) == "trois cent quatre-vingts");
    CHECK(nombre_en_lettres(999) == "neuf cent quatre-vingt-dix-neuf");
}

TEST_CASE("mille est invariable et ne prend jamais « un » devant lui") {
    CHECK(nombre_en_lettres(1000) == "mille");
    CHECK(nombre_en_lettres(1001) == "mille un");
    CHECK(nombre_en_lettres(2000) == "deux mille");
    CHECK(nombre_en_lettres(81000) == "quatre-vingt-un mille");
    CHECK(nombre_en_lettres(100000) == "cent mille");
    CHECK(nombre_en_lettres(300000) == "trois cent mille");
}

TEST_CASE("million et milliard prennent un s au pluriel") {
    CHECK(nombre_en_lettres(1000000) == "un million");
    CHECK(nombre_en_lettres(1200000) == "un million deux cent mille");
    CHECK(nombre_en_lettres(200000000) == "deux cents millions");
    CHECK(nombre_en_lettres(80000000) == "quatre-vingts millions");
    CHECK(nombre_en_lettres(1000000000) == "un milliard");
    CHECK(nombre_en_lettres(3000000000LL) == "trois milliards");
}

TEST_CASE("plus grande valeur d'un std::int64_t") {
    CHECK(nombre_en_lettres(std::numeric_limits<std::int64_t>::max()) ==
          "neuf trillions deux cent vingt-trois billiards trois cent soixante-douze billions "
          "trente-six milliards huit cent cinquante-quatre millions sept cent soixante-quinze "
          "mille huit cent sept");
}

// --- Montants en FCFA --------------------------------------------------------

TEST_CASE("montant_en_lettres : unité monétaire") {
    CHECK(montant_en_lettres(0) == "zéro franc CFA");
    CHECK(montant_en_lettres(1) == "un franc CFA");
    CHECK(montant_en_lettres(2) == "deux francs CFA");
    CHECK(montant_en_lettres(1000) == "mille francs CFA");
    CHECK(montant_en_lettres(25000) == "vingt-cinq mille francs CFA");
    CHECK(montant_en_lettres(1988000) ==
          "un million neuf cent quatre-vingt-huit mille francs CFA");
}

TEST_CASE("anomalie A1 : 1 988 000 ne doit jamais s'écrire « un million neuf cent "
          "quatre-vingt-dix-huit mille »") {
    CHECK(montant_en_lettres(1988000) !=
          "un million neuf cent quatre-vingt-dix-huit mille francs CFA");
}

// --- Robustesse (EOO-02, EOO-07) ---------------------------------------------

TEST_CASE("un montant négatif lève une exception") {
    CHECK_THROWS_AS(nombre_en_lettres(-1), std::invalid_argument);
    CHECK_THROWS_AS(montant_en_lettres(-2), std::invalid_argument);
    CHECK_THROWS_AS(montant_en_lettres(std::numeric_limits<std::int64_t>::min()),
                    std::invalid_argument);
}
