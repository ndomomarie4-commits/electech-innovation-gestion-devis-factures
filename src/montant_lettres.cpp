#include "montant_lettres.hpp"

#include <array>
#include <stdexcept>
#include <vector>

namespace {

constexpr std::int64_t BASE_GROUPE = 1000;      // on découpe le nombre par tranches de 3 chiffres
constexpr int CENT = 100;
constexpr int DIX = 10;
constexpr int VINGT = 20;
constexpr int INDEX_MILLE = 1;                  // tranche des milliers
constexpr int DIZAINE_SOIXANTE_DIX = 7;
constexpr int DIZAINE_QUATRE_VINGT = 8;
constexpr int DIZAINE_QUATRE_VINGT_DIX = 9;
constexpr int PREMIERE_DIZAINE_SIMPLE = 2;      // vingt, trente, ... soixante

constexpr std::array<const char*, 20> UNITES = {
    "zéro", "un", "deux", "trois", "quatre", "cinq", "six", "sept", "huit", "neuf",
    "dix", "onze", "douze", "treize", "quatorze", "quinze", "seize",
    "dix-sept", "dix-huit", "dix-neuf"};

constexpr std::array<const char*, 5> DIZAINES = {
    "vingt", "trente", "quarante", "cinquante", "soixante"};

constexpr std::array<const char*, 7> NOMS_TRANCHES = {
    "", "mille", "million", "milliard", "billion", "billiard", "trillion"};

/// Écrit n (1..99). @p pluriel_final ajoute le « s » de « quatre-vingts ».
std::string moins_de_cent(int n, bool pluriel_final) {
    if (n < VINGT) {
        return UNITES[static_cast<std::size_t>(n)];
    }
    const int dizaine = n / DIX;
    const int unite = n % DIX;

    if (dizaine == DIZAINE_SOIXANTE_DIX) {
        if (unite == 1) {
            return "soixante et onze";
        }
        return std::string("soixante-") + UNITES[static_cast<std::size_t>(DIX + unite)];
    }
    if (dizaine == DIZAINE_QUATRE_VINGT) {
        if (unite == 0) {
            return pluriel_final ? "quatre-vingts" : "quatre-vingt";
        }
        return std::string("quatre-vingt-") + UNITES[static_cast<std::size_t>(unite)];
    }
    if (dizaine == DIZAINE_QUATRE_VINGT_DIX) {
        return std::string("quatre-vingt-") + UNITES[static_cast<std::size_t>(DIX + unite)];
    }
    const std::string base = DIZAINES[static_cast<std::size_t>(dizaine - PREMIERE_DIZAINE_SIMPLE)];
    if (unite == 0) {
        return base;
    }
    if (unite == 1) {
        return base + " et un";
    }
    return base + "-" + UNITES[static_cast<std::size_t>(unite)];
}

/// Écrit n (1..999). @p pluriel_final ajoute le « s » de « deux cents » et « quatre-vingts ».
std::string moins_de_mille(int n, bool pluriel_final) {
    const int centaines = n / CENT;
    const int reste = n % CENT;
    std::string texte;

    if (centaines > 0) {
        if (centaines > 1) {
            texte += UNITES[static_cast<std::size_t>(centaines)];
            texte += " ";
        }
        texte += "cent";
        if (centaines > 1 && reste == 0 && pluriel_final) {
            texte += "s";
        }
    }
    if (reste > 0) {
        if (centaines > 0) {
            texte += " ";
        }
        texte += moins_de_cent(reste, pluriel_final);
    }
    return texte;
}

}  // namespace

std::string nombre_en_lettres(std::int64_t nombre) {
    if (nombre < 0) {
        throw std::invalid_argument("nombre_en_lettres : le nombre doit être positif ou nul");
    }
    if (nombre == 0) {
        return UNITES[0];
    }

    // Découpage en tranches de 3 chiffres, de la plus faible à la plus forte.
    std::vector<int> tranches;
    for (std::int64_t reste = nombre; reste > 0; reste /= BASE_GROUPE) {
        tranches.push_back(static_cast<int>(reste % BASE_GROUPE));
    }

    std::string texte;
    for (std::size_t i = tranches.size(); i-- > 0;) {
        const int valeur = tranches[i];
        if (valeur == 0) {
            continue;
        }
        std::string morceau;
        if (i == 0) {
            morceau = moins_de_mille(valeur, true);
        } else if (i == static_cast<std::size_t>(INDEX_MILLE)) {
            // « mille » est invariable et « cent »/« vingt » restent au singulier devant lui.
            morceau = (valeur == 1) ? "mille" : moins_de_mille(valeur, false) + " mille";
        } else {
            // « million », « milliard »... sont des noms : ils prennent un « s » et
            // le nombre qui les précède s'accorde (« deux cents millions »).
            morceau = moins_de_mille(valeur, true) + " " + NOMS_TRANCHES[i];
            if (valeur > 1) {
                morceau += "s";
            }
        }
        if (!texte.empty()) {
            texte += " ";
        }
        texte += morceau;
    }
    return texte;
}

std::string montant_en_lettres(std::int64_t montant) {
    const std::string lettres = nombre_en_lettres(montant);
    return lettres + (montant > 1 ? " francs CFA" : " franc CFA");
}
