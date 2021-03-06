//
// Commit initial : FP with ranges (Using C++17 with range-v3 : https://www.cjdb.com.au/a-prime-opportunity-for-ranges) - 30/09/2018
// Commit en cours : 05/12/2020 - Exemples tirés de l'ouvrage d'Ivan Cukic "FP in C++"
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @
// Paramétrage IDE : C/C++ Général Compilation multiprocesseur : OUI (debug/release) - C/C++ Langage C++17
// Compilation en 32 bits car la bibliothèque range-v3 ne passe a priori pas en 64 bits (répertoire include : C:\Users\andre\source\vcpkg-master\installed\x86-windows\include)
// TO DO : tester les exemples avancés de Conor Hoekstra (https://github.com/codereport/Talks/tree/master/2020-09-CppCon/SICP)

// #include "pch.h"		// En-tête indispensable sous Windows et VC++

#include <iostream>
#include <vector>
#include <chrono>
#include <fstream>
#include <range/v3/all.hpp>	// Installed with vcpkg
#include <algorithm>

using namespace std;

constexpr bool diviser(int const x, int const y) noexcept { return y % x == 0; }; // not to be confused with std::divides
constexpr bool is_even(int const x) noexcept { return diviser(2, x); };
constexpr bool is_odd(int const x) noexcept { return not is_even(x); };

std::vector<unsigned int> cache{ 0,1 }; // Vecteur utilisé pour la version "cache" de Fibonacci

inline void keep_window_open() // From "std_lib_facilities.h" of BS
{
    cin.clear();
    cout << "Please enter a character to exit\n";
    char ch{};
    cin >> ch;
    return;
}

template <typename TFunc> double RunAndMeasure(TFunc func)
{
    // Retourne une durée en ms - To use : RunAndMeasure([&]() {Code to insert });
    const auto start = chrono::steady_clock::now();
    func();
    const auto end = chrono::steady_clock::now();
    return chrono::duration <double, milli>(end - start).count();

}

int count_lines(const std::string& filename)
{
    std::ifstream in(filename);

    return std::count(
        std::istreambuf_iterator<char>(in),
        std::istreambuf_iterator<char>(),
        '\n');

}

std::vector<int> count_lines_in_files(const std::vector<std::string>& files)
{
   // return files | transform(count_lines);

}


unsigned int fib(unsigned int n)
{
    // Fibonacci Numbers : version classique récursive
    return n == 0 ? 0 : n == 1 ? 1 : fib(n - 1) + fib(n - 2);

}

unsigned int fib_caching(unsigned int n)
{
    // Fibonacci Numbers : version avec cache
    if (cache.size() > n) {
        return cache[n];
    }
    else {
        const auto result = fib(n - 1) + fib(n - 2);
        cache.push_back(result);
        return result;

    }

}



int main()
{
    /*
    namespace view = ranges::view;
    
    // ********************************************************************************************************************************************************************
    // This functional snippet 'reprints' the number if it's a prime number
    auto const divisible_by_2_or_3 = [](auto const x) noexcept {
        return (x != 2) and (x != 3) and (x < 2 or is_even(x) or diviser(3, x)); };

    auto const is_prime = [divisible_by_2_or_3](auto const x) noexcept {
        auto divisors = view::iota(5)
            | view::stride(6)
            | view::take_while([x](auto const d) noexcept { return d * d < x; });
        return not divisible_by_2_or_3(x) and
            ranges::none_of(divisors, [x](auto const d) noexcept {
            return diviser(d, x) or diviser(d + 2, x);
                });
    };

    // Attente de la saisie d'un nombre : s'il est premier, il est dupliqué à l'écran
    auto primes = ranges::istream<int>(std::cin) | view::filter(is_prime);
    ranges::copy(primes, ranges::ostream_iterator<int>(std::cout, "\n"));

    // ********************************************************************************************************************************************************************
    */

    cout << "Methode classique  : " << RunAndMeasure([&]() {cout << fib(40) << endl; }) << " ms" << endl;
    cout << "Methode avec cache : " << RunAndMeasure([&]() {cout << fib_caching(40) << endl; }) << " ms" << endl; // Environ 3 fois plus rapide
    keep_window_open();





}


