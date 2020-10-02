//332, 101, 160, 196, 209, 242, 249, 250, 346, 420


13.f----------------------------------------------------------------------------------------------------------

#include <iostream>

/*
pre: {N >= 0 and N = length(nums)}
proc sort(inout int nums[], int N)
post: {for every i, j: 0 <= i < counter and counter <= j < N: nums[i] >= 0 and nums[j] < 0}

best case: all positive numbers
		main for loop body: 2
		total: 1 + N*(2 + 1 + 1) + 1 = 4N + 2 -> Linear complexity O(N)

worst case: all negative numbers
		inner for loop body: 10
		inner for loop: (N - i - 1) * (10 + 4) + 1 + 3 = 14N - 14i - 10
		if: 14N - 14i - 10 + 3 = 14N - 14i - 7
		total: N * (14N - 14i - 7 + 2) + 1 + 1 = 14N^2 - 14Ni - 5N + 2 -> Quadratic complexity O(N^2)

invariant: 0 <= i <= N

función cota: N - i > 0
*/

const int MAX = 100000;

void sort(int nums[], int N) {
	int tmp;
	bool found;
	for (int i = 0; i < N; i++) {
		if (nums[i] < 0) {
			found = false;
			for (int j = N - 1; j > i && !found; j--) {
				if (nums[j] >= 0) {
					found = true;
					tmp = nums[j];
					nums[j] = nums[i];
					nums[i] = tmp;
				}
			}
		}
	}
}

int main() {
	int cases, N, nums[MAX], counter;

	std::cin >> cases;
	while (cases--) {
		std::cin >> N;
		for (int i = 0; i < N; i++) {
			std::cin >> nums[i];
		}
		counter = N;
		sort(nums, N);
		for (int i = 0; i < N; i++) {
			if (nums[i] < 0 && counter == N)
				counter = i;
			std::cout << nums[i] << " ";
		}
		std::cout << std::endl << counter << std::endl;
	}
	return 0;
}


13.g-------------------------------------------------------------------------------------------------------------

#include <iostream>
/*
pre: {n >= 0 and n = length(v) and v[i] != -1: 0 <= i <= 100000}
func tamSegmentoMaximo(int v[], int n) return int km1
post: {km1 = max km2: km2 = sum i: v[i] == v[i+1]}

invariant: 0 <= i <= n and km1 >= km2

best case: no equals
		else: 2
		total: n + (n-1)*(2 + 1) + 1 = 4n - 2 -> Linear complexity O(n)

worst case: all equals
		if: 4
		else: 3
		total: n + (n-1)*(1) + (n-2)*(4) + 1 + 3 = 6n - 5 -> Linear complexity O(n)
*/

const int MAX = 100000;

int tamSegmentoMaximo(int v[], int n) {
	int km1 = 0, km2 = 0;
	for (int i = 0; i < n; i++) {
		if (v[i] == v[i + 1]) 
				km2++;
		else {
			if (km2 > km1)
				km1 = km2;
			km2 = 0;
		}
	}
	return km1;
}

int main() {
	int v[MAX], n = 0, sol;
	std::cin >> v[n];
	while (v[n] != -1) {
		do {
			std::cin >> v[++n];
		} while (v[n] != -1);
		sol = tamSegmentoMaximo(v, n);
		if (sol != 0)
			std::cout << sol << std::endl;
		else
			std::cout << "HOY NO COMEN" << std::endl;
		n = 0;
		std::cin >> v[n];
	}
}


13.h----------------------------------------------------------------------------------------------------------

#include <iostream>

/*
pre:
func algoOcurre(int d, int n) return bool creciente && divertido
post:

invariante: 0 <= i <= N

función de cota: N - i

best case: decreciente desde el principio
		if creciente: 4
		for body: 1 + 4 + 1 + 1 + 1 = 8
		for: 2 * 3 + 8 + 1 = 15
		while: (n-3)*(2) = 2n - 6
		total: 3 + 15 + 2n - 6 = 2n + 12 -> Linear complexity O(n)

worst case: creciente, n-divertido y todos el mismo número
		if divertido: 3
		for body: 1 + 3 + 3 + 1 = 8
		for: (n-1)*3 + (n-2)*(8+1) = 12n - 21
		total: 3 + 12n - 21 = 12n - 18 -> Linear complexity O(n)
*/

