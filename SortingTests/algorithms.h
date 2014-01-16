#include <vector>
#include <chrono>
#include <thread>
#include <algorithm>

namespace sorting_tests
{
	/// <summary>
	/// A collection of sorting algorithms.
	/// </summary>
	class Algorithms
	{
	public:

		template <typename X> 
		static void DoQuickSort(std::vector<X> &v);

		template <typename X> 
		static void DoMergeSort(std::vector<X> &v);
	};


	/////////////////////////
	// Quicksort
	/////////////////////////

	/// <summary>
	/// Gets the partition value estimate.
	/// </summary>
	/// <param name="startIter">The first iterator in the container of values.</param>
	/// <param name="endIter">The iterator for one past the last position in the container of values.</param>
	/// <returns>
	/// An estimatived partition value based on random samples from the container.
	/// </returns>
	template <typename X> 
	static X EstimatePartitionValue(const typename std::vector<X>::iterator &startIter,
									const typename std::vector<X>::iterator &endIter)
	{
		auto size = std::distance(startIter, endIter);

		if(size > 2)
		{
			auto sampleA = *startIter; 
			auto sampleB = *(startIter + size/2);
			auto sampleC = *(endIter - 1); 
			return (sampleA + sampleB + sampleC) / 3;
		}
		else if(size == 2)
		{
			auto sampleA = *startIter;
			auto sampleB = *(endIter - 1); 
			return (sampleA + sampleB) / 2;
		}
		else
			return *startIter;
	}

	/// <summary>
	/// Implements the recursive body of the quick sort algorithm.
	/// </summary>
	/// <param name="startIter">The iterator for the starting position in the partition.</param>
	/// <param name="endIter">The iterator for one past the last position in the partition.</param>
	template <typename X> 
	static void DoQuickSortImpl(typename std::vector<X>::iterator &startIter, 
								typename std::vector<X>::iterator &endIter)
	{
		if(std::distance(startIter, endIter) > 1)
		{
			auto estPartVal = EstimatePartitionValue<X>(startIter, endIter);

			auto leftIter = startIter;
			auto rightIter = endIter - 1;

			do
			{
				while(*leftIter < estPartVal && std::distance(leftIter, rightIter) > 1)
					++leftIter;

				while(*rightIter > estPartVal && std::distance(leftIter, rightIter) > 1)
					--rightIter;

				// Swap values:
				if(*leftIter > *rightIter)
				{
					auto temp = *leftIter;
					*leftIter = *rightIter;
					*rightIter = temp;
				}
				
				if(*leftIter <= estPartVal)
					++leftIter;
				else
					--rightIter;
			}
			while(leftIter != rightIter);
			/*
			std::for_each(startIter, leftIter, [] (X x) { std::cout << x << " "; });
			std::cout << "and ";
			std::for_each(rightIter, endIter, [] (X x) { std::cout << x << " "; });
			std::cout << " with partition value " << estPartVal << std::endl;
			*/
			DoQuickSortImpl<X>(startIter, leftIter);
			DoQuickSortImpl<X>(rightIter, endIter);
		}
	}

	/// <summary>
	/// Does the quicksort.
	/// </summary>
	/// <param name="v">The vector whose values must be sorted.</param>
	template <typename X> 
	void Algorithms::DoQuickSort(std::vector<X> &v)
	{
		DoQuickSortImpl<X>(v.begin(), v.end());
	}


	/////////////////////////
	// Merge Sort
	/////////////////////////

	/// <summary>
	/// Does the merge sort using iterations.
	/// </summary>
	/// <param name="v">The vector whose values must be sorted.</param>
	template <typename X> 
	void Algorithms::DoMergeSort(std::vector<X> &v)
	{
		if(v.size() > 1)
		{
			std::vector<X> temp(v.size());

			// Scan the vector in groups whose size go up exponentially:
			for(size_t groupSize = 1; groupSize < v.size(); groupSize *= 2)
			{
				size_t idx;

				// Merge the groups in pairs:
				for(idx = 0; idx + groupSize < v.size(); idx += 2 * groupSize)
				{
					// The first group has always the size of a power of 2:
					auto iter1Begin = v.begin() + idx;
					auto iter1End = iter1Begin + groupSize;

					// But the second group might encounter the end of the vector before reaching the size of the previous group:
					auto iter2Begin = iter1End; // begins where the previous group ends
					auto iter2End = (v.size() - idx < 2 * groupSize) ? v.end() : iter2Begin + groupSize;

					// Finally merge the groups into the temporary storage:
					std::merge(iter1Begin, iter1End, 
							   iter2Begin, iter2End, 
							   temp.begin() + idx);
				}

				// If the last scan left the vector before reaching its end because the last group did not have a pair:
				if(v.size() > idx)
				{
					// Just copy the remainder so as to be available for the next iteration:
					std::copy(v.begin() + idx, // begins reading where the last loop left
							  v.end(), // ends reading in the very end of the vector
							  temp.begin() + idx); // write in the corresponding positions of the temp storage
				}

				v.swap(temp); // before the next iteration save the merge result, which is in the temp storage
			}
		}
	}
}