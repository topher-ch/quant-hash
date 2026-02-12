#pragma once

namespace quant_hash {
    class Permutation {
    public:
        Permutation();

        // Public API
        void setState() const;
        void getState() const;
        void apply();

    private:
        // Internal round functions
        void theta();
        void rho();
        void pi();
        void chi();
        void iota();
    };  
}