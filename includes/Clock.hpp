/**
 * @file Clock.hpp
 * @brief Le temps qui passe, mesure par qui la possede.
 *
 * Inclus sciemment : il tire <chrono>, l'en-tete standard le plus lourd
 * de la bibliotheque.
 *
 * @addtogroup system
 * @{
 */

#pragma once

#include <chrono>


/**
 * @class Clock
 * @brief Une horloge par proprietaire. Rien ne l'impose a personne.
 */

class Clock {
    public:
        using Source = std::chrono::steady_clock;
        using Duration = Source::duration;   ///< int64 nanosecondes

        /** @brief Avance. Une fois par frame, par le proprietaire. */
        void tick() {
            const Source::time_point now = Source::now();

            /* Le premier tick ne mesure rien : sans lui, la premiere
                * frame vaudrait le temps ecoule depuis la construction. */
            if (_started) {
                _delta = scaled(now - _last);
                _total += _delta;
            }
            _started = true;
            _last = now;
        }

        /** @brief Le pas de la frame courante, exact. */
        Duration delta() const { return _delta; }

        /**
         * @brief Le total depuis le premier tick, exact.
         */
        Duration total() const { return _total; }
        
        /** 
         * @brief 0 gele, 0.25 ralentit, 2 accelere. 
         */
        void scale(double scale) { _scale = scale; }
        double scale() const { return _scale; }

    private:
        /** @brief A l'echelle 1, la duree brute passe sans arrondi. */
        Duration scaled(Duration raw) const {
            if (_scale == 1.0)
                return raw;
            return Duration(static_cast<Duration::rep>(raw.count() * _scale));
        }

        Source::time_point _last;
        Duration _delta {};
        Duration _total {};
        double _scale = 1;
        bool _started = false;

};

/** @} */
