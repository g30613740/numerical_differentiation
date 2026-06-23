#include "functions.h"

int main () {

	// I. Parameters of the program. //
    const long double a = -3.14, b = 3.14;
    const size_t M = 20, shredded_M = 2 * M - 1;
    const long double h = abs (a - b) / (M - 1);

    // II. Memory allocation. //

    // arrays for derivative creating (step h) //
    long double *x = new long double [M];
    long double *y = new long double [M];
    long double *math_derivative = new long double [M];
    long double *nm_derivative = new long double [M];
    // arrays for derivative creating (step h / 2) //
    long double *shredded_x = new long double [shredded_M];
    long double *shredded_y = new long double [shredded_M];
    long double *shredded_math_derivative = new long double [shredded_M];
    long double *shredded_nm_derivative = new long double [shredded_M];
    // updated Runge solution //
    long double *runge_main_members = new long double [M];
    long double *updated_runge_solution = new long double [M];

    // III. Creating derivatives. //

    get_the_array_of_the_derivatives_at_a_points_of_a_grid (x, y, math_derivative, nm_derivative, M, a, h);
    get_the_array_of_the_derivatives_at_a_points_of_a_grid (
        shredded_x,
        shredded_y,
        shredded_math_derivative,
        shredded_nm_derivative,
        shredded_M,
        a,
        h / 2);

    // IV. Update solution with first and second Runge formules. //

    for (size_t i = 0; i < M; ++i) {
        runge_main_members[i] = (shredded_nm_derivative[2*i] - nm_derivative[i]) / 3;
        updated_runge_solution[i] = nm_derivative[i] + runge_main_members[i];
    }

    // V. Evaluating errors and format outputting. //

    evaluate_and_print_errors_as_a_table (
        math_derivative,
        nm_derivative,
        shredded_math_derivative,
        shredded_nm_derivative,
        updated_runge_solution,
        runge_main_members,
        M,
        shredded_M);

    // VI. Creating plot. //

    const size_t M_viz = 100;
    const string filename = "parameters.txt";

    extract_data_to_the_file (
        math_derivative,
        M_viz,
        x,
        nm_derivative,
        M,
        shredded_x,
        shredded_nm_derivative,
        shredded_M,
        updated_runge_solution,
        filename);

    // start Python for plot creating //
    string comand_and_filename = "python3 create_plot.py"; // start Python
    system (comand_and_filename.c_str ());                 // calling Python

    // VII. Freeing up resources. //
    
    delete [] x;
    delete [] y;
    delete [] math_derivative;
    delete [] nm_derivative;
    delete [] shredded_x;
    delete [] shredded_y;
    delete [] shredded_math_derivative;
    delete [] shredded_nm_derivative;
    delete [] runge_main_members;
    delete [] updated_runge_solution;

    return 0;
}