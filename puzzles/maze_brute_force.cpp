/******************************************************************************
Complete the function FindPath below.  This function takes a matrix object
(defined below), and a start and an end cells within that matrix.
The matrix is filled with values of either 0 or 1.  The function should return
the shortest path between the start and the end cells given, such that no
matrix cells with value of 1 are part of the path.  The function should return
this path in the form of sequence of Matrix cells, including start and end.
A valid path consists of sequence of matrix cells adjacent to each other.
Cell A is adjacent to cell B if it is immediately to the right, left,
above, or below.  For example, in the following matrix:

 0  1  2
 3  4  5
 6  7  8

 Cell "4" is adjacent to cells 3, 1, 5, and 7.

There are no wraparounds, e.g. cells 7 and 1 are not adjacent.

Cells are identified via (row, col), starting from 0, i.e. in the following matrix
0 0 0 0 0
0 0 0 0 1
0 0 0 0 0

Cell with value 1 is at (1, 4)

Example 1:

Matrix:
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
0 0 0 0 0 0 0 0 0
Start:(0,0) End:(2, 3)

Possible solution (one of many):  (0,0),(0,1),(0,2),(0,3),(1,3),(2,3)

Example 2:

Matrix:
0 1 0 0 0 0 0 0 0
0 0 0 1 0 0 0 0 0
0 1 0 0 0 0 0 0 0
Start:(0,0) End:(2, 3)

Solution:  (0,0),(1,0),(1,1),(1,2),(2,2),(2,3)

If no path could be found, the function should return an empty list.

Note:
     - Feel free to use a text editor or IDE of your choice to do this instead.
     - If you do, simply just copy-paste your code here when you're done.
     - Do not change function signature.
     - You are free to add any supporting helper functions, data types, or
       structures you wish.
     - You may make use of STL data structures and algorithms
     - main function has been provided to make code run inside Rextester Web
       IDE. It is not required to be part of the submission and will not be
       graded.
******************************************************************************/

#include <vector>
#include <memory>


struct Location
{
	size_t row_;
	size_t col_;
};

using Locations = std::vector<Location>;

struct Matrix
{
	friend class MutMatrix;
public:
	explicit Matrix(size_t rows, size_t cols, const Locations& walls)
			: rows_{ rows }, cols_{ cols }, data_(new int[rows * cols])
	{ InitializeMatrix(walls); }


	void InitializeMatrix(const Locations& walls)
	{
		// Zero data
		for (size_t row = 0; row < rows_; row++)
		{
			for (size_t col = 0; col < cols_; col++)
			{
				data_[cols_ * row + col] = 0;
			}
		}

		// Add walls
		for (const auto& wall : walls)
		{
			data_[cols_ * wall.row_ + wall.col_] = 1;
		}
	}

	const int& operator()(const Location& location) const
	{
		if (location.row_ >= rows_ || location.col_ >= cols_)
			throw std::out_of_range("OOB");

		return data_[cols_ * location.row_ + location.col_];
	}

	size_t NumRows() const { return rows_; }
	size_t NumCols() const { return cols_; }

private:
	size_t rows_;
	size_t cols_;
	std::unique_ptr<int[]> data_;
};

// didn't want to modify provided code
class MutMatrix {
public:
	explicit MutMatrix(const Matrix& m)
	{
		rows_ = m.NumRows();
		cols_ = m.NumCols();
		data_ = std::make_unique<int[]>(rows_ * cols_);
		for (size_t i = 0; i < rows_ * cols_; i++)
			data_[i] = m.data_[i];
	}

	int& operator()(const Location& location) {
		if (location.row_ >= rows_ || location.col_ >= cols_)
			throw std::out_of_range("OOB");

		return data_[cols_ * location.row_ + location.col_];
	}
	size_t rows_;
	size_t cols_;
	std::unique_ptr<int[]> data_;
};



bool operator==(const Location& l, const Location& r){
	return l.row_ == r.row_ && l.col_ == r.col_;
}


// algorithm: recursive fill
//   there is definintly a more efficient solution,
//   however for the sake of time...
std::vector<Locations> FindPathRec(MutMatrix& m, const Location& start, const Location& end) {
	// hit a wall
	if (m(start))
		return {};
	if (start == end) {
		return { { start } };
	}

	// make start a wall so that we don't go backwards
	m(start) = 1;

	// mat sizing
	const size_t r = m.rows_ - 1;
	const size_t c = m.cols_ - 1;

	std::vector<Locations> ret;

	// recursive call return values
	std::vector<Locations> slns;

	// check each direction
	if (start.row_ != 0) {
		const Location new_start = { start.row_ - 1, start.col_ };
		const std::vector<Locations> tmp = FindPathRec(m, new_start, end);
		slns.insert(slns.end(), tmp.begin(), tmp.end());
	}
	if (start.col_ != 0) {
		const Location new_start = { start.row_ , start.col_ - 1};
		const std::vector<Locations> tmp = FindPathRec(m, new_start, end);
		slns.insert(slns.end(), tmp.begin(), tmp.end());
	}
	if (start.row_ < r) {
		const Location new_start = { start.row_ + 1, start.col_ };
		const std::vector<Locations> tmp = FindPathRec(m, new_start, end);
		slns.insert(slns.end(), tmp.begin(), tmp.end());
	}
	if (start.col_ < c) {
		const Location new_start = { start.row_ , start.col_ + 1};
		const std::vector<Locations> tmp = FindPathRec(m, new_start, end);
		slns.insert(slns.end(), tmp.begin(), tmp.end());
	}

	// ret = slns.map(s => [start].concat(s))
	for (Locations& sln : slns) {
		ret.emplace_back(Locations({ start }));
		Locations& path = ret[ret.size() - 1];
		path.insert(path.end(), sln.begin(), sln.end());
	}

	return ret;
}

Locations FindPath(const Matrix& m, const Location& start, const Location& end)
{
	// make mutable copy of m
	MutMatrix mut_m(m);
	std::vector<Locations> paths = FindPathRec(mut_m, start, end);
	if (paths.empty())
		return {};

	size_t min_i = 0, min_s = paths[0].size();
	for (size_t i = 0; i < paths.size(); i++)
		if (paths[i].size() < min_s) {
			min_i = i;
			min_s = paths[i].size();
		}

	return paths[min_i];
}

int main ()
{
	Locations walls;
	walls.push_back({1, 1});
	walls.push_back({1, 0});
	walls.push_back({0, 1});

	Matrix matrix(3,3, walls);
	Locations ret = FindPath(matrix, {0,0}, {2,2});
//	for (const Location& pt : ret) {
//		std::cout << pt.row_ << ", " << pt.col_ << std::endl;
//	}
}
