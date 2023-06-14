#include <vector>

template<typename T, typename Less>
bool FindMax(std::vector<T> const& arr, T& maxValue, Less const& less)
{
	auto it = std::max_element(arr.begin(), arr.end(), less);
	if (it == arr.end())
	{
		return false;
	}
	maxValue = *it;
	return true;
};