bool algoOcurre(int d, int n) {
	int first, second, tmp = 1, i = 0;
	bool creciente = true, divertido = true;
	std::cin >> first;
	for (i; i < n - 1 && creciente && divertido; i++) {
		std::cin >> second;
		if (first != second && first + 1 != second) creciente = false; //could do creciente = first != second || first + 1 != second;
		if (first == second) {
			if (++tmp > d) divertido = false; //could do divertido = ++tmp > d;
		}
		else
			tmp = 1;
		first = second;
	}
	while (i < n - 1) {
		std::cin >> first;
		i++;
	}
	return creciente && divertido;
}

int main() {
	int cases, n, d;
	std::cin >> cases;
	while (cases--) {
		std::cin >> d >> n;
		if (algoOcurre(d, n))
			std::cout << "SI" << std::endl;
		else
			std::cout << "NO" << std::endl;
	}
	return 0;
}


13.j-------------------------------------------------------------------------------------------------------------

#include <iostream>

int main() {
	long long int fib1, fib2, tmp;
	int num;

	std::cin >> num;
	while (num != -1) {
		fib1 = 0;
		fib2 = 1;
		for (int i = 0; i < num; i++) {
			tmp = fib2;
			fib2 += fib1;
			fib1 = tmp;
		}
		std::cout << fib1 << std::endl;
		std::cin >> num;
	}

	return 0;
}


13.k------------------------------------------------------------------------------------------------------------

#include <iostream>

/*
pre: {numwagons >= 0 and numwagons = length(wagons) and stealnum <= numwagons}
func steal()
post: {max = max actual: actual = sum wagons (if i >= 1: from i - 1 to i + stealnum - 1) or (if i = 0: from 0 to stealnum - 1): 0 <= i <= numwagons - stealnum}

Best case: max in the first wagon and stealnum = numwagons
		First for: 1 + N*(3 + 1) + (N + 1)*1 = 5N + 2
		Total = 1 + 5N + 2 + 2 + 1 + 2 = 5N + 8 -> Linear complexity -> O(n)

Worst case: max in the final wagon and stealnum = 1
		First for: 1 + 2*1 + 1*(1 + 3) = 7
		If: 3
		Second for loop body: 8 + 3 + 1 = 12 
		Second for loop: 1 + (N + 1)*2 + N*12 = 14N + 3
		Total: 1 + 7 + 2 + 14N + 3 = 14N + 13 -> Linear complexity -> O(n)

Invariant: i <= numwagons - stealnum + 1 and max >= actual and first <= i
*/

void steal() {
	int first, max, actual, numwagons, stealnum;

	std::cin >> numwagons >> stealnum;
	int* wagons = new int[numwagons];

	for (int i = 0; i < numwagons; i++)
		std::cin >> wagons[i];

	max = 0;
	for (int i = 0; i < stealnum; i++) 
		max += wagons[i];

	actual = max;
	first = 0;
	for (int i = 1; i <= numwagons - stealnum; i++) {
		actual = actual + wagons[i + stealnum - 1] - wagons[i - 1];
		if (max <= actual) {
			max = actual;
			first = i;
		}
	}
	std::cout << first << " " << max << std::endl;
	delete []wagons;
}

int main() {
	int cases;

	std::cin >> cases;
	while (cases--) {
		steal();
	}

	return 0;
}


13.l------------------------------------------------------------------------------------------------------------

#include <iostream>

