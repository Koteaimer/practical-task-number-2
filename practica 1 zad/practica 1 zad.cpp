#include <iostream>
#include <vector>
#include <iomanip>

using namespace std;

int main() {
	const size_t SCREEN_WIDTH = 80;
	const size_t MAX_ARSTERISK = SCREEN_WIDTH - 3 - 1;
	cerr << "Enter number count: ";
	size_t number_count;
	if (!(cin >> number_count || number_count == 0)) {
		return 0;
	}
	cerr << "Enter numbers: ";
	vector<double> numbers(number_count);
	for (size_t i = 0; i < number_count; i++) {
		cin >> numbers[i];
	}
	cerr << "Enter bin count: ";
	size_t bin_count;
	cin >> bin_count;
	for (size_t i = 0; i < numbers.size(); i++) {
		for (size_t j = i + 1; j < numbers.size();) {
			if (numbers[i] == numbers[j]) {
				numbers.erase(numbers.begin() + j);
			}
			else {
				j++;
			}
		}
	}
	cout << "Unique numbers: ";
	for (double x : numbers) {
		cout << x << " ";
	}
	cout << endl;
	if (numbers.empty() || bin_count == 0) {
		return 0;
	 }
	number_count = numbers.size();
	double min = numbers[0];
	double max = numbers[0];
	for (double x : numbers) {
		if (x < min) {
			min = x;
		}
		else if (x > max) {
			max = x;
		}
	}
	double bin_size = 0.0;
	if (max != min) {
		bin_size = (max - min) / bin_count;
	}
	vector<size_t> bins(bin_count, 0);
	for (size_t i = 0; i < number_count; i++) {
		bool found = false;
		for (size_t j = 0; (j < bin_count - 1) && !found; j++) {
			auto lo = min + j * bin_size;
			auto hi = min + (j + 1) * bin_size;
			if ((lo <= numbers[i]) && (numbers[i] < hi)) {
				bins[j]++;
				found = true;
			}
		}
		if (!found) {
			bins[bin_count - 1]++;
		}
	}
	size_t max_count = 0;
	for (size_t count : bins) {
		if (count > max_count) {
			max_count = count;
		}
	}
	for (size_t count : bins) {
		cout << setw(3) << count << "|";
		size_t height = count;
		if (max_count > MAX_ARSTERISK) {
			height = MAX_ARSTERISK * (static_cast<double>(count) / max_count);
		}
		for (size_t i = 0; i < height; i++) {
			cout << "*";
		}
		cout << endl;
	}
}