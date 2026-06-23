#include <iostream>
#include <fstream>
#include <math.h>
#include <iomanip>

using namespace std;


long double get_the_value_of_the_math_function_at_a_point (long double point);

long double get_the_value_of_the_derivative_of_the_math_function_at_a_point (long double point);

void get_the_array_of_the_derivatives_at_a_points_of_a_grid (
    long double* &arg_x,
    long double* &arg_y,
    long double* &arg_math_derivative,
    long double* &arg_nm_derivative,
    const size_t arg_M,
    const long double arg_a,
    const long double arg_h);

void evaluating_errors_for_two_vectors (
    const long double *accurate_values,
    const long double *approximate_values,
    const size_t number_of_values,
    long double* &result);

void evaluate_and_print_errors_as_a_table (
    const long double* par_math_derivative,
    const long double* par_nm_derivative,
    const long double* par_shredded_math_derivative,
    const long double* par_shredded_nm_derivative,
    const long double* par_updated_runge_solution,
    const long double* par_runge_main_members,
    const size_t par_M,
    const size_t par_shredded_M);

void extract_data_to_the_file (
    const long double* par_math_derivative,
    const size_t par_M_viz,
    const long double* par_x,
    const long double* par_nm_derivative,
    const size_t par_M,
    const long double* par_shredded_x,
    const long double* par_shredded_nm_derivative,
    const size_t par_shredded_M,
    const long double* par_updated_runge_solution,
    const string par_filename);