/*
pre: {10000 > n > 0 and n = length(v) and 0 < v[i] < 1000000000000000000}
proc criogenizacion(long long int v[], int n, inout long long int mayor, inout long long int fMayor, inout long long int menor, inout long long int fMenor
post: {fMayor = # mayor and fMenor = #menor: mayor = max v[i] and menor = min v[i]: 0 <= i < n}

Best case: everything 0 or 100000000000000000
		first cycle for body: 5 + 2 + 5 + 2 + 1 = 15 
		rest cycles for body: 2 + 3 + 2 + 3 + 1 = 11
		total = 1 + N + 1 + 15 + (N-1)*11 =  12n + 6 -> Linear complexity -> O(n)

Worst case: everything different
		for body: 5 + 2 + 5 + 2 + 1 = 15 
		total: 1 + N + 1 + 15*N = 16N + 2 -> Linear complexity -> O(n)
		
Invariant: 0 <= i <= n and mayor >= v[i] and menor <= v[i] and fMayor >= 0 and fMenor >= 0
*/

void criogenizacion(long long int v[], int n, long long int &mayor, long long int &fMayor, long long int &menor, long long int &fMenor) {
	for (int i = 0; i < n; i++) {
		if (v[i] > mayor) {
			mayor = v[i];
			fMayor = 1;
		}
		else if (v[i] == mayor)
			fMayor++;
		if (v[i] < menor) {
			menor = v[i];
			fMenor = 1;
		}
		else if (v[i] == menor)
			fMenor++;
	}
}

int main() {
	int cases, n;
	long long int num, v[10000], mayor, menor, fMayor, fMenor;

	std::cin >> cases;
	while (cases--) {
		std::cin >> num;
		n = 0;
		while (num != 0) {
			v[n] = num;
			std::cin >> num;
			n++;
		}
		mayor = 0;
		menor = 1000000000000000000;
		fMayor = 0;
		fMenor = 0;
		criogenizacion(v, n, mayor, fMayor, menor, fMenor);
		std::cout << menor << " " << fMenor << " " << mayor << " " << fMayor << std::endl;
	}
	return 0;
}


13.m---------------------------------------------------------------------------------------------------------------

#include <iostream>
/*
pre: {100000 > length >= 0}
func count(int length) return cnt
post: {cnt = #v[j] > v[i]: 0 <= j < i  and 0 <= i < length}

Invariant: 0 <= i <= length and cnt >= 0

Best case: Descendent
		inner while: (n-1)*3 + (n-2)*5 = 8n - 13
		outter while body:  3 + 8n - 13 + 2 = 8n - 8
		total: 1 + 2 + 1 + 8n - 8 = 8n - 4 -> Linear complexity -> O(n)

Worst case: Ascendent
		inner while: 3*2 + 3 + 1 + 1 = 11
		outter while body:  3 + 11 + 3 = 17
		total: 1 + n + 1 + n*(1 + 17) = 19n + 2 -> Linear complexity -> O(n)
*/

int count(int nums[], int length) {
	int cnt = 0, done, i;
	while (length--) {
		done = false;
		i = length - 1;
		while (i >= 0 && !done) {
			if (nums[i] < nums[length])
				done = true;
			else
				cnt++;
			i--;
		}
		length = i != -1 ? i+2 : 0;
	}
	return cnt;
}

int main() {
	int cases, length, nums[100000];

	std::cin >> cases;
	while (cases--) {
		std::cin >> length;
		for (int i = 0; i < length; i++)
			std::cin >> nums[i];

		std::cout << count(nums, length) << std::endl;
	}

	return 0;
}


13.n------------------------------------------------------------------------------------------------------------

#include <iostream>

/*
pre: {length >= 0 and length = length(nums) and nums[i] >= 0 and nums[i] < nums[j]: 0 <= i < length and j > i}
proc deletealo(inout int nums, int length)
post: {nums[i] = -1 if nums[i] odd: 0 <= i < length}

Best case: all even
		total: 1 + n+1 + n*(3 + 1) = 5n + 2 -> Linear complexity -> O(n)

Worst case: all odd
		total: 1 + n+1 + n*(3 + 2 + 1) = 7n + 2 -> Linear complexity -> O(n)
*/

