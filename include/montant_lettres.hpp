/**
 * @file montant_lettres.hpp
 * @brief Conversion d'un montant entier en toutes lettres (orthographe française).
 *
 * Module indépendant de toute couche : aucun SQL, aucune entrée/sortie console
 * (exigence EOO-06). Les montants sont des entiers exacts (EOO-05).
 */
#ifndef MONTANT_LETTRES_HPP
#define MONTANT_LETTRES_HPP

#include <cstdint>
#include <string>

/**
 * @brief Écrit un nombre entier positif ou nul en lettres, sans unité.
 *
 * Exemples : 21 -> « vingt et un », 80 -> « quatre-vingts »,
 * 80000 -> « quatre-vingt mille », 200 -> « deux cents ».
 *
 * @param nombre Nombre à convertir (>= 0).
 * @return Le nombre en lettres, en minuscules.
 * @throws std::invalid_argument si @p nombre est négatif.
 */
std::string nombre_en_lettres(std::int64_t nombre);

/**
 * @brief Écrit un montant en FCFA en lettres, suivi de « francs CFA ».
 *
 * Exemple : 894017 -> « huit cent quatre-vingt-quatorze mille dix-sept francs CFA ».
 * Le mot « franc » reste au singulier pour 0 et 1.
 *
 * @param montant Montant en FCFA (>= 0).
 * @return Le montant en lettres, en minuscules.
 * @throws std::invalid_argument si @p montant est négatif.
 */
std::string montant_en_lettres(std::int64_t montant);

#endif  // MONTANT_LETTRES_HPP
