#ifndef MATRIX_H
#define MATRIX_H

#include <iostream> //std::string
#include <sstream> //std::stringstream
#include <initializer_list> //std::initializer_list
#include <cmath> //pow

/*add me:
* - inverse
* - division
* - powers
*
*fix me:
* - determinant: calling on matrices >3x3 segfejls
* - multiplication: gives incorrect answer (sometimes)
* - 
*/


namespace Matrix_Utils {
	template<class T> //not just numbers...
	std::string numberToString(T Number){
		std::stringstream ss;
		ss << Number;
		return ss.str();
	}

	//segmentfejl.... :(
	//fix me!
/*	template<class T>
	long double detOfArray(T mat, uint32_t n, long double& d = 0){
		int c, subi, i, j, subj;
		T submat;  

		for(c = 0; c < n; c++) {  
			subi = 0;  
			for(i = 1; i < n; i++) {  
				subj = 0;
				for(j = 0; j < n; j++) {
					if (j == c) continue;
					submat[subi][subj] = mat[i][j];
					subj++;
				}
				subi++;
			}
			d += pow(-1 ,c) * mat[0][c] * detOfArray(submat, (n - 1), d);
		}

		return d;
	}*/

	/*
	//segfejl igen :(
	template<class T, size_t RC>
	long double detOfArray(T (& a)[RC][RC], uint32_t& n) {
		long double det=0;
		uint32_t h, k;
		T temp;

		for (uint32_t p=0;p<n;p++) {
			h = k = 0;
			//k = 0;
			for (uint32_t i = 1; i < n; i++) {
				for (uint32_t j=0; j < n; j++) {
					if (j == p) continue;
					temp[h][k] = a[i][j];
					k++;
					if(k == n - 1) {
						h++;
						k = 0;
					}
				}
			}
			det += a[0][p] * pow(-1, p) * detOfArray(temp, n - 1);
		}
		return det;
	}*/


	//convert to c++ :P
	long double detOfArray(long double **a,int n) {
	   int i,j,j1,j2;
	   long double det = 0;
	   long double **m = NULL;

	   if (n < 1) { /* Error */
			throw std::runtime_error("DETERMINANT: INVALID SIZE ERROR!");
	   } else if (n == 1) { /* Shouldn't get used */
		  det = a[0][0];
	   } else if (n == 2) {
		  det = a[0][0] * a[1][1] - a[1][0] * a[0][1];
	   } else {
		  det = 0;
		  for (j1=0;j1<n;j1++) {
		     m = malloc((n-1)*sizeof(double *));
		     for (i=0;i<n-1;i++)
		        m[i] = malloc((n-1)*sizeof(double));
		     for (i=1;i<n;i++) {
		        j2 = 0;
		        for (j=0;j<n;j++) {
		           if (j == j1)
		              continue;
		           m[i-1][j2] = a[i][j];
		           j2++;
		        }
		     }
		     det += pow(-1.0,1.0+j1+1.0) * a[0][j1] * detOfArray(m,n-1);
		     for (i=0;i<n-1;i++)
		        free(m[i]);
		     free(m);
		  }
	   }
	   return(det);
	}
}


template<class TYPE, size_t ROW, size_t COL>
class Matrix {

public:
	TYPE matrix[ROW][COL];

	//the practical applications for an array with dimensions >4mil. are lacking.
	unsigned int rows, cols;

	//good to set it here...
	//bool isquare = (ROW == COL);


	Matrix(): rows(ROW), cols(COL) {} //default construxtor.

	template <class T>//2D init-list constructor
	Matrix(const std::initializer_list<std::initializer_list<T> >& list):
		rows(ROW), cols(COL)
	{	
		decltype(list.size()) r = 0;
		for (const auto& l : list) {
			decltype((*list.begin()).size()) c = 0;
			for (const auto& d : l) {
				matrix[r][c] = (TYPE) d;
				if (++c >= cols) break;
			}
			if (++r >= rows) break;
		}
	}
	template<class T> //1D init-list constructor
	Matrix(const std::initializer_list<T>& list):
		rows(ROW), cols(COL)
	{	
		decltype(list.size()) c = 0;
		for (const auto& l : list)
				matrix[0][c++] = (TYPE) l;
	}
	template<class T> ///initialize matrix with 2D array
	Matrix(const T init[ROW][COL]):
		rows(ROW), cols(COL)
	{
		for (unsigned int r = 0; r < rows; r++)
			for (unsigned int c = 0; c < cols; c++)
				matrix[r][c] = init[r][c];

	}
	~Matrix(){} //default destructor