void deletealo(int nums[], int length) {
	for (int i = 0; i < length; i++)
		if (nums[i] % 2 != 0)
			nums[i] = -1;
}

int main() {
	int length, *nums;

	std::cin >> length;
	while (length != -1) {
		nums = new int[length];
		for (int i = 0; i < length; i++)
			std::cin >> nums[i];
		deletealo(nums, length);

		for (int i = 0; i < length; i++)
			if (nums[i] >= 0)
				std::cout << nums[i] << " ";
		delete[]nums;
		std::cout << std::endl;
		std::cin >> length;
	}

	return 0;
}


13.o-------------------------------------------------------------------------------------------------------------

#include <iostream>
#include <string>
#include <vector>

/*
Invariante: -1 <= i < length and max >= 0 and aux >= 0 and first >= 0 and and last >= -1 and laux >= -1 and max >= aux

Best case: no FFFFFF
		For loop body: 2 + 1 + 1 + 3 = 7
		total: 6 + 2 + n+1 + n*(7 + 1) = 9n + 9 -> Linear complexity -> O(n)

Worst case: all FFFFFF
		For loop body first: 2 + 1 + 1 + 1 + 1 + 3 = 9
		For loop body last: 2 + 1 + 1 + 1 + 3 = 8
		total: 6 + 2 + n+1 + 9+1 + (n-1)*(8 + 1) = 10n + 10 -> Linear complexity -> O(n)
*/

void blancos(std::vector <std::string> nums, int pixels) {
	int first = 0, last = -1, max = 0, aux = 0, laux = -1;

	for (int i = pixels - 1; i >= 0; i--) {
		if (nums[i] == "FFFFFF") {
			if (aux == 0)
				laux = i;
			aux++;
		}
		else
			aux = 0;
		if (aux >= max) {
			max = aux;
			last = laux;
			first = i;
		}
	}
	std::cout << first << " " << last << std::endl;
}

int main() {
	int lineas, pixels;
	std::string str;
	std::vector <std::string> nums;
	while (std::cin >> lineas) {
		std::cin >> pixels;
		while (lineas--) {
			for (int i = 0; i < pixels; i++) {
				std::cin >> str;
				nums.push_back(str);
			}
			blancos(nums, pixels);
			nums.erase(nums.begin(), nums.end());
		}
	}
	return 0;
}


13.p------------------------------------------------------------------------------------------------------------

#include <iostream>

/*
Worst case: all greater
		For body first: 2 + 1 + 1 + 1 + 1 + 3 = 9
		For body rest: 2 + 1 + 1 + 1 + 3 = 8
		total: 3 + n+1 + 9+1 + (n-1)*(8+1) = 10n - 5

Best case: all lower
		For body: 2 + 1 = 3
		total: 3 + n+1 + n*(3+1) = 5n + 4 -> Linear complexity -> O(n)
		
*/

void holi(int heights[], int length, int trans, int &first, int &last) {
	int f, aux = 0, max = 0;
	for (int i = 0; i < length; i++) {
		if (heights[i] > trans) {
			if (aux == 0)
				f = i;
			aux++;
		}
		else
			aux = 0;
		if (aux > max) {
			max = aux;
			first = f;
			last = i;
		}
	}
}

int main() {
	int cases, length, trans, *heights, first, last;

	std::cin >> cases;
	while (cases--) {
		std::cin >> length >> trans;
		heights = new int[length];
		for (int i = 0; i < length; i++)
			std::cin >> heights[i];
		first = 0;
		last = 0;
		holi(heights, length, trans, first, last);
		std::cout << first << " " << last << std::endl;
		delete[]heights;
	}
	return 0;
}


14.1-------------------------------------------------------------------------------------------------------------

#include <iostream>

/*
{length > 0, num >= 0}
int compare (int length, int index, int max, int counter) return int index
{(index = counter: max = num[counter]: num[counter - 1] < max and max > num [counter + 1])}
*/

