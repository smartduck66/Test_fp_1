//
// Using C++17 with range-v3 : https://www.cjdb.com.au/a-prime-opportunity-for-ranges
// This functional snippet 'reprints' the number if it's a prime number
// Commit en cours : FP with ranges - 30/09/2018
// Caractères spéciaux : [ ]   '\n'   {  }   ||   ~   _     @
// Paramétrage IDE : C/C++ Général Compilation multiprocesseur : OUI (debug/release) - C/C++ Langage C++14

#include "pch.h"		// En-tête indispensable sous Windows et VC++

#include <iostream>
#include <range/v3/all.hpp>	// Installed with vcpkg


constexpr bool divides(int const x, int const y) noexcept { return y % x == 0; }; // not to be confused with std::divides
constexpr bool is_even(int const x) noexcept { return divides(2, x); };
constexpr bool is_odd(int const x) noexcept { return not is_even(x); };



int main()
{
	
		// A mettre dans la 1ère ligne du "main" pour afficher les caractères accentués sous la console Windows
		std::locale::global(std::locale("fr-FR"));

		namespace view = ranges::view;
		auto const divisible_by_2_or_3 = [](auto const x) noexcept {
			return (x != 2) and (x != 3) and (x < 2 or is_even(x) or divides(3, x)); };

		auto const is_prime = [divisible_by_2_or_3](auto const x) noexcept {
			auto divisors = view::iota(5)
				| view::stride(6)
				| view::take_while([x](auto const d) noexcept { return d * d < x; });
			return not divisible_by_2_or_3(x) and
				ranges::none_of(divisors, [x](auto const d) noexcept {
				return divides(d, x) or divides(d + 2, x);
			});
		};

		auto primes = ranges::istream<int>(std::cin) | view::filter(is_prime);
		ranges::copy(primes, ranges::ostream_iterator<int>(std::cout, "\n"));

		
	
}