	//getter/setters (index):
	TYPE& at(uint32_t row, uint32_t col){
		//if (row >= rows || col >= cols) throw "ERROR: OUT OF BOUNDS";
		return matrix[row][col];
	}

	TYPE& operator()(uint32_t row, uint32_t col){ //mat(2,1) = mat.at(2,1)
		return matrix[row][col];
	}

	//printing:
	std::string toString(){ ///returns a text representation (std::string)
		std::string buf;
		//single row uses brackets.
		if (rows==1) { // "[12	21	12	2	23	2] 
			buf += '[';
			for (uint32_t c = 0; c < cols; c++) {
				buf += Matrix_Utils::numberToString(matrix[0][c]);
				if (c != cols - 1) buf += '\t';
			}buf += ']';
			return buf;
		}
		
		buf += "┌";
		for (uint32_t c = 0; c < cols; c++) buf += '\t';
		buf += "┐";

		for (uint32_t r = 0; r < rows; r++) {
			buf += "\n│";			
			for (uint32_t c = 0; c < cols; c++) {
				buf += Matrix_Utils::numberToString(matrix[r][c]);
				buf += "\t";
			}
			buf += "│";
		}

		buf += "\n└";
		for (uint32_t c = 0; c < cols; c++) buf += '\t';
		buf += "┘";

		return buf;
	}

	template<class T>///set matrix to an initializer list
	void operator=(const std::initializer_list<std::initializer_list<T> >& list){
		decltype(list.size()) r = 0;
		for (const auto& l : list) {
			decltype((*list.begin()).size()) c = 0;
			for (const auto& d : l)
				matrix[r][c++] = d;
			r++;
		}
	}
	template<class T>///set matrix from a 2D array
	void operator=(const T init[ROW][COL]){
		for (unsigned int r = 0; r < rows; r++)
			for (unsigned int c = 0; c < cols; c++)
				matrix[r][c] = init[r][c];
	}
	template<class T>
	Matrix& operator=(const Matrix<T,ROW,COL>& x){
		for (unsigned int r = 0; r < rows; r++)
			for (unsigned int c = 0; c < cols; c++)
				matrix[r][c] = (TYPE)x.matrix[r][c];
	}

	//multiplication:
	
	template<class T, size_t NROWS, size_t NCOLS> //fix algorithm (is this fixed???)
	Matrix<long double,  ROW, NCOLS>& operator*(Matrix<T, NROWS, NCOLS>& num){
		
		if (COL != NROWS) {
			std::cout <<"DIMENSION ERROR:\n(" <<ROW <<" x " <<COL 
				<<") * (" <<NROWS <<" x " <<NCOLS <<") is an invalid operation.\n";
			throw std::runtime_error("MULTIPLICATION: DIM ERROR!");
		}

		Matrix<long double, ROW, NCOLS>* ans = new Matrix<long double, ROW, NCOLS>;

		for (uint32_t y = 0; y < rows; y++)
			for (uint32_t x = 0; x < num.cols; x++) {
				ans->at(y, x) = 0;
				for (uint32_t z = 0; z < cols; z++) {
					//std::cout <<"matrix["<<z<<"]["<<y<<"]*num.at("<<x<<","<<z<<")= " //debugging
					//	<<matrix[y][z]<<"*"<<num.at(x,z)<<"= "<<matrix[y][z]*num.at(z, x)<<"\n";
					ans->matrix[y][x] += (long double)matrix[y][z] * num.matrix[z][x];
				}
				//std::cout <<"Sum : " <<ans->at(y, x) <<"\n\n";// <<ans->toString();
			}
		return *ans;
	}
	//ADD ME: operator*=() : only takes square matricies with equal dimensions.

	//scalar multiplication:
	template<class T> 
	Matrix& operator*(const T& n){
		for (uint32_t r = 0; r < rows; r++)
			for (uint32_t c = 0; c < cols; c++)
				matrix[r][c] *= n;
		return *this;
	}
	template<class T>
	Matrix& operator*=(const T& n){
		for (uint32_t r = 0; r < rows; r++)
			for (uint32_t c = 0; c < cols; c++)
				matrix[r][c] *= n;
		return *this; //is a return type needed?
	}