int compare(int length, int index, int max, int counter) {
	int num;
	if (length != 0) {
		std::cin >> num;
		if (num > max) {
			index = counter++;
			max = num;
			length--;
			index = compare(length, index, max, counter);
		}
		else {
			for (int i = 0; i < length - 1; i++)
				std::cin >> num;
		}
	}
	return index;
}

int main() {
	int length, index = 0, max = 0, counter = 0;

	std::cin >> length;
	while (length != 0) {
		std::cout << compare(length, index, max, counter) << std::endl;
		std::cin >> length;
	}
	return 0;
}


14.2----------------------------------------------------------------------------------------------------------------------------

#include<iostream>
#include <vector>
using namespace std;

/*
{for every s >= 0: numbers[s] > 0 and (there exists t > 0: length(numbers) = 2 ^ t)}
proc bool almostSorted((inout bool sorted, in vector <int> numbers, inout int init, inout int length, inout int multiplier) return bool sorted
{sorted = (For every v in numbers: init <= v < length / 2: a[v] < max(length / 2, length)) && (For every w in numbers: length / 2 <= w < length: a[w] > min(init, length / 2) && almostSorted(sorted, numbers, init, length / 2, multiplier) && almostSorted(sorted, numbers, init, length / 2,  multiplier + length / 2))}

complexity: O(nlogn)
*/

//6 12 8 18 10 15 16 40 0

void read(vector <int> &numbers, int n, int &length) {
	cin >> n;
	numbers.push_back(n);
	while (numbers[length] != 0) {
		length++;
		cin >> n;
		numbers.push_back(n);
	}
}

bool almostSorted(bool sorted, vector <int> numbers, int init, int length, int multiplier) {
	int max = 0, min = numbers[init + multiplier];
	if (length >= 2 && sorted) {
		for (int j = (init + multiplier); j < (length + multiplier) / 2; j++) {
			if (min > numbers[j])
				min = numbers[j];
		}

		for (int j = (length + multiplier) / 2; j < (length + multiplier); j++) {
			if (max < numbers[j])
				max = numbers[j];
		}

		for (int j = (init + multiplier); j < (length + multiplier) / 2; j++) {
			if (numbers[j] > max)
				sorted = false;
		}

		for (int j = (init + multiplier); j < (length + multiplier); j++) {
			if (numbers[j] < min)
				sorted = false;
		}
		sorted = almostSorted(sorted, numbers, init, length / 2, multiplier) && almostSorted(sorted, numbers, init, length / 2,  multiplier + length / 2);
	}
	return sorted;
}

int main() {
	vector <int> numbers;
	int init, length, n, multiplier = 0;
	bool sorted;
	cin >> n;
	numbers.push_back(n);
	while (numbers[0] != 0) {
		sorted = true;
		init = 0;
		length = 1;

		read(numbers, n, length);
		if (almostSorted(sorted, numbers, init, length, multiplier))
			cout << "SI" << endl;
		else
			cout << "NO" << endl;
		numbers.erase(numbers.begin(), numbers.end());
		cin >> n;
		numbers.push_back(n);
	}
	return 0;

}


15.1----------------------------------------------------------------------------------------

#include<iostream>

/*
{1 <= num <= 2^31 - 1}
proc fibonacho(in Matrix fibaso, inout Matrix res, in long long int num)
{fib(n)}
fib(in long long int n){fib(n) = fib(n-2) + fib(n - 1): fib(0) = 1 && fib(1) = 1}
complexity: O(nlogn)
*/

typedef struct {
	long long int a0, a1, a2, a3;
} Matrix;

Matrix prod(Matrix m1, Matrix m2) {
	Matrix res;

	res.a0 = (m1.a0 * m2.a0 + m1.a1 * m2.a2) % 46337;
	res.a1 = (m1.a0 * m2.a1 + m1.a1 * m2.a3) % 46337;
	res.a2 = (m1.a2 * m2.a0 + m1.a3 * m2.a2) % 46337;
	res.a3 = (m1.a2 * m2.a1 + m1.a3 * m2.a3) % 46337;

	return res;
}

