// SortingTests.cpp : Defines the entry point for the console application.
//
#ifdef _MSC_VER
#   include "stdafx.h"
#   include <vld.h>
#   define CLNAME "Visual Studio"
#elif defined __GNUG__
#   ifdef __clang__
#       define CLNAME "Clang++"
#   elif
#       define CLNAME "GNU G++"
#   endif
#endif

#include "gtest/gtest.h"
#include "algorithms.h"
#include <vector>
#include <chrono>
#include <random>
#include <iostream>
#include <algorithm>

int main(int argc, char *argv[])
{
	std::cout << "Running main() from SortingTests.cpp\n";
	testing::InitGoogleTest(&argc, argv);
	return RUN_ALL_TESTS();
}

namespace sorting_tests
{
	/// <summary>
	/// Generates random values to be sorted.
	/// </summary>
	template <typename X> 
	static void GenerateValues(std::vector<X> &values)
	{
		std::random_device randomDevice;				
		std::ranlux24_base randomEngine(randomDevice());
		std::uniform_real_distribution<double> uniformDistribution(0, 1.0);

		std::generate(values.begin(), values.end(), [&] ()
		{
			return uniformDistribution(randomEngine) * values.size();
		});
	}

	class Sorting_TestCase : public ::testing::TestWithParam<size_t> { };

	/// <summary>
	/// Tests the algorithms for quick and merge sort.
	/// </summary>
	TEST_P(Sorting_TestCase, QuickAndMergeSort_Test)
	{
		using namespace std::chrono;

		std::vector<int> values(GetParam());

		// Quick sort:

		GenerateValues(values);

		auto startTime = system_clock::now();
		Algorithms::DoQuickSort(values);
		auto endTime = system_clock::now();

        EXPECT_TRUE( std::is_sorted(values.begin(), values.end()) );

		std::cout << ">>> Recursive quick sort for " << GetParam() << " numbers took " << duration_cast<milliseconds> (endTime - startTime).count() << " milliseconds." << std::endl;

		// Recursive merge sort:

		GenerateValues(values);

		startTime = system_clock::now();
		Algorithms::DoMergeSort(values);
		endTime = system_clock::now();

        EXPECT_TRUE( std::is_sorted(values.begin(), values.end()) );

		std::cout << ">>> Iterative merge sort for " << GetParam() << " numbers took " << duration_cast<milliseconds> (endTime - startTime).count() << " milliseconds." << std::endl;

        // Toolchain STL implementation for std::sort for benchmark:

		GenerateValues(values);

		startTime = system_clock::now();
		std::sort(values.begin(), values.end());
		endTime = system_clock::now();

		EXPECT_TRUE( std::is_sorted(values.begin(), values.end()) );

        std::cout << ">>> " << CLNAME << " STL sort for " << GetParam() << " numbers took " << duration_cast<milliseconds> (endTime - startTime).count() << " milliseconds." << std::endl;
	}

	INSTANTIATE_TEST_CASE_P(QuickAndMergeSort_Test, 
							Sorting_TestCase, 
							::testing::Values(1e5, 5e5, 25e5, 50e5));
}