	//addition:
	template<class T>//fixme
	Matrix& operator+(Matrix<T,ROW,COL>& a){
		Matrix<int,ROW,COL> ans;
		for (uint32_t r = 0; r < rows; r++)
			for (uint32_t c = 0; c < cols; c++)
				ans.matrix[r][c] = matrix[r][c] + a.matrix[r][c];
		return ans;
	}
	template<class T>
	Matrix& operator+=(const Matrix<T,ROW,COL>& a){
		for (uint32_t r = 0; r < rows; r++)
			for (uint32_t c = 0; c < cols; c++)
				matrix[r][c] += a.matrix[r][c];
		return *this;
	}

	//subtraction:
	template<class T>//fixme 
	Matrix& operator-(Matrix<T,ROW,COL>& a){
		Matrix<long double, ROW, COL> ans;		
		for (uint32_t r = 0; r < rows; r++)
			for (uint32_t c = 0; c < cols; c++)
				ans.matrix[r][c] = matrix[r][c] - a.matrix[r][c];
		return ans;
	}
	template<class T>
	Matrix& operator-=(const Matrix<T,ROW,COL>& a){
		for (uint32_t r = 0; r < rows; r++)
			for (uint32_t c = 0; c < cols; c++)
				matrix[r][c] -= a.matrix[r][c];
		return *this;
	}

};

//matrix functions
template<class T, size_t ROW, size_t COL>
long double det(Matrix<T,ROW,COL>& mat){

	if (mat.rows != mat.cols) //not a square matrix
		throw std::runtime_error("DET(): DIM ERROR!");
	if (mat.rows == 1) //1x1
		return mat.matrix[0][0];
	if (mat.rows == 2) //2x2
		return mat.matrix[0][0]*mat.matrix[1][1] - mat.matrix[1][0]*mat.matrix[0][1];
	if (mat.rows == 3) //3x3
		return (//rule of Sarrus (there is probably a more efficient process)
			mat.matrix[0][0] * mat.matrix[1][1] * mat.matrix[2][2] +
			mat.matrix[0][1] * mat.matrix[1][2] * mat.matrix[2][0] +
			mat.matrix[0][2] * mat.matrix[1][0] * mat.matrix[2][1] -
			mat.matrix[2][0] * mat.matrix[1][2] * mat.matrix[0][2] -
			mat.matrix[2][1] * mat.matrix[1][0] * mat.matrix[0][0] -
			mat.matrix[2][2] * mat.matrix[1][1] * mat.matrix[0][1]
		);
	/*
	long double product1 = 0, product2 = 0, solution = 0;

	for (uint32_t c = 0; c < mat.cols; c++) {
		product1 = mat.at(0, ((c + 0) % mat.cols));
		std::cout <<product1;
		for (uint32_t r = 1; r < mat.rows; r++) {
			product1 *= (long double)mat.at(r, ((c + r) % mat.cols));
			std::cout <<" * " <<mat.at(r, ((c + r) % mat.cols));
		}
		std::cout <<" = +" <<product1 <<"\n";		
		solution += product1;
	}
	for (uint32_t c = 0; c < mat.cols; c++){ //0, 1, 2
		product2 = mat.at(mat.rows - 1, c); //2
		std::cout <<"\n" <<product2;
		uint32_t i = c;
		for (long long int r = mat.rows - 2; r >= 0; r--){ //1, 0
		
			std::cout <<" * " <<mat.at(r, (r + 1 + i) % mat.cols);
			product2 *= mat.at(r, (r + ++i) % mat.cols);
		}
		std::cout <<" = -" <<product2;
		solution -= product2;
		//system("sleep 1");//
	}
	return solution;*/
		
	//}
	//else 
		//I don't know any algorithms for more than 3x3 matrices...
	std::cout <<"\nThis feature hasn't been implemented yet\n";
//	return NULL;

//	long double d = 0;
	
	return Matrix_Utils::detOfArray(mat.matrix, mat.rows);

}

/*
//most recently stolen code...
int determinant(int size,int det[][100])  // size & row of the square matrix
{
    int temp[100][100],a=0,b=0,i,j,k;
    int sum=0,sign;  //sum will hold value of determinant of the current matrix
 
    if(size==2) return (det[0][0]*det[1][1]-det[1][0]*det[0][1]);
     
    sign=1;
    for(i=0;i<size;i++){  // note that 'i' will indicate column no.
        a=0;
        b=0;
 
        // copy into submatrix and recurse
        for (j=1;j<size;j++) { // should start from the next row !!
            for (k=0;k<size;k++){
                if(k==i) continue;
                    temp[a][b++]=det[j][k];
            }
            a++;
            b=0;
        }
        sum+=sign*det[0][i]*determinant(size-1,temp);   // increnting row & decrementing size
        sign*=-1;
    }
    return sum;
}
*/
#endif
