#include <stdexcept>

class InvalidOption : public runtime_error
{
public:
    InvalidOption() : std::runtime_error("Invalid option!") {}
};

class PokemonNotFound : public runtime_error
{
public:
    PokemonNotFound() : std::runtime_error("Pokémon not found") {}
};

class RepeatedType : public runtime_error
{
public:
    RepeatedType() : std::runtime_error("Each Pokemon must have a different type!") {}
};