void fibonacho(Matrix fibaso, Matrix &res, long long int num) {
	if (num > 1) {
		if (num % 2 == 0) {
			fibonacho(fibaso, res, num / 2);
			res = prod(res, res);
		}
		else {
			fibonacho(fibaso, res, num - 1);
			res = prod(res, fibaso);
		}
	}
}

int main() {
	long long int num;
	Matrix fibaso, res;

	std::cin >> num;
	while (num != 0) {
		fibaso.a0 = 0;
		fibaso.a1 = 1;
		fibaso.a2 = 1;
		fibaso.a3 = 1;

		res.a0 = 0;
		res.a1 = 1;
		res.a2 = 1;
		res.a3 = 1;

		fibonacho(fibaso, res, num);
		std::cout << res.a1 << std::endl;
		std::cin >> num;
	}

	return 0;
}


15.a--------------------------------------------------------------------

#include <iostream>
#include <vector>

bool elemento_situado(const std::vector <int>& v, int ini, int fin) {
	bool situado = false;
	int half = (fin + ini) / 2;
	if (ini < fin) {
		if (v[half] == half) {
			situado = true;
		}
		else if (v[half] < half) {
			situado = elemento_situado(v, half + 1, fin);
		}
		else if (v[half] > half) {
			situado = elemento_situado(v, ini, half);
		}
	}
	return situado;
}

int main() {
	int N, length, num, i;
	std::vector <int> v;
	std::cin >> N;

	while (N--) {
		std::cin >> length;
		i = length;
		while (i--) {
			std::cin >> num;
			v.push_back(num);
		}
		elemento_situado(v, 0, length) ? std::cout << "SI" : std::cout << "NO";
		std::cout << std::endl;
		v.erase(v.begin(), v.end());
	}
	return 0;
}


16.1-----------------------------------------------------------------------

#include <iostream>

const int n = 5;

void op(int numbers[], int k, int sol, int el, int cnt, bool &ok) {
	if (cnt < n) {
		op(numbers, k, sol + numbers[el], el + 1, cnt + 1, ok);
		op(numbers, k, sol - numbers[el], el + 1, cnt + 1, ok);
		op(numbers, k, sol * numbers[el], el + 1, cnt + 1, ok);
		if(numbers[el] != 0 && sol % numbers[el] == 0)
			op(numbers, k, sol / numbers[el], el + 1, cnt + 1, ok);
	}
	else {
		if (sol == k)
			ok = true;
	}
}

int main() {
	int k, numbers[n];
	bool ok;

	while (std::cin >> k) {
		ok = false;
		for (int i = 0; i < n; i++) 
			std::cin >> numbers[i];
		op(numbers, k, numbers[0], 1, 1, ok);
		if (ok)
			std::cout << "YES" << std::endl;
		else
			std::cout << "NO" << std::endl;
	}

	return 0;
}


16.e----------------------------------------------------------------------------------------------

#include <iostream>

const int MAX = 20;

void calculate(int numbers[MAX][MAX], int N, bool mark[MAX], int row, int sol, int &solution) {
	if (row != N) {
		for (int counter = 0; counter < N; counter++) {
			if (mark[counter] == false) {
				mark[counter] = true;
				calculate(numbers, N, mark, row + 1, sol + numbers[row][counter], solution);
				mark[counter] = false;
			}
		}
	}
	else if (sol < solution) {
		solution = sol;
	}
}

int main() {
	int N, numbers[MAX][MAX], solution;
	bool mark[MAX];
	std::cin >> N;
	while (N != 0) {
		for (int i = 0; i < N; i++)
			for (int j = 0; j < N; j++)
				std::cin >> numbers[i][j];
		for (int i = 0; i < N; i++)
			mark[i] = false;
		solution = 200000;
		calculate(numbers, N, mark, 0, 0, solution);
		std::cout << solution << std::endl;
		std::cin >> N;
	}

	return 0;
}