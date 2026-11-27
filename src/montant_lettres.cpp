#include "montant_lettres.hpp"

#include <array>
#include <string>

namespace {

const std::array<std::string, 20> unites = {
    "zéro", "un", "deux", "trois", "quatre",
    "cinq", "six", "sept", "huit", "neuf",
    "dix", "onze", "douze", "treize", "quatorze",
    "quinze", "seize", "dix-sept", "dix-huit", "dix-neuf"
};

const std::array<std::string, 10> dizaines = {
    "", "", "vingt", "trente", "quarante",
    "cinquante", "soixante", "soixante", "quatre-vingt", "quatre-vingt"
};

std::string convertir_moins_de_cent(int nombre) {
    if (nombre < 20) {
        return unites[nombre];
    }

    int dizaine = nombre / 10;
    int unite = nombre % 10;

    if (dizaine == 7 || dizaine == 9) {
        return dizaines[dizaine] + "-" + unites[10 + unite];
    }

    if (dizaine == 8 && unite == 0) {
        return "quatre-vingts";
    }

    if (unite == 0) {
        return dizaines[dizaine];
    }

    if (unite == 1 && dizaine != 8) {
        return dizaines[dizaine] + " et un";
    }

    return dizaines[dizaine] + "-" + unites[unite];
}

std::string convertir_moins_de_mille(int nombre) {
    if (nombre < 100) {
        return convertir_moins_de_cent(nombre);
    }

    int centaines = nombre / 100;
    int reste = nombre % 100;

    std::string resultat;

    if (centaines == 1) {
        resultat = "cent";
    } else {
        resultat = unites[centaines] + " cent";
    }

    if (reste == 0 && centaines > 1) {
        resultat += "s";
    }

    if (reste > 0) {
        resultat += " " + convertir_moins_de_cent(reste);
    }

    return resultat;
}

std::string convertir_nombre(std::int64_t nombre) {
    if (nombre < 1000) {
        return convertir_moins_de_mille(static_cast<int>(nombre));
    }

    if (nombre < 1000000) {
        std::int64_t milliers = nombre / 1000;
        int reste = static_cast<int>(nombre % 1000);

        std::string resultat;

        if (milliers == 1) {
            resultat = "mille";
        } else {
            resultat = convertir_nombre(milliers) + " mille";
        }

        if (reste > 0) {
            resultat += " " + convertir_moins_de_mille(reste);
        }

        return resultat;
    }

    if (nombre < 1000000000) {
        std::int64_t millions = nombre / 1000000;
        int reste = static_cast<int>(nombre % 1000000);

        std::string resultat = convertir_nombre(millions) + " million";

        if (millions > 1) {
            resultat += "s";
        }

        if (reste > 0) {
            resultat += " " + convertir_nombre(reste);
        }

        return resultat;
    }

    std::int64_t milliards = nombre / 1000000000;
    std::int64_t reste = nombre % 1000000000;

    std::string resultat = convertir_nombre(milliards) + " milliard";

    if (milliards > 1) {
        resultat += "s";
    }

    if (reste > 0) {
        resultat += " " + convertir_nombre(reste);
    }

    return resultat;
}

} // namespace

std::string montant_en_lettres(std::int64_t montant) {
    if (montant < 0) {
        return "moins " + convertir_nombre(-montant) + " francs CFA";
    }

    return convertir_nombre(montant) + " francs CFA";
}
